#pragma once


#define BASE_ASSET(_Asset)											\
public:																\
	_Asset##Data* data = nullptr;									\
	_Asset(_Asset##Data* _data) : data(_data) {isValid = true;}		\
	_Asset() = default;							 					\
																	\
_Asset##Data* GetData() { return data; }							\
bool IsValid() const { return isValid; }							\
const std::string& GetAssetID() const { return data->assetID;}		\
private:															\
	bool isValid = false;											\
private:
	

namespace Eclipse
{
	
}