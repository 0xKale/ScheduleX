#pragma once
#include "includes.h"
#include "vars.hpp"
#include "offsets.hpp"

namespace hooks
{
    inline float GetTargetFOV(float originalGameFov)
    {
        if (vars::bCustomFieldOfView)
            return vars::fFieldOfView;

        return originalGameFov; 
    }
    typedef void(__fastcall* tSetfieldOfView)(void* CameraMain, float fov);
    inline tSetfieldOfView oSetfieldOfView = nullptr;

    inline void __fastcall hkSetfieldOfView(void* CameraMain, float fov)
    {
        if (!CameraMain)
            return;
        float finalFov = GetTargetFOV(fov);
        oSetfieldOfView(CameraMain, finalFov);
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
    }
}