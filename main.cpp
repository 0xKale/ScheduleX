#include "includes.h"
#include "hooks.hpp"
#include "gui.hpp"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


void InitImGui()
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(vars::window);
    ImGui_ImplDX11_Init(vars::pDevice, vars::pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (vars::bShowMenu && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    return CallWindowProc(vars::oWndProc, hWnd, uMsg, wParam, lParam);
}

bool init = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    if (!init)
    {
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&vars::pDevice)))
        {
            vars::pDevice->GetImmediateContext(&vars::pContext);
            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc(&sd);
            vars::window = sd.OutputWindow;
            ID3D11Texture2D* pBackBuffer;
            pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            vars::pDevice->CreateRenderTargetView(pBackBuffer, NULL, &vars::mainRenderTargetView);
            pBackBuffer->Release();
            vars::oWndProc = (WNDPROC)SetWindowLongPtr(vars::window, GWLP_WNDPROC, (LONG_PTR)WndProc);

            InitImGui();
            init = true;
        }
        else
            return vars::oPresent(pSwapChain, SyncInterval, Flags);
    }

	// il2cpp thread attach for getname
    if (hooks::il2cpp_domain_get && hooks::il2cpp_thread_attach) {
        void* domain = hooks::il2cpp_domain_get();
        if (domain) {
            hooks::il2cpp_thread_attach(domain);
        }
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    gui::Render();
	esp::Render();

    ImGui::Render();
    vars::pContext->OMSetRenderTargets(1, &vars::mainRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    return vars::oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
    bool init_hook = false;
    do
    {
        if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
        {
            // Bind kiero to vars::oPresent
            kiero::bind(8, (void**)&vars::oPresent, hkPresent);
            hooks::Init();
            init_hook = true;
        }
    } while (!init_hook);
    return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hMod);
        CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
        break;
    case DLL_PROCESS_DETACH:
        kiero::shutdown();
        MH_Uninitialize();
        break;
    }
    return TRUE;
}