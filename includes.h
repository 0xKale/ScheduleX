#pragma once
#include <Windows.h>
#include <vector>
#include <d3d11.h>
#include <dxgi.h>
#include <string>

// ImGui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

// Kiero & MinHook
#include "kiero/kiero.h"
#include "kiero/minhook/include/MinHook.h"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;

// this needs to be in this order dont remix them please ty 
#include "offsets.hpp"
#include "vars.hpp"
#include "hooks.hpp"
#include "esp.hpp"
