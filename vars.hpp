#pragma once
#include <d3d11.h>
#include <dxgi.h>

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

namespace vars
{
    inline HWND window = NULL;
    inline WNDPROC oWndProc = nullptr;
    inline Present oPresent = nullptr;

    inline ID3D11Device* pDevice = NULL;
    inline ID3D11DeviceContext* pContext = NULL;
    inline ID3D11RenderTargetView* mainRenderTargetView = NULL;

    // --- Menu States ---
    inline bool bShowMenu = true;
    inline int iLastGameLockState = 1; // Default Locked
    inline bool bLastCursorVisible = false;

    // --- Settings ---
    inline bool bCustomFieldOfView = false;
    inline float fFieldOfView = 90.0f;

    inline bool bCustomStackLimit = false;
    inline int iStackLimit = 20;

    inline bool bDebug = false;
    inline float fDebugFloat = 1.0f;
    inline int iDebugInt = 0;
}