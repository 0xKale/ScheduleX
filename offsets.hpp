#pragma once
#include <Windows.h>
#include <cstdint>

namespace offsets
{
    inline uintptr_t base = (uintptr_t)GetModuleHandle(NULL);
    inline uintptr_t GameAssembly = 0;

    namespace localplayer
    {
        inline uintptr_t SetfieldOfView = 0x2C841A0; // FOV - UnityEngine.Camera$$set_fieldOfVie
        inline uintptr_t GetStackLimit = 0x997CC0;// Stack Limit - ScheduleOne.ItemFramework.ItemInstance$$get_StackLimit
		inline uintptr_t CanTakeDamage = 0x66485; // Can Take Damage - ScheduleOne.PlayerScripts.Health.PlayerHealth$$get_CanTakeDamage // dont give godmode
		inline uintptr_t RVA_RpcTakeDamage = 0x663110; // Set Can Take Damage - ScheduleOne.PlayerScripts.Health.PlayerHealth$$set_CanTakeDamage
    }
    namespace debug
    {
        inline uintptr_t DebugValue = 0xAADD90;
    }
    namespace unity
    {
		inline uintptr_t SetLockState = 0x2CA5710; // Cursor Lock - UnityEngine.Cursor$$set_lockState
		inline uintptr_t SetVisible = 0x2CA5750; // Cursor Visible - UnityEngine.Cursor$$set_visible
        inline uintptr_t WorldToScreenPoint = 0x2C82EF0; // UnityEngine.Camera::WorldToScreenPoint
        inline uintptr_t GetTransform = 0x2CBA530; // Player Transform - UnityEngine.Component$$get_transform
        inline uintptr_t GetPosition = 0x2CCEAD0; // Transform Position - UnityEngine.Transform$$get_position
		inline uintptr_t GetName = 0x2CC20E0; // GameObject Name - UnityEngine.GameObject$$get_name
    }
    namespace casino
    {
		inline uintptr_t RVA_GetRandomSymbol = 0x7EE610; // Get Random Symbol - ScheduleOne.Casino.SlotMachine.SlotMachineReel$$GetRandomSymbol
		inline uintptr_t RVA_GetCurrentBet = 0x7F0870; // Get Current Bet - ScheduleOne.Casino.SlotMachine.SlotMachineController$$get_CurrentBet
    }
    namespace player
    {
		inline uintptr_t PlayerUpdate = 0x63FE10; // Player Update - Player.PlayerModel$$Update


		
        inline uintptr_t StaticPlayerList = 0x20;// Player List offset
	}
    namespace npc
    {
		inline uintptr_t MovementUpdate = 0x7254D0; // NPC Movement Update - NPC.NPCModel$$MovementUpdate
    }
}