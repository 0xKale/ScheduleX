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


    // SKATING VARIABLES
    inline bool bModifySkate = false;
    inline bool bInstantJump = false;
    inline float fSkateGravity = 20.0f;    // Normal gravity
    inline float fSkateTurn = 50.0f;       // Turning sharpness
    inline float fSkateBoost = 10.0f;      // Speed gain while turning
    inline float fSkateJumpCharge = 0.0f;  // Instant Jump Charge
}