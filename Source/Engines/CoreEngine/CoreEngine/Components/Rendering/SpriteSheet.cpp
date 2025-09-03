#include "SpriteSheet.h"

#include "rapidjson/rapidjson/rapidjson.h"
#include "rapidjson/rapidjson/document.h"

#include "rapidjson/rapidjson/filereadstream.h"
#include "rapidjson/rapidjson/filewritestream.h"
#include "rapidjson/rapidjson/prettywriter.h"

#include <fstream>

namespace ENGINE_NAMESPACE
{
    void SpriteSheet::Load(const char* aMetaPath)
    {
        FILE* filePtr = fopen(aMetaPath, "rb");
        char readBuffer[32768];

        rapidjson::FileReadStream fileRS(filePtr, readBuffer, sizeof(readBuffer));

        rapidjson::Document doc;
        doc.ParseStream(fileRS);
        fclose(filePtr);

        auto& frames = doc["Frames"];
        mySpriteRects.clear();
        for (auto& frame : frames.GetArray())
        {
            SpriteSheetRect rec;
            auto min = frame["Min"].GetArray();
            rec.min.x = min[0].GetFloat();
            rec.min.y = min[1].GetFloat();

            auto max = frame["Max"].GetArray();
            rec.max.x = max[0].GetFloat();
            rec.max.y = max[1].GetFloat();

            mySpriteRects.push_back(rec);
        }
    }

    void SpriteSheet::Save(const char* aMetaPath)
    {
        rapidjson::Document doc;
        doc.SetObject();

        rapidjson::Value framesArray(rapidjson::kArrayType);

        {
            rapidjson::Value object(rapidjson::kObjectType);
            rapidjson::Value min(rapidjson::kArrayType);
            min.PushBack(0, doc.GetAllocator());
            min.PushBack(0, doc.GetAllocator());
            object.AddMember("Min", min, doc.GetAllocator());
            
            rapidjson::Value max(rapidjson::kArrayType);
            max.PushBack(100, doc.GetAllocator());
            max.PushBack(100, doc.GetAllocator());
            object.AddMember("Max", max, doc.GetAllocator());

            framesArray.PushBack(object, doc.GetAllocator());
        }

        doc.AddMember("Frames", framesArray, doc.GetAllocator());

        FILE* filePtr = fopen(aMetaPath, "wb");

        char writeBuffer[32768];
        rapidjson::FileWriteStream fileWS(filePtr, writeBuffer, sizeof(writeBuffer));

        rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(fileWS);
        doc.Accept(writer);

        fclose(filePtr);
    }
}