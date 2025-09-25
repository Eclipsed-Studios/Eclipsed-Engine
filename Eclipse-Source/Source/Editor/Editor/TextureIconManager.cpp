#include "TextureIconManager.h"

#include <filesystem>
#include <fstream>

#include "AssetManagement/Loader/ResourceLoaderHelper.h"

#include <glad/glad.h>

#include "FileWatcher.h"

namespace Eclipse::Editor
{
	void IconManager::CheckForChanges()
	{
		namespace fs = std::filesystem;

		auto onFileAdded = [](const std::string& path) {
			FileInfo info = Resources::GetFileInfo(path);
			if (info.type != FileInfo::FileType_Texture) return;

			if (std::find(filesToLoad.begin(), filesToLoad.end(), path) == filesToLoad.end()) filesToLoad.push_back(path);
			};

		auto onFileRemoved = [](const std::string& path) {
			FileInfo info = Resources::GetFileInfo(path);
			if (info.type != FileInfo::FileType_Texture) return;

			std::string relativePath = fs::relative(path, SOURCE_PATH).generic_string();
			size_t id = std::hash<std::string>{}(relativePath);

			if (loadedIcons.find(id) == loadedIcons.end()) return;

			loadedIcons.erase(id);
			};

		FileWatcher::Subscribe(EventType::FileAdded, onFileAdded);
		FileWatcher::Subscribe(EventType::FileRemoved, onFileRemoved);

		int textureCounter = 0;
		for (auto& entry : fs::recursive_directory_iterator(ASSET_PATH))
		{
			FileInfo info = Resources::GetFileInfo(entry);
			if (info.type != FileInfo::FileType_Texture) continue;

			textureCounter++;

			std::string relativePath = fs::relative(entry.path(), SOURCE_PATH).generic_string();
			size_t id = std::hash<std::string>{}(relativePath);

			if (loadedIcons.find(id) != loadedIcons.end())
			{
				fs::file_time_type ftime = fs::last_write_time(entry);

				std::chrono::system_clock::time_point sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
					ftime - fs::file_time_type::clock::now()
					+ std::chrono::system_clock::now()
				);

				if (loadedIcons[id].lastWriteTime != std::chrono::system_clock::to_time_t(sctp))
				{
					filesToLoad.push_back(entry.path().string());
					loadedIcons.erase(id);
				}
			}
			else
			{
				filesToLoad.push_back(entry.path().string());
			}
		}
	}

	void IconManager::Update()
	{
		namespace fs = std::filesystem;

		for (auto it = filesToLoad.begin(); it != filesToLoad.end();)
		{
			const std::string path(it->c_str());
			if (IsFileReady(path))
			{

				std::string relativePath = fs::relative(path, SOURCE_PATH).generic_string();

				size_t id = std::hash<std::string>{}(relativePath);

				if (loadedIcons.find(id) == loadedIcons.end())
				{
					if (!LoadTextureIconFromPath(path))
					{
						it++;
						continue;
					}
					ExportLoadedTextures();

					it = filesToLoad.erase(it);
				}
				else
				{
					it++;
				}
			}
			else
			{
				it++;
			}
		}

	}

	void IconManager::LoadIconsFile()
	{
		namespace fs = std::filesystem;

		std::ifstream in(IconBundleFilePath, std::ios::binary);

		int count = 0;
		in.read(reinterpret_cast<char*>(&count), sizeof(int));

		if (count == 0)
		{
			in.close();

			LoadAllTextureIcons();
			ExportLoadedTextures();
			return;
		}

		for (int i = 0; i < count; ++i)
		{
			size_t id;
			in.read(reinterpret_cast<char*>(&id), sizeof(size_t));

			IconData& data = loadedIcons[id];

			in.read(reinterpret_cast<char*>(&data.channels), sizeof(unsigned));
			in.read(reinterpret_cast<char*>(&data.width), sizeof(int));
			in.read(reinterpret_cast<char*>(&data.height), sizeof(int));
			in.read(reinterpret_cast<char*>(&data.lastWriteTime), sizeof(long long));

			const int size = data.width * data.height * data.channels;
			data.data.resize(size);
			in.read(reinterpret_cast<char*>(data.data.data()), size);

			CreateOpenGLTextureFromData(data);
		}

		in.close();
	}

	void IconManager::LoadAllTextureIcons()
	{
		namespace fs = std::filesystem;

		std::vector<std::string> texturesPathsToLoad;
		for (const fs::directory_entry& entry : fs::recursive_directory_iterator(ASSET_PATH))
		{
			FileInfo info = Resources::GetFileInfo(entry);
			if (info.type != FileInfo::FileType_Texture) continue;

			texturesPathsToLoad.push_back(entry.path().string());
		}

		for (const std::string& path : texturesPathsToLoad)
		{
			LoadTextureIconFromPath(path);
		}
	}

	bool IconManager::LoadTextureIconFromPath(const std::filesystem::path& path)
	{
		namespace fs = std::filesystem;

		std::string relativePath = fs::relative(path, SOURCE_PATH).generic_string();

		size_t id = std::hash<std::string>{}(relativePath);

		IconData& data = loadedIcons[id];

		{ // Get last write time.
			fs::file_time_type ftime = fs::last_write_time(path);

			std::chrono::system_clock::time_point sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
				ftime - fs::file_time_type::clock::now()
				+ std::chrono::system_clock::now()
			);

			data.lastWriteTime = std::chrono::system_clock::to_time_t(sctp);
		}

		{ // Load texture
			int width = 0, height = 0;
			unsigned char* pixels = ResourceLoaderHelper::Load_Texture_STB(path.string().c_str(), width, height, data.channels);
			if (!pixels)
			{
				loadedIcons.erase(id);
				return false;
			}

			if (width >= height)
			{
				data.width = 128.f;
				data.height = (float)height / (float)width * 128.f;
			}
			else
			{
				data.height = 128.f;
				data.width = (float)width / (float)height * 128.f;
			}

			unsigned char* resizedPixels = ResourceLoaderHelper::Resize_STB(pixels, width, height, data.width, data.height, data.channels);

			const int size = data.width * data.height * data.channels;
			data.data.resize(size);
			memcpy(data.data.data(), resizedPixels, size);

			ResourceLoaderHelper::FreeData_STB(resizedPixels);
		}

		CreateOpenGLTextureFromData(data);
		return true;
	}

	void IconManager::ExportLoadedTextures()
	{
		namespace fs = std::filesystem;

		std::ofstream out(IconBundleFilePath, std::ios::binary);

		const int count = (int)loadedIcons.size();
		out.write(reinterpret_cast<const char*>(&count), sizeof(int));

		for (auto& [id, data] : loadedIcons)
		{
			out.write(reinterpret_cast<const char*>(&id), sizeof(size_t));
			out.write(reinterpret_cast<const char*>(&data.channels), sizeof(unsigned));
			out.write(reinterpret_cast<const char*>(&data.width), sizeof(unsigned));
			out.write(reinterpret_cast<const char*>(&data.height), sizeof(unsigned));
			out.write(reinterpret_cast<const char*>(&data.lastWriteTime), sizeof(long long));

			out.write(reinterpret_cast<const char*>(data.data.data()), data.width * data.height * data.channels);
		}

		out.close();
	}

	bool IconManager::IsFileReady(const std::filesystem::path& path)
	{
		std::ifstream file(path, std::ios::binary);
		return file.is_open() && file.peek() != std::ifstream::traits_type::eof();
	}

	void IconManager::CreateOpenGLTextureFromData(IconData& data)
	{
		glGenTextures(1, &data.textureID);
		glBindTexture(GL_TEXTURE_2D, data.textureID);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		GLenum format;
		if (data.channels == 1)
			format = GL_RED;
		else if (data.channels == 2)
			format = GL_RG;
		else if (data.channels == 3)
			format = GL_RGB;
		else if (data.channels == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, data.width,
			data.height, 0, format, GL_UNSIGNED_BYTE, data.data.data());
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	const IconData& IconManager::GetIcon(const std::string& path)
	{
		namespace fs = std::filesystem;

		std::string relative = fs::relative(path, SOURCE_PATH).generic_string();
		size_t id = std::hash<std::string>{}(relative);

		if (loadedIcons.find(id) == loadedIcons.end()) return{};


		return loadedIcons[id];
	}
}
