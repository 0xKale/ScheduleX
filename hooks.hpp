#pragma once
#include "includes.h"

namespace hooks
{
    // --- Cursor Logic ---
    typedef void(__fastcall* tSetLockState)(int value, void* method);
    inline tSetLockState oSetLockState = nullptr;

    inline void __fastcall hkSetLockState(int value, void* method)
    {
        vars::iLastGameLockState = value; // Capture what the game WANTS to do

        if (vars::bShowMenu) {
            return oSetLockState(0, method); // Force Unlock (0 = None)
        }
        return oSetLockState(value, method); // Allow normal behavior
    }

    typedef void(__fastcall* tSetVisible)(bool value, void* method);
    inline tSetVisible oSetVisible = nullptr;

    inline void __fastcall hkSetVisible(bool value, void* method)
    {
        vars::bLastCursorVisible = value;
        if (vars::bShowMenu) {
            return oSetVisible(true, method); // Force Visible
        }
        return oSetVisible(value, method);
    }

    // --- Helper to Force Cursor State Immediately ---
    inline void ForceUnlock()
    {
        // Call this when opening the menu to apply settings INSTANTLY
        if (oSetLockState) oSetLockState(0, nullptr);
        if (oSetVisible) oSetVisible(true, nullptr);
    }

    inline void CursorHandler() // Restore function
    {
        if (oSetLockState) oSetLockState(vars::iLastGameLockState, nullptr);
        if (oSetVisible) oSetVisible(vars::bLastCursorVisible, nullptr);
    }

    // --- Game Logic Hooks ---
    typedef bool(__fastcall* tDebugValue)(void* __this);
    inline tDebugValue oDebugValue = nullptr;

    inline bool __fastcall hkDebugValue(void* __this)
    {
        if (!__this) return false;
        return vars::bDebug ? true : oDebugValue(__this);
    }

    typedef void(__fastcall* tSetfieldOfView)(void* CameraMain, float fov);
    inline tSetfieldOfView oSetfieldOfView = nullptr;

    inline void __fastcall hkSetfieldOfView(void* CameraMain, float fov)
    {
        if (!CameraMain) return;
        return oSetfieldOfView(CameraMain, vars::bCustomFieldOfView ? vars::fFieldOfView : fov);
    }

    typedef int(__fastcall* tGetStackLimit)(void* __this);
    inline tGetStackLimit oGetStackLimit = nullptr;

    inline int __fastcall hkGetStackLimit(void* __this)
    {
        return vars::bCustomStackLimit ? vars::iStackLimit : oGetStackLimit(__this);
    }

    inline void Init()
    {
        while (offsets::GameAssembly == 0)
        {
            offsets::GameAssembly = (uintptr_t)GetModuleHandle("GameAssembly.dll");
            Sleep(100);
        }

        MH_Initialize();

        // Helper macro to clean up hook creation
#define CREATE_HOOK(addr, hook, orig) \
            if (MH_CreateHook((void*)(offsets::GameAssembly + addr), &hook, (LPVOID*)&orig) == MH_OK) \
                MH_EnableHook((void*)(offsets::GameAssembly + addr));

        CREATE_HOOK(offsets::unity::SetLockState, hkSetLockState, oSetLockState);
        CREATE_HOOK(offsets::unity::SetVisible, hkSetVisible, oSetVisible);
        CREATE_HOOK(offsets::debug::DebugValue, hkDebugValue, oDebugValue);
        CREATE_HOOK(offsets::localplayer::SetfieldOfView, hkSetfieldOfView, oSetfieldOfView);
        CREATE_HOOK(offsets::localplayer::GetStackLimit, hkGetStackLimit, oGetStackLimit);
    }
}