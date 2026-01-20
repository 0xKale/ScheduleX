#pragma once
#include <Windows.h>
#include <cstdint>

namespace offsets
{
    inline uintptr_t base = (uintptr_t)GetModuleHandleA("GameAssembly.dll");
    inline uintptr_t GameAssembly = 0;

    namespace localplayer
    {
        inline uintptr_t SetfieldOfView = 0x2C841A0; // FOV - UnityEngine.Camera$$set_fieldOfVie
        inline uintptr_t GetStackLimit = 0x997CC0;// Stack Limit - ScheduleOne.ItemFramework.ItemInstance$$get_StackLimit
		inline uintptr_t CanTakeDamage = 0x66485; // Can Take Damage - ScheduleOne.PlayerScripts.Health.PlayerHealth$$get_CanTakeDamage // dont give godmode
        inline uintptr_t RpcTakeDamage = 0x663110; // ScheduleOne.PlayerScripts.Health.PlayerHealth$$set_CanTakeDamage
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
		inline uintptr_t GetRandomSymbol = 0x7EE610; // Get Random Symbol - ScheduleOne.Casino.SlotMachine.SlotMachineReel$$GetRandomSymbol
		inline uintptr_t GetCurrentBet = 0x7F0870; // Get Current Bet - ScheduleOne.Casino.SlotMachine.SlotMachineController$$get_CurrentBet
    }
    namespace equippable {
        inline uintptr_t TrashGrabberGetCapacity = 0x8B4AD0; // ScheduleOne.Equipping.Equippable.TrashGrabber$$GetCapacity
    }
    namespace player
    {


        inline uintptr_t PlayerUpdate = 0x642620; // scheduleone.playerscripts.player$$update

        //offsets
        inline uintptr_t StaticPlayerList = 0x0; // public static list<player> players;
        inline uintptr_t ListItems = 0x10; // internal array buffer
        inline uintptr_t ListSize = 0x18; // current count
        inline uintptr_t ArrayStart = 0x20; // start of elements in array
        inline uintptr_t PointerStep = 0x8; // size of x64 pointer

        inline uintptr_t PlayerMovementUpdate = 0x66A720;
        inline uintptr_t TakeDamage = 0x6F8CA0;

        // VERIFIED OFFSETS
        inline uintptr_t moveSpeed = 0x38;       // Multiplier
        inline uintptr_t verticalVelocity = 0x9C; // The "Real" Jump/Gravity
        inline uintptr_t isGrounded = 0xC8;       // Infinite Jump flag
        inline uintptr_t stamina = 0x54;          // Stamina value
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
        inline uintptr_t CanSeeTarget = 0x7A9520;// ScheduleOne.NPCs.NPCAwareness$$CanSeeTarget 
    }
    namespace world
    {
        inline uintptr_t GetTempMultiplier = 0xA3FA20; //ScheduleOne.Growing.GrowContainer$$GetTemperatureGrowthMultiplier
    }
    namespace skating {
		inline uintptr_t EffectsFixedUpdate = 0xAC2CA0; // Skateboard Effects FixedUpdate - ScheduleOne.Skating.SkateboardEffects$$FixedUpdate
        inline uintptr_t boardInstance = 0x20;

        inline uintptr_t currentSpeed = 0x118; // float (Read-Only usually)
        inline uintptr_t topSpeed = 0x214; // float: Max Kmh forward
        inline uintptr_t reverseTopSpeed = 0x1A8; // float: Max Kmh backward
        inline uintptr_t pushForce = 0x218; // float: Acceleration per kick
        inline uintptr_t pushDuration = 0x228; // float: How long acceleration lasts after kicking

		// handling/tuning
        inline uintptr_t turnForce = 0x188; // float: How hard it turns
        inline uintptr_t turnChangeRate = 0x18C; // float: Response time (Input Lag)
        inline uintptr_t turnReturnRate = 0x190; // float: Snappiness (Centering speed)
        inline uintptr_t turnSpeedBoost = 0x194; // float: Speed gained while turning (Carving)
        inline uintptr_t rotationClamp = 0x1B8; // float: Max rotation speed (Limits 360s/Reverts)

		// physics
        inline uintptr_t gravity = 0x1A0; // float: Downward force
        inline uintptr_t brakeForce = 0x1A4; // float: Rolling resistance
        inline uintptr_t slowOnTerrain = 0x1BC; // bool:  Does grass/dirt slow you down?
        inline uintptr_t frictionEnabled = 0x1BD; // bool:  Master friction switch
        inline uintptr_t longFriction = 0x1C8; // float: Longitudinal (Forward/Back) Grip
        inline uintptr_t latFriction = 0x1CC; // float: Lateral (Sideways) Grip -> Controls Drifting

        // jump
        inline uintptr_t jumpCharge = 0x120; // float: Current charge (0.0 to 1.0)
        inline uintptr_t jumpForce = 0x1D0; // float: Base vertical power
        inline uintptr_t jumpDurMin = 0x1D4; // float: Minimum time force is applied
        inline uintptr_t jumpDurMax = 0x1D8; // float: Maximum time force is applied
        inline uintptr_t jumpFwdBoost = 0x1F8; // float: Forward velocity added on jump

        // air control
        inline uintptr_t airMoveEnabled = 0x238; // bool:  Can you steer while airborne?
        inline uintptr_t airMoveForce = 0x23C; // float: Power of air steering

        // hover
        inline uintptr_t hoverForce = 0x1FC; // float: Upward lifting force
        inline uintptr_t hoverRayLen = 0x200; // float: How far down to look for ground
        inline uintptr_t hoverHeight = 0x204; // float: Target floating height
    }
    namespace police
    {
        // Police Officer
        inline uintptr_t CanInvestigatePlayer = 0x7E5F10; // ScheduleOne_Police_PoliceOfficer$$CanInvestigatePlayer
        inline uintptr_t CanInvestigate = 0x7E5FE0; // ScheduleOne_Police_PoliceOfficer$$CanInvestigate
        inline uintptr_t OfficerUpdate = 0x7E9D30; // ScheduleOne_Police_PoliceOfficer$$Update

        // Behaviour
        inline uintptr_t UpdateLethalBehaviour = 0x76CDC0; // ScheduleOne_NPCs_Behaviour_PursuitBehaviour$$UpdateLethalBehaviour
        inline uintptr_t UpdateNonLethalBehaviour = 0x76CEA0; // ScheduleOne_NPCs_Behaviour_PursuitBehaviour$$UpdateNonLethalBehaviour
        inline uintptr_t UpdateArrestBehaviour = 0x76C2D0; // ScheduleOne_NPCs_Behaviour_PursuitBehaviour$$UpdateArrestBehaviour
    }

    namespace law
    {
        inline uintptr_t SetCheckpointEnabled = 0x60CBB0; // ScheduleOne_Law_CheckpointManager$$SetCheckpointEnabled
    }
    namespace ItemFramework
    {
        inline uintptr_t SetBalance = 0x994440; // ScheduleOne_ItemFramework_CashInstance$$SetBalance
	}
}