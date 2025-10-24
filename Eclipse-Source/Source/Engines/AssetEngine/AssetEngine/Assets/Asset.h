#pragma once

#define ASSET_IMPL(TYPE, HANDLE, MANAGER)																	\
friend class MANAGER;																						\
public:																										\
TYPE() = default;																							\
TYPE(HANDLE* handle) : dataHandle(handle) { if (dataHandle) dataHandle->refCount++; }						\
~TYPE() { if (dataHandle) dataHandle->refCount--; }															\
TYPE(const TYPE& other) : dataHandle(other.dataHandle) { if (dataHandle)dataHandle->refCount++; }			\
Textures operator=(const Textures& other)																	\
{																											\
	if (this == &other)																						\
		return *this;																						\
																											\
	if (dataHandle)																							\
		dataHandle->refCount--;																				\
																											\
	dataHandle = other.dataHandle;																			\
																											\
	if (dataHandle)																							\
		dataHandle->refCount++;																				\
																											\
	return *this;																							\
}																											\
TYPE(TYPE&& other) noexcept																					\
	: dataHandle(other.dataHandle)																			\
{																											\
	other.dataHandle = nullptr;																				\
}																											\
																											\
TYPE& operator=(TYPE&& other) noexcept																		\
{																											\
	if (this != &other)																						\
	{																										\
		if (dataHandle)																						\
			dataHandle->refCount--;																			\
																											\
		dataHandle = other.dataHandle;																		\
		other.dataHandle = nullptr;																			\
	}																										\
	return *this;																							\
}																											\
																											\
	private:																								\
		HANDLE* dataHandle = nullptr;