#include "BlackBoard.h"


namespace ENGINE_NAMESPACE
{
	rapidjson::Value Utilities::BlackBoard::Save(rapidjson::Document::AllocatorType& allocator) const
	{
        rapidjson::Value value(rapidjson::kObjectType);

        for (auto& [type, list] : myData)
        {
            rapidjson::Value objList(rapidjson::kArrayType);

            for (auto& [name, obj] : list)
            {
                rapidjson::Value entry(rapidjson::kObjectType);

                if (obj.type() == typeid(int))
                {
                    entry.AddMember(
                        rapidjson::Value(name.c_str(), allocator).Move(),
                        rapidjson::Value(std::any_cast<int>(obj)).Move(),
                        allocator
                    );
                }
                else if (obj.type() == typeid(float))
                {
                    entry.AddMember(
                        rapidjson::Value(name.c_str(), allocator).Move(),
                        rapidjson::Value(std::any_cast<float>(obj)).Move(),
                        allocator
                    );
                }
                else if (obj.type() == typeid(std::string))
                {
                    entry.AddMember(
                        rapidjson::Value(name.c_str(), allocator).Move(),
                        rapidjson::Value(std::any_cast<std::string>(obj).c_str(), allocator).Move(),
                        allocator
                    );
                }
                else if (obj.type() == typeid(Math::Vector2i))
                {
                    entry.AddMember(
                        rapidjson::Value(name.c_str(), allocator).Move(),
                        rapidjson::Value(std::any_cast<Math::Vector2i>(obj).Save(allocator), allocator).Move(),
                        allocator
                        );
                }

                objList.PushBack(entry, allocator);
            }
            
            value.AddMember(
                rapidjson::Value(type.name(), allocator).Move(),
                objList,
                allocator
            );
        }

        return value;
	}

	void Utilities::BlackBoard::Load(const rapidjson::Value& aValue)
	{
        LoadArray<int>(aValue);
        LoadArray<Math::Vector2i>(aValue);
        LoadArray<std::string>(aValue);
        LoadArray<float>(aValue);
	}
}