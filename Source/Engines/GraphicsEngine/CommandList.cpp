#include "CommandList.h"

namespace Eclipse
{
    void CommandList::Emplace(const std::function<void()>& aCommand)
    {
        myCommandList.emplace_back(aCommand);
    }

    void CommandList::Execute()
    {
        for(auto& command : myCommandList)
            command();
    }

    void CommandList::Clear()
    {
        myCommandList.clear();
    }
}