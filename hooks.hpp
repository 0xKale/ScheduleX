#pragma once
#include "includes.h"
#include <iostream>
#include <iomanip>
#include <map>

namespace hooks
{
    // unity
    typedef void(__fastcall* tSetLockState)(int value, void* method);
    inline tSetLockState oSetLockState = nullptr;

    inline void __fastcall hkSetLockState(int value, void* method)
    {
        vars::iLastGameLockState = value;
        if (vars::bShowMenu) {
            return oSetLockState(0, method); // force unlock
        }
        return oSetLockState(value, method);
    }

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

    // il2cpp internals
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

    // local player
    typedef void(__fastcall* tSetfieldOfView)(void* CameraMain, float fov);
    inline tSetfieldOfView oSetfieldOfView = nullptr;

    inline void __fastcall hkSetfieldOfView(void* CameraMain, float fov)
    {
        if (CameraMain) {
            vars::pMainCamera = CameraMain; // store camera for w2s
        }

        if (!CameraMain) return;
        return oSetfieldOfView(CameraMain, vars::bCustomFieldOfView ? vars::fFieldOfView : fov);
    }

    typedef void(__fastcall* tSetBalance)(void* __this, float balance);
    inline tSetBalance oSetBalance = nullptr;

    inline void __fastcall hkSetBalance(void* __this, float balance) {
        if (__this) vars::pCashInstance = __this; // capture instance

        if (vars::bCustomBalance) {
            return oSetBalance(__this, vars::fTargetCash); //custom value
        }
        return oSetBalance(__this, balance);
    }

    // bank hook
    typedef void(__fastcall* tSetBankBalance)(void* __this, float balance);
    inline tSetBankBalance oSetBankBalance = nullptr;

    inline void __fastcall hkSetBankBalance(void* __this, float balance) {
        if (__this) {
            vars::pBankInstance = __this; // capture object
        }

        if (vars::bCustomBalance) {
            return oSetBankBalance(__this, vars::fTargetBank);
        }

        return oSetBankBalance(__this, balance);
    }

    typedef int(__fastcall* tGetStackLimit)(void* __this);
    inline tGetStackLimit oGetStackLimit = nullptr;

    inline int __fastcall hkGetStackLimit(void* __this)
    {
        return vars::bCustomStackLimit ? vars::iStackLimit : oGetStackLimit(__this);
    }

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

    // casino
    typedef int32_t(*tGetRandomSymbol)(void* method);
    tGetRandomSymbol o_GetRandomSymbol = nullptr;

    int32_t hk_GetRandomSymbol(void* method)
    {
        if (vars::bAlwaysJackpot) {
            return 5;
        }
        return o_GetRandomSymbol(method);
    }

    typedef int32_t(*tGetCurrentBetAmount)(void* instance, void* method);
    tGetCurrentBetAmount o_GetCurrentBetAmount = nullptr;

    int32_t hk_GetCurrentBetAmount(void* instance, void* method)
    {
        if (vars::bCustomBet) {
            return vars::iBetAmount;
        }
        return o_GetCurrentBetAmount(instance, method);
    }

    // equippable
    typedef int32_t(*tGetCapacity)(void* instance, void* method);
    inline tGetCapacity oGetCapacity = nullptr;

    inline int32_t hkGetCapacity(void* instance, void* method) {
        if (vars::bBetterTrashGrabber) {
            return vars::iTrashGrabberCapacityAmount;
        }
        return oGetCapacity(instance, method);
    }

    // shop
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

    // movement
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

                if (GetAsyncKeyState(VK_SPACE) & 1)
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

    typedef void(__fastcall* tSkateEffectsUpdate)(void* __this);
    inline tSkateEffectsUpdate oSkateEffectsUpdate = nullptr;

    inline void __fastcall hkSkateEffectsUpdate(void* __this)
    {
        if (oSkateEffectsUpdate) oSkateEffectsUpdate(__this);
        if (!__this || (uintptr_t)__this < 0x10000) return;
        if (vars::bModifySkate)
        {
            uintptr_t board = *(uintptr_t*)((uintptr_t)__this + offsets::skating::boardInstance);

            if (board > 0x10000)
            {
                *(float*)(board + offsets::skating::topSpeed) = vars::fSkateTopSpeed;
                *(float*)(board + offsets::skating::reverseTopSpeed) = vars::fSkateReverseSpeed;
                *(float*)(board + offsets::skating::pushForce) = vars::fSkatePushForce;
                *(float*)(board + offsets::skating::pushDuration) = vars::fSkatePushDur;
                *(float*)(board + offsets::skating::turnForce) = vars::fSkateTurnForce;
                *(float*)(board + offsets::skating::turnChangeRate) = vars::fSkateResponse;
                *(float*)(board + offsets::skating::turnReturnRate) = vars::fSkateSnappiness;
                *(float*)(board + offsets::skating::turnSpeedBoost) = vars::fSkateBoost;
                *(float*)(board + offsets::skating::rotationClamp) = vars::fSkateSpinLimit;
                *(float*)(board + offsets::skating::gravity) = vars::fSkateGravity;
                *(float*)(board + offsets::skating::brakeForce) = vars::fSkateBrake;
                *(float*)(board + offsets::skating::longFriction) = vars::fSkateLongFriction;
                *(float*)(board + offsets::skating::latFriction) = vars::fSkateLatFriction;
                *(bool*)(board + offsets::skating::slowOnTerrain) = vars::bSkateSlowOnGrass;
                *(float*)(board + offsets::skating::jumpForce) = vars::fSkateJumpBase;
                *(float*)(board + offsets::skating::jumpFwdBoost) = vars::fSkateJumpFwd;

                float currentCharge = *(float*)(board + offsets::skating::jumpCharge);
                if (currentCharge > 0.01f && vars::fSkateJumpMult > 1.0f) {
                    *(float*)(board + offsets::skating::jumpCharge) = vars::fSkateJumpMult;
                }

                *(bool*)(board + offsets::skating::airMoveEnabled) = vars::bSkateAirControl;
                if (vars::bSkateAirControl) {
                    *(float*)(board + offsets::skating::airMoveForce) = vars::fSkateAirForce;
                }

                if (vars::bHoverMode) {
                    *(float*)(board + offsets::skating::hoverHeight) = vars::fHoverHeight;
                    *(float*)(board + offsets::skating::hoverRayLen) = vars::fHoverHeight + 1.5f;
                    *(float*)(board + offsets::skating::hoverForce) = 50.0f;
                    *(float*)(board + offsets::skating::latFriction) = 0.05f;
                    *(float*)(board + offsets::skating::brakeForce) = 0.0f;
                }
            }
        }
    }

    // world
    typedef float(__fastcall* tGetTempMult)(void* __this, void* method);
    inline tGetTempMult oGetTempMult = nullptr;

    inline float __fastcall hkGetTempMult(void* __this, void* method)
    {
        if (vars::bModifyWorld && vars::fGrowMultiplier > 1.0f)
        {
            return vars::fGrowMultiplier;
        }
        return oGetTempMult(__this, method);
    }

    // police
    typedef void(__fastcall* tOfficerUpdate)(void* __this, void* method);
    inline tOfficerUpdate oOfficerUpdate = nullptr;
    inline void __fastcall hkOfficerUpdate(void* __this, void* method) {
        if (vars::bFreezePolice) return;
        if (oOfficerUpdate) oOfficerUpdate(__this, method);
    }

    typedef bool(__fastcall* tCanInvestigatePlayer)(void* __this, void* player, void* method);
    inline tCanInvestigatePlayer oCanInvestigatePlayer = nullptr;
    inline bool __fastcall hkCanInvestigatePlayer(void* __this, void* player, void* method) {
        if (vars::bNoSearch) return false;
        if (oCanInvestigatePlayer) return oCanInvestigatePlayer(__this, player, method);
        return false;
    }

    typedef bool(__fastcall* tCanInvestigate)(void* __this, void* method);
    inline tCanInvestigate oCanInvestigate = nullptr;
    inline bool __fastcall hkCanInvestigate(void* __this, void* method) {
        if (vars::bPoliceIgnoreAll) return false;
        if (oCanInvestigate) return oCanInvestigate(__this, method);
        return true;
    }

    typedef void(__fastcall* tUpdateLethal)(void* __this);
    inline tUpdateLethal oUpdateLethal = nullptr;
    inline void __fastcall hkUpdateLethal(void* __this) {
        if (vars::bDisarmPolice || vars::bPacifistPolice) return;
        if (oUpdateLethal) oUpdateLethal(__this);
    }

    typedef void(__fastcall* tUpdateNonLethal)(void* __this);
    inline tUpdateNonLethal oUpdateNonLethal = nullptr;
    inline void __fastcall hkUpdateNonLethal(void* __this) {
        if (vars::bDisarmPolice || vars::bPacifistPolice) return;
        if (oUpdateNonLethal) oUpdateNonLethal(__this);
    }

    typedef void(__fastcall* tUpdateArrest)(void* __this);
    inline tUpdateArrest oUpdateArrest = nullptr;
    inline void __fastcall hkUpdateArrest(void* __this) {
        if (vars::bAntiJail || vars::bNoSearch) return;
        if (oUpdateArrest) oUpdateArrest(__this);
    }

    // npc
    typedef void* (__fastcall* tGetName)(void* object);
    inline tGetName oGetName = nullptr;

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
        return oNpcUpdate(__this);
    }

    // player esp
    typedef void(__fastcall* tPlayerUpdate)(void* __this, void* method);
    inline tPlayerUpdate oPlayerUpdate = nullptr;

    inline void __fastcall hkPlayerUpdate(void* __this, void* method) {
        if (__this) {
            void* klass = *(void**)__this;
            if (klass) {
                void* static_fields = *(void**)((uintptr_t)klass + 0xB8);
                if (static_fields) {
                    vars::pPlayerList = *(void**)((uintptr_t)static_fields + offsets::player::StaticPlayerList);
                }
            }
        }
        return oPlayerUpdate(__this, method);
    }

    // projection helpers
    typedef Vector3(__fastcall* tWorldToScreenPoint)(void* camera, Vector3 pos, int eye);
    inline tWorldToScreenPoint oWorldToScreenPoint = nullptr;

    inline bool GetScreenPos(Vector3 worldPos, struct ImVec2& screenPos)
    {
        if (!vars::pMainCamera || !oWorldToScreenPoint) return false;

        Vector3 result = oWorldToScreenPoint(vars::pMainCamera, worldPos, 2);

        if (result.z <= 0.f) return false;

        screenPos.x = result.x;
        screenPos.y = ImGui::GetIO().DisplaySize.y - result.y;
        return true;
    }

    typedef Quaternion(__fastcall* tGetRotation)(void* transform);
    inline tGetRotation oGetRotation = nullptr;

    // menu helpers
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
    }

    inline void Init()
    {
        while (offsets::GameAssembly == 0)
        {
            offsets::GameAssembly = (uintptr_t)GetModuleHandle("GameAssembly.dll");
            Sleep(100);
        }

        HMODULE hGameAssembly = GetModuleHandle("GameAssembly.dll");
        il2cpp_domain_get = (t_il2cpp_domain_get)GetProcAddress(hGameAssembly, "il2cpp_domain_get");
        il2cpp_thread_attach = (t_il2cpp_thread_attach)GetProcAddress(hGameAssembly, "il2cpp_thread_attach");

        MH_Initialize();

        // unity camera helpers
        oWorldToScreenPoint = (tWorldToScreenPoint)(offsets::GameAssembly + offsets::unity::WorldToScreenPoint);
        oGetTransform = (tGetTransform)(offsets::GameAssembly + offsets::unity::GetTransform);
        oGetPosition = (tGetPosition)(offsets::GameAssembly + offsets::unity::GetPosition);
        oGetName = (tGetName)(offsets::GameAssembly + offsets::unity::GetName);
        oGetRotation = (tGetRotation)(offsets::GameAssembly + offsets::unity::GetRotation);

#define CREATE_HOOK(addr, hook, orig) \
            if (MH_CreateHook((void*)(offsets::GameAssembly + addr), &hook, (LPVOID*)&orig) == MH_OK) \
                MH_EnableHook((void*)(offsets::GameAssembly + addr));

        // unity
        CREATE_HOOK(offsets::unity::SetLockState, hkSetLockState, oSetLockState);
        CREATE_HOOK(offsets::unity::SetVisible, hkSetVisible, oSetVisible);

        // debug
        CREATE_HOOK(offsets::debug::DebugValue, hkDebugValue, oDebugValue);

        // local player
        CREATE_HOOK(offsets::localplayer::SetfieldOfView, hkSetfieldOfView, oSetfieldOfView);
        CREATE_HOOK(offsets::localplayer::GetStackLimit, hkGetStackLimit, oGetStackLimit);
        CREATE_HOOK(offsets::localplayer::CanTakeDamage, hk_get_CanTakeDamage, o_get_CanTakeDamage);
        CREATE_HOOK(offsets::localplayer::RpcTakeDamage, hk_RpcTakeDamage, o_RpcTakeDamage);
        CREATE_HOOK(offsets::ItemFramework::SetBalance, hkSetBalance, oSetBalance);


        // equippable
        CREATE_HOOK(offsets::equippable::TrashGrabberGetCapacity, hkGetCapacity, oGetCapacity);

        // shop
        CREATE_HOOK(offsets::item::ItemGetValue, hkGetItemValue, oGetItemValue);
        CREATE_HOOK(offsets::dealer::DealerPriceMultiplier, hkGetPriceMultiplier, oGetPriceMultiplier);

        // movement
        CREATE_HOOK(offsets::player::PlayerMovementUpdate, hkPlayerMovementUpdate, oPlayerMovementUpdate);
        CREATE_HOOK(offsets::skating::EffectsFixedUpdate, hkSkateEffectsUpdate, oSkateEffectsUpdate);

        // world
        CREATE_HOOK(offsets::world::GetTempMultiplier, hkGetTempMult, oGetTempMult);

        // police
        CREATE_HOOK(offsets::police::OfficerUpdate, hkOfficerUpdate, oOfficerUpdate);
        CREATE_HOOK(offsets::police::CanInvestigatePlayer, hkCanInvestigatePlayer, oCanInvestigatePlayer);
        CREATE_HOOK(offsets::police::CanInvestigate, hkCanInvestigate, oCanInvestigate);
        CREATE_HOOK(offsets::police::UpdateLethalBehaviour, hkUpdateLethal, oUpdateLethal);
        CREATE_HOOK(offsets::police::UpdateNonLethalBehaviour, hkUpdateNonLethal, oUpdateNonLethal);
        CREATE_HOOK(offsets::police::UpdateArrestBehaviour, hkUpdateArrest, oUpdateArrest);

        // npc
        CREATE_HOOK(offsets::npc::MovementUpdate, hkNpcUpdate, oNpcUpdate);

        // player esp
        CREATE_HOOK(offsets::player::PlayerUpdate, hkPlayerUpdate, oPlayerUpdate);

		// economy 
        CREATE_HOOK(offsets::casino::GetRandomSymbol, hk_GetRandomSymbol, o_GetRandomSymbol);
        CREATE_HOOK(offsets::casino::GetCurrentBet, hk_GetCurrentBetAmount, o_GetCurrentBetAmount);
        CREATE_HOOK(offsets::ItemFramework::SetBalance, hkSetBalance, oSetBalance);
        CREATE_HOOK(offsets::ItemFramework::SetBankBalance, hkSetBankBalance, oSetBankBalance);

#undef CREATE_HOOK
    }
}