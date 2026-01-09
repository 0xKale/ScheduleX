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
		inline uintptr_t GrassUpdate = 0x7B4F40; // StylizedGrassDemo_PlayerController$$Update
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
        inline uintptr_t GetRotation = 0x2CCEC40; // get rotation - UnityEngine_Transform$$get_rotation
    }
    namespace casino
    {
		inline uintptr_t RVA_GetRandomSymbol = 0x7EE610; // Get Random Symbol - ScheduleOne.Casino.SlotMachine.SlotMachineReel$$GetRandomSymbol
		inline uintptr_t RVA_GetCurrentBet = 0x7F0870; // Get Current Bet - ScheduleOne.Casino.SlotMachine.SlotMachineController$$get_CurrentBet
    }
    namespace equippable {
        inline uintptr_t TrashGrabberGetCapacity = 0x8B4AD0; // ScheduleOne.Equipping.Equippable.TrashGrabber$$GetCapacity
    }
    namespace player
    {
        inline uintptr_t PlayerModelUpdate = 0x63FE10; // Player Update - Player.PlayerModel$$Update
        inline uintptr_t StaticPlayerList = 0x20;// Player List offset

        inline uintptr_t PlayerMovementUpdate = 0x66A720;
        inline uintptr_t TakeDamage = 0x6F8CA0;

        // VERIFIED OFFSETS
        inline uintptr_t moveSpeed = 0x38;       // Multiplier
        inline uintptr_t verticalVelocity = 0x9C; // The "Real" Jump/Gravity
        inline uintptr_t isGrounded = 0xC8;       // Infinite Jump flag
        inline uintptr_t stamina = 0x54;          // Stamina value

        // COMBAT / SURVIVAL
        inline uintptr_t RVA_TakeDamage = 0x6F8CA0;
	}
    namespace atm
    {
		inline uintptr_t GetRelevantBalance = 0x973AE0; // ATM Get Relevant Balance - ScheduleOne_UI_ATM_ATMInterface$$get_relevantBalance
        inline uintptr_t WithdrawButtonPressed = 0x973820; // ATM Withdraw Button Pressed - ScheduleOne_UI_ATM_ATMInterface$$WithdrawButtonPressed
		inline uintptr_t ProcessTransaction = 0x972330; // ATM Process Transaction - ScheduleOne_UI_ATM_ATMInterface$$ProcessTransaction
		inline uintptr_t GetAmountFromIndex = 0x971E90; // ATM Get Amount From Index - ScheduleOne_UI_ATM_ATMInterface$$GetAmountFromIndex
		inline uintptr_t GetRemainingAllowedDeposit = 0x973BC0; // ATM Get Remaining Allowed Deposit - ScheduleOne_UI_ATM_ATMInterface$$get_remainingAllowedDeposit
    } 
    namespace dealer
    {
		inline uintptr_t DealerPriceMultiplier = 0x6D40A0; // Dealer Price Multiplier - ScheduleOne.Economy.Dealer$$GetPriceMultiplier
    }
    namespace item
    {
		inline uintptr_t ItemGetValue = 0x70E5C0;// Item Get Value - ScheduleOne.Items.Item$$get_Value
    }
    namespace npc
    {
		inline uintptr_t MovementUpdate = 0x7254D0; // NPC Movement Update - NPC.NPCModel$$MovementUpdate
		inline uintptr_t AddCash = 0x704AC0; // NPC Add Cash - NPC.NPCModel$$AddCash
    }
    namespace world
    {
        inline uintptr_t GetTempMultiplier = 0xA3FA20; //ScheduleOne.Growing.GrowContainer$$GetTemperatureGrowthMultiplier
    }
    namespace skating {
        // Class: ScheduleOne.Skating.SkateboardEffects
        // Function: FixedUpdate
        // RVA: 0xAC2CA0
        inline uintptr_t EffectsFixedUpdate = 0xAC2CA0; // ScheduleOne_Skating_SkateboardEffects$$FixedUpdate

        // Field: private Skateboard skateboard; // 0x20
        inline uintptr_t boardInstance = 0x20;

        // --- SKATEBOARD CLASS OFFSETS ---
        // Class: ScheduleOne.Skating.Skateboard
        inline uintptr_t currentSpeed = 0x118; // float
        inline uintptr_t jumpCharge = 0x120; // float
        inline uintptr_t turnForce = 0x188; // float
        inline uintptr_t turnSpeedBoost = 0x194; // float
        inline uintptr_t gravity = 0x1A0; // float
        inline uintptr_t brakeForce = 0x1A4; // float
    }
}