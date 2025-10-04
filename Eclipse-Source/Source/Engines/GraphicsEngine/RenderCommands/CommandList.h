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
        void Init();

        template <class CommandClass, class ...Args>
        void Enqueue(Args... args);

        void Enqueue(const std::function<void()>& aLambda);

        void Execute();
        void Reset();

    private:
        bool hasCommands = false;

        uint8_t* myData = nullptr;
        size_t commandCursor = 0;

        RenderCommandBase* myRoot;
        RenderCommandBase** myLink;
    };

    template <class CommandClass, class ...Args>
    inline void CommandList::Enqueue(Args... args)
    {
        hasCommands = true;
        const size_t commandSize = sizeof(CommandClass);

        RenderCommandBase* command = reinterpret_cast<RenderCommandBase*>(myData + commandCursor);
        commandCursor += commandSize;
        ::new(command) CommandClass(std::forward<Args>(args)...);
        *myLink = command;
        myLink = &command->next;
    }

    class CommandListManager
    {
    public:
        static CommandList& GetSpriteCommandList() { return SpriteCommandList; }
        static CommandList& GetDebugDrawCommandList() { return DebugDrawCommandList; }

        static void ExecuteAllCommandLists()
        {
            SpriteCommandList.Execute();
            DebugDrawCommandList.Execute();
        }

        static void InitAllCommandLists()
        {
            SpriteCommandList.Init();
            DebugDrawCommandList.Init();
        }

        static void ResetAllCommandLists()
        {
            SpriteCommandList.Reset();
            DebugDrawCommandList.Reset();
        }

    private:
        static inline CommandList SpriteCommandList;
        static inline CommandList DebugDrawCommandList;
    };
}