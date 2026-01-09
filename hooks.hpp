#pragma once
#include "includes.h"
#include <iostream>
#include <iomanip>
#include <map>

namespace hooks
{


    // cursor shit
    typedef void(__fastcall* tSetLockState)(int value, void* method);
    inline tSetLockState oSetLockState = nullptr;

    inline void __fastcall hkSetLockState(int value, void* method)
    {
        vars::iLastGameLockState = value;
        if (vars::bShowMenu) {
            return oSetLockState(0, method); // Force Unlock
        }
        return oSetLockState(value, method);
    }

    // cursor visible
    typedef void(__fastcall* tSetVisible)(bool value, void* method);
    inline tSetVisible oSetVisible = nullptr;

    inline void __fastcall hkSetVisible(bool value, void* method)
    {
        if (!vars::bShowMenu) {
            vars::bLastCursorVisible = value;
        }
        if (vars::bShowMenu) {
            return oSetVisible(true, method);
        }
        return oSetVisible(value, method);
    }
    // il2cpp threading - getname fix
    typedef void* (*t_il2cpp_domain_get)();
    inline t_il2cpp_domain_get il2cpp_domain_get = nullptr;

    typedef void* (*t_il2cpp_thread_attach)(void* domain);
    inline t_il2cpp_thread_attach il2cpp_thread_attach = nullptr;

    // debug
    typedef bool(__fastcall* tDebugValue)(void* __this);
    inline tDebugValue oDebugValue = nullptr;

    inline bool __fastcall hkDebugValue(void* __this)
    {
        if (!__this) return false;
        return vars::bDebug ? true : oDebugValue(__this);
    }

    // fov
    typedef void(__fastcall* tSetfieldOfView)(void* CameraMain, float fov);
    inline tSetfieldOfView oSetfieldOfView = nullptr;

    inline void __fastcall hkSetfieldOfView(void* CameraMain, float fov)
    {
        if (CameraMain) {
            vars::pMainCamera = CameraMain; // add camera to vars for w2s use
        }

        if (!CameraMain) return;
        return oSetfieldOfView(CameraMain, vars::bCustomFieldOfView ? vars::fFieldOfView : fov);
    }

    // stack limit
    typedef int(__fastcall* tGetStackLimit)(void* __this);
    inline tGetStackLimit oGetStackLimit = nullptr;

    inline int __fastcall hkGetStackLimit(void* __this)
    {
        return vars::bCustomStackLimit ? vars::iStackLimit : oGetStackLimit(__this);
    }

    // can take damage - godmode
    typedef bool (*tGet_CanTakeDamage)(void* instance, void* method);
    tGet_CanTakeDamage o_get_CanTakeDamage = nullptr;

    bool hk_get_CanTakeDamage(void* instance, void* method) {
        if (vars::bCanTakeDamage) {
            return false;
        }
        return o_get_CanTakeDamage(instance, method);
    }

    typedef void (*tRpcTakeDamage)(void* instance, float damage, bool flinch, bool playBloodMist, void* method);
    tRpcTakeDamage o_RpcTakeDamage = nullptr;

    void hk_RpcTakeDamage(void* instance, float damage, bool flinch, bool playBloodMist, void* method)
    {
        if (vars::bCanTakeDamage) {
            damage = 0.0f;
        }
        o_RpcTakeDamage(instance, damage, flinch, playBloodMist, method);
    }

    //casino
    // jackpot
    typedef int32_t(*tGetRandomSymbol)(void* method);
    tGetRandomSymbol o_GetRandomSymbol = nullptr;

    int32_t hk_GetRandomSymbol(void* method)
    {
        if (vars::bAlwaysJackpot) {
            return 5;
        }
        return o_GetRandomSymbol(method);
    }

    // custom bet
    typedef int32_t(*tGetCurrentBetAmount)(void* instance, void* method);
    tGetCurrentBetAmount o_GetCurrentBetAmount = nullptr;

    int32_t hk_GetCurrentBetAmount(void* instance, void* method)
    {
        if (vars::bCustomBet) {
            return vars::iBetAmount;
        }
        return o_GetCurrentBetAmount(instance, method);
    }

    // trash grabber capacity
    typedef int32_t(*tGetCapacity)(void* instance, void* method);
    inline tGetCapacity oGetCapacity = nullptr;

    inline int32_t hkGetCapacity(void* instance, void* method) {
        if (vars::bBetterTrashGrabber) {
            return vars::iTrashGrabberCapacityAmount;
        }
        return oGetCapacity(instance, method);
    }

    //player modifiers 
    typedef void(__fastcall* tPlayerMovementUpdate)(void* __this);
    inline tPlayerMovementUpdate oPlayerMovementUpdate = nullptr;

    inline void __fastcall hkPlayerMovementUpdate(void* __this)
    {
        if (oPlayerMovementUpdate) oPlayerMovementUpdate(__this);

        if (!__this || (uintptr_t)__this < 0x10000) return;

        uintptr_t base = (uintptr_t)__this;
        vars::pLocalPlayerController = base;

        __try {
            if (vars::bModifyMovement)
            {
                *(float*)(base + offsets::player::moveSpeed) = vars::fWalkSpeed;
                bool isGameGrounded = *(bool*)(base + offsets::player::isGrounded);

                if (GetAsyncKeyState(VK_SPACE) & 1) // On Tap
                {
                    if (vars::bInfiniteJump || isGameGrounded)
                    {
                        *(float*)(base + offsets::player::verticalVelocity) = vars::fJumpVelocity;
                    }
                }
                float currentVel = *(float*)(base + offsets::player::verticalVelocity);
                if (currentVel < -0.1f)
                {
                    *(float*)(base + offsets::player::verticalVelocity) = currentVel * vars::fGravityScale;
                }
            }
            if (vars::bModifyPhysics) {
                *(float*)(base + offsets::player::stamina) = 100.0f;
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {}
    }


    // self godmode
    typedef void(__fastcall* tTakeDamage)(void* __this, float damage, void* method);
    inline tTakeDamage oTakeDamage = nullptr;

    inline void __fastcall hkTakeDamage(void* __this, float damage, void* method)
    {
        if (vars::bGodMode) {
            return; 
        }
        return oTakeDamage(__this, damage, method);
    }


    typedef float (*tGetRelevantBalance)(void* __this, void* method);
    inline tGetRelevantBalance oGetRelevantBalance = nullptr;

    inline float hkGetRelevantBalance(void* __this, void* method) {
        if (vars::bATMWithdraw) {
			return vars::fATMWithdrawAmount; // override balance
        }
        return oGetRelevantBalance(__this, method);
    }

    typedef void (*tProcessTransaction)(void* __this, float amount, void* method);
    inline tProcessTransaction oProcessTransaction = nullptr;

    inline void hkProcessTransaction(void* __this, float amount, void* method) {
        if (vars::bATMWithdraw) {
            amount = vars::fATMWithdrawAmount;
        }
        return oProcessTransaction(__this, amount, method);
    }

    typedef float (*tGetAmountFromIndex)(void* __this, int index, void* method);
    inline tGetAmountFromIndex oGetAmountFromIndex = nullptr;

    inline float hkGetAmountFromIndex(void* __this, int index, void* method) {
        if (vars::bATMWithdraw) {
            return vars::fATMWithdrawAmount;
        }
        return oGetAmountFromIndex(__this, index, method);
    }

    typedef float (*tGetRemainingDeposit)(void* __this, void* method);
    inline tGetRemainingDeposit oGetRemainingDeposit = nullptr;

    inline float hkGetRemainingDeposit(void* __this, void* method) {
        if (vars::bATMWithdrawLimit) {
            return vars::fATMWithdrawLimit;
        }
        return oGetRemainingDeposit(__this, method);
    }

    typedef float (*tGetItemValue)(void* __this, void* method);
    inline tGetItemValue oGetItemValue = nullptr;

    inline float hkGetItemValue(void* __this, void* method) {
        if (vars::bCustomItemValue) {
            return vars::fItemValue;
        }
        return oGetItemValue(__this, method);
    }

    typedef float (*tGetPriceMultiplier)(void* __this, void* method);
    inline tGetPriceMultiplier oGetPriceMultiplier = nullptr;

    inline float hkGetPriceMultiplier(void* __this, void* method) {
        if (vars::bDealerPriceMultiplier) {
            return vars::fDealerMultiplier;
        }
        return oGetPriceMultiplier(__this, method);
    }

    // w2s
    typedef Vector3(__fastcall* tWorldToScreenPoint)(void* camera, Vector3 pos, int eye);
    inline tWorldToScreenPoint oWorldToScreenPoint = nullptr;

    inline bool GetScreenPos(Vector3 worldPos, struct ImVec2& screenPos)
    {
        if (!vars::pMainCamera || !oWorldToScreenPoint) return false;

        // 2 = Mono Eye (Standard)
        Vector3 result = oWorldToScreenPoint(vars::pMainCamera, worldPos, 2);

        // If Z < 0, object is behind camera
        if (result.z <= 0.f) return false;

        screenPos.x = result.x;
        screenPos.y = ImGui::GetIO().DisplaySize.y - result.y; // Flip Y for ImGui
        return true;
    }
    
    // get rotation for 3d boxes
    typedef Quaternion(__fastcall* tGetRotation)(void* transform);
    inline tGetRotation oGetRotation = nullptr;

    // player update ESP
    typedef void(__fastcall* tPlayerModelUpdate)(void* __this, void* method);
    inline tPlayerModelUpdate oPlayerModelUpdate = nullptr;

    inline void __fastcall hkPlayerModelUpdate(void* __this, void* method) {
        if (__this)
        {
            void* Class = *(void**)__this;
            if (Class)
            {
                // 0xB8 is standard for x64 Static Fields
                void* staticFields = *(void**)((uintptr_t)Class + 0xB8);
                if (staticFields) {
                    vars::pPlayerList = *(void**)((uintptr_t)staticFields + offsets::player::StaticPlayerList);
                }
            }
        }
        return oPlayerModelUpdate(__this, method);
    }


	// player update - to prevent updates when menu is open
    typedef void (*tGrassPlayerUpdate)(void* __this, void* method);
    inline tGrassPlayerUpdate oGrassPlayerUpdate = nullptr;

    inline void hkGrassPlayerUpdate(void* __this, void* method)
    {
        if (vars::bShowMenu) {
            return;
        }

        return oGrassPlayerUpdate(__this, method);
    }

	// get name for NPCs
    typedef void* (__fastcall* tGetName)(void* object);
    inline tGetName oGetName = nullptr;

	// npc update - to gather npc list
    typedef void* (__fastcall* tGetTransform)(void* component);
    inline tGetTransform oGetTransform = nullptr;

    typedef Vector3(__fastcall* tGetPosition)(void* transform);
    inline tGetPosition oGetPosition = nullptr;

    typedef void(__fastcall* tNpcUpdate)(void* __this);
    inline tNpcUpdate oNpcUpdate = nullptr;

    inline void __fastcall hkNpcUpdate(void* __this)
    {
        if (__this)
        {
            if (vars::vNpcList.empty())
            {
                vars::vNpcList.push_back(__this);
            }
            else
            {
                bool found = false;
                for (void* npc : vars::vNpcList)
                {
                    if (npc == __this)
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    vars::vNpcList.push_back(__this);
                }
            }
        }
        return oNpcUpdate(__this); // ts so ugly twin
    }

    inline void ForceUnlock()
    {
        if (oSetLockState) oSetLockState(0, nullptr);
        if (oSetVisible) oSetVisible(true, nullptr);
    }

    inline void CursorHandler()
    {
        if (oSetLockState)
            oSetLockState(vars::iLastGameLockState, nullptr);
        if (oSetVisible)
            oSetVisible(vars::bLastCursorVisible, nullptr);
        if (!vars::bShowMenu) {
            HWND hWnd = FindWindowA(NULL, "Schedule I");
            if (hWnd) {
                RECT rect;
                GetWindowRect(hWnd, &rect);
                ClipCursor(&rect);
            }
        }
        else {
            // IMPORTANT: When menu is OPEN, we must stop clipping so the mouse can move freely
            //ClipCursor(NULL);
        }
    }

    inline void Init()
    {
        while (offsets::GameAssembly == 0)
        {
            offsets::GameAssembly = (uintptr_t)GetModuleHandle("GameAssembly.dll");
            Sleep(100);
        }

		// il2cpp functions
        HMODULE hGameAssembly = GetModuleHandle("GameAssembly.dll");
        il2cpp_domain_get = (t_il2cpp_domain_get)GetProcAddress(hGameAssembly, "il2cpp_domain_get");
        il2cpp_thread_attach = (t_il2cpp_thread_attach)GetProcAddress(hGameAssembly, "il2cpp_thread_attach");

        MH_Initialize();

        // w2s hook setup
        uintptr_t w2sAddr = offsets::GameAssembly + offsets::unity::WorldToScreenPoint;
        oWorldToScreenPoint = (tWorldToScreenPoint)w2sAddr;

		oGetTransform = (tGetTransform)(offsets::GameAssembly + offsets::unity::GetTransform); // Player Transform
		oGetPosition = (tGetPosition)(offsets::GameAssembly + offsets::unity::GetPosition); // Transform Position
		oGetName = (tGetName)(offsets::GameAssembly + offsets::unity::GetName); // Get Name
        oGetRotation = (tGetRotation)(offsets::GameAssembly + offsets::unity::GetRotation); // get rotation

        // macro for qol 
        #define CREATE_HOOK(addr, hook, orig) \
            if (MH_CreateHook((void*)(offsets::GameAssembly + addr), &hook, (LPVOID*)&orig) == MH_OK) \
                MH_EnableHook((void*)(offsets::GameAssembly + addr));

        CREATE_HOOK(offsets::unity::SetLockState, hkSetLockState, oSetLockState);
        CREATE_HOOK(offsets::unity::SetVisible, hkSetVisible, oSetVisible);
        CREATE_HOOK(offsets::debug::DebugValue, hkDebugValue, oDebugValue);
        CREATE_HOOK(offsets::localplayer::SetfieldOfView, hkSetfieldOfView, oSetfieldOfView);
        CREATE_HOOK(offsets::localplayer::GetStackLimit, hkGetStackLimit, oGetStackLimit);
        CREATE_HOOK(offsets::player::PlayerModelUpdate, hkPlayerModelUpdate, oPlayerModelUpdate);
        CREATE_HOOK(offsets::npc::MovementUpdate, hkNpcUpdate, oNpcUpdate);
		CREATE_HOOK(offsets::localplayer::CanTakeDamage, hk_get_CanTakeDamage, o_get_CanTakeDamage); 
		CREATE_HOOK(offsets::localplayer::RVA_RpcTakeDamage, hk_RpcTakeDamage, o_RpcTakeDamage);
        CREATE_HOOK(offsets::casino::RVA_GetRandomSymbol, hk_GetRandomSymbol, o_GetRandomSymbol);
		CREATE_HOOK(offsets::casino::RVA_GetCurrentBet, hk_GetCurrentBetAmount, o_GetCurrentBetAmount);
		//CREATE_HOOK(offsets::localplayer::GrassUpdate, hkGrassPlayerUpdate, oGrassPlayerUpdate); // dont work to stop player moving when menu open
        CREATE_HOOK(offsets::equippable::TrashGrabberGetCapacity, hkGetCapacity, oGetCapacity);
		//CREATE_HOOK(offsets::atm::GetRelevantBalance, hkGetRelevantBalance, oGetRelevantBalance);
        //CREATE_HOOK(offsets::atm::ProcessTransaction, hkProcessTransaction, oProcessTransaction);
		//CREATE_HOOK(offsets::atm::GetAmountFromIndex, hkGetAmountFromIndex, oGetAmountFromIndex);
		//CREATE_HOOK(offsets::atm::GetRemainingAllowedDeposit, hkGetRemainingDeposit, oGetRemainingDeposit);
        CREATE_HOOK(offsets::item::ItemGetValue, hkGetItemValue, oGetItemValue);
		CREATE_HOOK(offsets::dealer::DealerPriceMultiplier, hkGetPriceMultiplier, oGetPriceMultiplier);
        CREATE_HOOK(offsets::player::PlayerMovementUpdate, hkPlayerMovementUpdate, oPlayerMovementUpdate);
		//CREATE_HOOK(offsets::player::TakeDamage, hkTakeDamage, oTakeDamage); // shitty

        


#undef CREATE_HOOK
    }
}