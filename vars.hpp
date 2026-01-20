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
    inline int iLastGameLockState = 0; // default locked
    inline bool bLastCursorVisible = true;
    inline bool bWatermark = true;

    // options
    inline bool bCustomFieldOfView = false;
    inline float fFieldOfView = 90.0f; // default fov

    inline bool bCustomStackLimit = false;
    inline int iStackLimit = 20; // default stack limit 20

    // self options
    inline bool bCanTakeDamage = false; // godmode
    inline bool bGodMode = false;

    // movement category
    inline uintptr_t pLocalPlayerController = 0;
    inline uintptr_t pLocalPlayerModel = 0;

    inline bool bModifyMovement = false;
    inline bool bModifyPhysics = false;

    inline float fWalkSpeed = 1.0f;
    inline float fJumpVelocity = 15.0f; // set this higher for higher jumps
    inline float fGravityScale = 1.0f;  // 1.0 = normal, 0.5 = low gravity
    inline bool bInfiniteJump = false;

    // equipable
    inline int iTrashGrabberCapacityAmount = 9999; // trash grabber capacity
    inline bool bBetterTrashGrabber = false; // toggle for trash grabber capacity

    // atm options
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

    // w2s + esp stuff
    inline void* pMainCamera = nullptr; // to store the unity camera
    inline bool bEspEnabled = false;  // toggle for esp
    inline bool bPlayerEsp = false; // toggle for player esp
    inline bool bNpcEsp = false; // toggle for npc esp

    // player esp options
    inline bool bDrawPlayerBox2D = false; // toggle for player boxes
    inline bool bDrawPlayerBox3D = false; // toggle for player boxes3d
    inline bool bDrawPlayerName = false;  // specific toggle for player names
    inline float cPlayerBox[4] = { 1.0f, 0.0f, 0.0f, 1.0f }; // red
    inline float cPlayerName[4] = { 1.0f, 1.0f, 0.0f, 1.0f }; // yellow

    // npc esp options
    inline bool bDrawNpcBox2D = true;   // specific toggle for npc boxes
    inline bool bDrawNpcBox3D = false;   // specific toggle for npc boxes
    inline bool bDrawNpcName = false;  // specific toggle for npc names
    inline bool bDrawNPCList = false; // draw name ui list
    inline float cNpcBox[4] = { 0.0f, 1.0f, 0.0f, 1.0f }; // green
    inline float cNpcName[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; // white

    inline void* pPlayerList = nullptr; // player list
    inline void* pLocalPlayer = nullptr; // local player
    inline std::vector<void*> vNpcList; // npc list

    // world tab 
    inline bool bModifyWorld = false;
    inline float fGrowMultiplier = 1.0f;

    // skating
    inline bool bModifySkate = false;

    // speed
    inline float fSkateTopSpeed = 32.0f;     // default 32.0. set to 300 for super sonic.
    inline float fSkateReverseSpeed = 1.0f;  // default 1.0.
    inline float fSkatePushForce = 9.0f;     // default 9.0. higher = more speed per kick.
    inline float fSkatePushDur = 0.5f;       // default 0.5. higher = glide longer after kick.

    // handling
    inline float fSkateTurnForce = 25.0f;    // default 25.0.
    inline float fSkateResponse = 4.0f;      // "turnchangerate". default 4.0. higher = instant turning.
    inline float fSkateSnappiness = 1.5f;    // "turnreturnrate". default 1.5. higher = board snaps straight.
    inline float fSkateBoost = 1.0f;         // "turnspeedboost". default 1.0. higher = infinite speed while turning.
    inline float fSkateSpinLimit = 5.0f;     // "rotationclamp". default 5.0. set high (1000) to spin incredibly fast.

    // physics & friction
    inline float fSkateGravity = 12.0f;      // default 12.0. lower = moon gravity.
    inline float fSkateBrake = 4.0f;         // "brakeforce". default 4.0. set to 0.0 for infinite roll.
    inline float fSkateLongFriction = 0.9f;  // forward grip. default 0.9.
    inline float fSkateLatFriction = 10.0f;  // sideways grip. default 10.0. set to 0.1 for drifting/sliding.
    inline bool  bSkateSlowOnGrass = true;   // default true. set false to go fast on grass.

    // jump
    inline float fSkateJumpBase = 35.0f;     // "jumpforce". default 35.0. base height.
    inline float fSkateJumpFwd = 15.0f;      // "jumpfwdboost". default 15.0. forward launch power.
    inline float fSkateJumpMult = 1.0f;      // instant charge multiplier (e.g. 10.0x).

    // air control
    inline bool  bSkateAirControl = true;    // default true. enable steering in air.
    inline float fSkateAirForce = 10.0f;     // default 10.0. how hard you can steer in air.

    // hover
    inline bool  bHoverMode = false;         // enable hovering.
    inline float fHoverHeight = 0.2f;        // height in meters.

    // police stuff
    inline bool bModifyPolice = false;
    inline bool bNoSearch = false;
    inline bool bPoliceIgnoreAll = false;
    inline bool bFreezePolice = false;
    inline bool bDisarmPolice = false;
    inline bool bPacifistPolice = false;
    inline bool bAntiJail = false;

    // economy
    inline bool bCustomBalance = false; // balance mod toggle
    inline float fTargetCash = 100000.0f; // target cash amount
    inline float fTargetBank = 500000.0f; // target bank amount

    // pointers
    inline void* pCashInstance = nullptr; // captured cash object
    inline void* pBankInstance = nullptr; // captured bank object

    // casino
    inline bool bAlwaysJackpot = false; // jackpot toggle
    inline bool bCustomBet = false; // bet toggle
    inline int iBetAmount = 1000; // bet value
}

namespace defaults
{
    // world defaults
    // speed
    constexpr float topSpeed = 32.0f;
    constexpr float reverseSpeed = 1.0f;
    constexpr float pushForce = 9.0f;
    constexpr float pushDur = 0.5f;

    // handling
    constexpr float turnForce = 25.0f;
    constexpr float response = 4.0f;
    constexpr float snappiness = 1.5f;
    constexpr float boost = 1.0f;
    constexpr float spinLimit = 5.0f;

    // physics
    constexpr float gravity = 12.0f;
    constexpr float brake = 4.0f;
    constexpr float longFriction = 0.9f;
    constexpr float latFriction = 10.0f;
    constexpr bool  slowOnGrass = true;

    // jump
    constexpr float jumpBase = 35.0f;
    constexpr float jumpFwd = 15.0f;
    constexpr float jumpMult = 1.0f;

    // air
    constexpr bool  airControl = true;
    constexpr float airForce = 10.0f;

    // hover
    constexpr bool  hoverMode = false;
    constexpr float hoverHeight = 0.2f;
}