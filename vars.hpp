#pragma once
#include <d3d11.h>
#include <dxgi.h>

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

struct Vector3 {
    float x, y, z;
};

struct Vector2 {
    float x, y;
};

struct Quaternion {
    float x, y, z, w;
};

namespace vars
{

    inline HWND window = NULL;
    inline WNDPROC oWndProc = nullptr;
    inline Present oPresent = nullptr;

    inline ID3D11Device* pDevice = NULL;
    inline ID3D11DeviceContext* pContext = NULL;
    inline ID3D11RenderTargetView* mainRenderTargetView = NULL;

    // menu states
    inline bool bShowMenu = true;
    inline int iLastGameLockState = 0; // Default Locked
    inline bool bLastCursorVisible = true;
    inline bool bWatermark = true;

    // options
    inline bool bCustomFieldOfView = false;
	inline float fFieldOfView = 90.0f; // default FOV

    inline bool bCustomStackLimit = false;
	inline int iStackLimit = 20; // default stack limit 20


	// self options
	inline bool bCanTakeDamage = false; // godmode

    // Movement Category
    inline uintptr_t pLocalPlayerController = 0;
    inline uintptr_t pLocalPlayerModel = 0;

    inline bool bModifyMovement = false;
    inline bool bModifyPhysics = false;
    inline bool bGodMode = false;

    inline float fWalkSpeed = 1.0f;
    inline float fJumpVelocity = 15.0f; // Set this higher for higher jumps
    inline float fGravityScale = 1.0f;  // 1.0 = Normal, 0.5 = Low Gravity
    inline bool bInfiniteJump = false;

    // Casino Options
    inline bool bAlwaysJackpot = false;   // Toggle for Jackpot
    inline bool bCustomBet = false;       // Toggle for Custom Bet
    inline int iBetAmount = 1000;         // Value for Custom Bet

	// equipable
	inline int iTrashGrabberCapacityAmount = 9999; // trash grabber capacity
	inline bool bBetterTrashGrabber = false; // toggle for trash grabber capacity

	// ATM Options
	inline bool bATMWithdraw = false; // atm withdraw
	inline float fATMWithdrawAmount = 99999.0f; // atm withdraw amount
	inline bool bATMWithdrawLimit = false; // atm withdraw limit toggle
	inline float fATMWithdrawLimit = 10000.0f; // atm daily limit

    // item
	inline bool bCustomItemValue = false; // toggle for custom item value
	inline float fItemValue = 1000.0f; // custom item value 

    // dealer
	inline bool bDealerPriceMultiplier = false; // toggle for dealer price multiplier
	inline float fDealerMultiplier = 100.0f; // dealer price multiplier


    // debug shit
    inline bool bDebug = false;
    inline float fDebugFloat = 1.0f;
    inline int iDebugInt = 0;

    //w2s + esp stuff
    inline void* pMainCamera = nullptr; // To store the Unity Camera
    inline bool bEspEnabled = false;  // Toggle for ESP
    inline bool bDrawBox = false; // Toggle for Boxes
	inline bool bPlayerEsp = false; // Toggle for Player ESP
    inline bool bNpcEsp = false; // Toggle for NPC ESP
    inline bool bDrawNpcBox2D = true;   // Specific Toggle for NPC Boxes
    inline bool bDrawNpcBox3D = false;   // Specific Toggle for NPC Boxes
    inline bool bDrawNpcName = false;  // Specific Toggle for NPC Names



	inline void* pPlayerList = nullptr;// player list
	inline void* pLocalPlayer = nullptr; // local player

	inline std::vector<void*> vNpcList; // npc list


    //ESP COLORS
    inline float cPlayerBox[4] = { 1.0f, 0.0f, 0.0f, 1.0f }; // red
    inline float cNpcBox[4] = { 0.0f, 1.0f, 0.0f, 1.0f }; // green
	inline float cNpcName[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; // white


    // world tab 

    inline bool bModifyWorld = false;
    inline float fGrowMultiplier = 1.0f;

    inline bool bModifySkate = false;

    // speed
    inline float fSkateTopSpeed = 32.0f;     // Default 32.0. Set to 300 for Super Sonic.
    inline float fSkateReverseSpeed = 1.0f;  // Default 1.0.
    inline float fSkatePushForce = 9.0f;     // Default 9.0. Higher = more speed per kick.
    inline float fSkatePushDur = 0.5f;       // Default 0.5. Higher = glide longer after kick.

	// handling
    inline float fSkateTurnForce = 25.0f;    // Default 25.0.
    inline float fSkateResponse = 4.0f;      // "TurnChangeRate". Default 4.0. Higher = Instant turning.
    inline float fSkateSnappiness = 1.5f;    // "TurnReturnRate". Default 1.5. Higher = Board snaps straight.
    inline float fSkateBoost = 1.0f;         // "TurnSpeedBoost". Default 1.0. Higher = Infinite speed while turning.
    inline float fSkateSpinLimit = 5.0f;     // "RotationClamp". Default 5.0. Set high (1000) to spin incredibly fast.

	// physics & friction
    inline float fSkateGravity = 12.0f;      // Default 12.0. Lower = Moon gravity.
    inline float fSkateBrake = 4.0f;         // "BrakeForce". Default 4.0. Set to 0.0 for Infinite Roll.
    inline float fSkateLongFriction = 0.9f;  // Forward Grip. Default 0.9.
    inline float fSkateLatFriction = 10.0f;  // Sideways Grip. Default 10.0. Set to 0.1 for drifting/sliding.
    inline bool  bSkateSlowOnGrass = true;   // Default true. Set false to go fast on grass.

    // jump
    inline float fSkateJumpBase = 35.0f;     // "JumpForce". Default 35.0. Base height.
    inline float fSkateJumpFwd = 15.0f;      // "JumpFwdBoost". Default 15.0. Forward launch power.
    inline float fSkateJumpMult = 1.0f;      // Instant Charge Multiplier (e.g. 10.0x).

    // air control
    inline bool  bSkateAirControl = true;    // Default true. Enable steering in air.
    inline float fSkateAirForce = 10.0f;     // Default 10.0. How hard you can steer in air.

    // hover
    inline bool  bHoverMode = false;         // Enable hovering.
    inline float fHoverHeight = 0.2f;        // Height in meters.


	//police stuff
    inline bool bModifyPolice = false;
    inline bool bNoSearch = false;
    inline bool bPoliceIgnoreAll = false;
    inline bool bFreezePolice = false;
    inline bool bDisarmPolice = false;
    inline bool bPacifistPolice = false;
    inline bool bAntiJail = false;

    // menu settings
    inline float fMenuOpacity = 1.0f;
    inline float fMenuRounding = 4.0f;
    inline bool bMenuAnimations = true;
    inline float fMenuScale = 1.0f;
    inline int iMenuColorTheme = 0; // 0 = Dark, 1 = Light, 2 = Classic, 3 = Custom
    inline float cMenuAccent[4] = { 0.26f, 0.59f, 0.98f, 1.0f }; // Default ImGui blue
    inline bool bSaveOnClose = false;
    inline bool bShowTooltips = true;
    inline bool bConfirmOnReset = true;
}

namespace defaults
{

    //WORLD DEFAULTS
    // Speed
    constexpr float topSpeed = 32.0f;
    constexpr float reverseSpeed = 1.0f;
    constexpr float pushForce = 9.0f;
    constexpr float pushDur = 0.5f;

    // Handling
    constexpr float turnForce = 25.0f;
    constexpr float response = 4.0f;
    constexpr float snappiness = 1.5f;
    constexpr float boost = 1.0f;
    constexpr float spinLimit = 5.0f;

    // Physics
    constexpr float gravity = 12.0f;
    constexpr float brake = 4.0f;
    constexpr float longFriction = 0.9f;
    constexpr float latFriction = 10.0f;
    constexpr bool  slowOnGrass = true;

    // Jump
    constexpr float jumpBase = 35.0f;
    constexpr float jumpFwd = 15.0f;
    constexpr float jumpMult = 1.0f;

    // Air
    constexpr bool  airControl = true;
    constexpr float airForce = 10.0f;

    // Hover (Mod Defaults)
    constexpr bool  hoverMode = false;
    constexpr float hoverHeight = 0.2f;

    // Menu Defaults
    constexpr float menuOpacity = 1.0f;
    constexpr float menuRounding = 4.0f;
    constexpr bool  menuAnimations = true;
    constexpr float menuScale = 1.0f;
    constexpr int   menuColorTheme = 0;
    constexpr bool  saveOnClose = false;
    constexpr bool  showTooltips = true;
    constexpr bool  confirmOnReset = true;
}
