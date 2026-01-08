#pragma once
#include <Windows.h>
#include <cstdint>

namespace offsets
{
    inline uintptr_t base = (uintptr_t)GetModuleHandle(NULL);
    inline uintptr_t GameAssembly = 0;

    namespace localplayer
    {
        inline uintptr_t SetfieldOfView = 0x2C841A0;
        inline uintptr_t GetStackLimit = 0x997CC0;
    }
    namespace debug
    {
        inline uintptr_t DebugValue = 0xAADD90;
    }
    namespace unity
    {
        inline uintptr_t SetLockState = 0x2CA5710;
        inline uintptr_t SetVisible = 0x2CA5750;
    }
}