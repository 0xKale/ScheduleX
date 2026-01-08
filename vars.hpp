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
    inline int iLastGameLockState = 1; // Default Locked
    inline bool bLastCursorVisible = false;

    // options
    inline bool bCustomFieldOfView = false;
	inline float fFieldOfView = 90.0f; // default FOV

    inline bool bCustomStackLimit = false;
	inline int iStackLimit = 20; // default stack limit

    inline bool bDebug = false;
    inline float fDebugFloat = 1.0f;
    inline int iDebugInt = 0;

    //w2s
    inline void* pMainCamera = nullptr; // To store the Unity Camera
    inline bool bEspEnabled = true;  // Toggle for ESP
    inline bool bDrawBox = true; // Toggle for Boxes
	inline bool bPlayerEsp = false; // Toggle for Player ESP
    inline bool bNpcEsp = false; // Toggle for NPC ESP

	inline void* pPlayerList = nullptr;// player list
    inline void* pLocalPlayer = nullptr;

    inline std::vector<void*> vNpcList;
}