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
    inline bool bDrawNpcBox = true;   // Specific Toggle for NPC Boxes
    inline bool bDrawNpcName = true;  // Specific Toggle for NPC Names



	inline void* pPlayerList = nullptr;// player list
	inline void* pLocalPlayer = nullptr; // local player

	inline std::vector<void*> vNpcList; // npc list


    //ESP COLORS
    inline float cPlayerBox[4] = { 1.0f, 0.0f, 0.0f, 1.0f }; // red
    inline float cNpcBox[4] = { 1.0f, 1.0f, 0.0f, 1.0f }; // yellow
	inline float cNpcName[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; // white
}