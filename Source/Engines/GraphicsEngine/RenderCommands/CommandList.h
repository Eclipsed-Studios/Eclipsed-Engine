#pragma once

#define MAXCOMMANDALLOCATION 10000

#include "RenderCommand.h"

#include <vector>
#include <functional>

namespace Eclipse
{
    class LambdaCommand : public RenderCommandBase
    {
    public:
        LambdaCommand(std::function<void()>&& aLambda) : myLamdaCommand(std::move(aLambda))
        {

        }

        void Execute() override { myLamdaCommand(); };

        std::function<void()> myLamdaCommand;
    };

    class CommandList
    {
    public:
        static void Init();

        template <class CommandClass, class ...Args>
        static void Enqueue(Args... args);

        static void Enqueue(const std::function<void()>& aLambda);

        static void Execute();
        static void Reset();

    private:
        static inline uint8_t* myData = nullptr;
        static inline size_t commandCursor = 0;

        static inline RenderCommandBase* myRoot;
        static inline RenderCommandBase** myLink;
    };

    template <class CommandClass, class ...Args>
    inline void CommandList::Enqueue(Args... args)
    {
        const size_t commandSize = sizeof(CommandClass);

        RenderCommandBase* command = reinterpret_cast<RenderCommandBase*>(myData + commandCursor);
        commandCursor += commandSize;
        ::new(command) CommandClass(std::forward<Args>(args)...);
        *myLink = command;
        myLink = &command->next;
    }
}