#pragma once
#include "includes.h"
#include "vars.hpp"
#include "offsets.hpp"

namespace hooks
{
    typedef void(__fastcall* tSetfieldOfView)(void* CameraMain, float fov);
    inline tSetfieldOfView oSetfieldOfView = nullptr;

    inline void __fastcall hkSetfieldOfView(void* CameraMain, float fov)
    {
        if (!CameraMain) return;

        if (vars::bCustomFieldOfView)
            return oSetfieldOfView(CameraMain, vars::fFieldOfView);

        return oSetfieldOfView(CameraMain, fov);
    }

    typedef int(__fastcall* tGetStackLimit)(void* __this);
    inline tGetStackLimit oGetStackLimit = nullptr;
    inline int __fastcall hkGetStackLimit(void* __this)
    {
        if (vars::bCustomStackLimit)
            return vars::iStackLimit;
        return oGetStackLimit(__this);
    }

    inline void Init()
    {
        while (offsets::GameAssembly == 0)
        {
            offsets::GameAssembly = (uintptr_t)GetModuleHandle("GameAssembly.dll");
            Sleep(100);
        }

        MH_STATUS status = MH_Initialize();
        if (status != MH_OK && status != MH_ERROR_ALREADY_INITIALIZED)
            return;

        uintptr_t fovAddress = offsets::GameAssembly + offsets::localplayer::SetfieldOfView;
        if (MH_CreateHook((void*)fovAddress, &hkSetfieldOfView, (LPVOID*)&oSetfieldOfView) == MH_OK)
        {
            MH_EnableHook((void*)fovAddress);
        }
        uintptr_t stackAddr = offsets::GameAssembly + offsets::localplayer::GetStackLimit;
        if (MH_CreateHook((void*)stackAddr, &hkGetStackLimit, (LPVOID*)&oGetStackLimit) == MH_OK)
        {
            MH_EnableHook((void*)stackAddr);
        }
    }
}