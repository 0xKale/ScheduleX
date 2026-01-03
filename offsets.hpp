#pragma once
#include <Windows.h>
#include <cstdint>

namespace offsets
{
    inline uintptr_t base = (uintptr_t)GetModuleHandle(NULL);
    inline uintptr_t GameAssembly = 0;

    namespace localplayer
    {
        inline uintptr_t SetfieldOfView = 0x2C841A0; // UnityEngine.Camera$$set_fieldOfView
        inline uintptr_t GetStackLimit = 0x997CC0; // ScheduleOne.ItemFramework.ItemInstance$$get_StackLimit
    }
}