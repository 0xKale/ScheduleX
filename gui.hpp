#pragma once
#include "includes.h"

namespace gui
{
    inline void RenderQoLTab()
    {
        ImGui::Checkbox("Debug", &vars::bDebug);



        ImGui::Separator();
        ImGui::Checkbox("Custom FOV", &vars::bCustomFieldOfView);
        if (vars::bCustomFieldOfView) {
            ImGui::Indent();
            ImGui::SliderFloat("FOV Amount", &vars::fFieldOfView, 60.0f, 120.0f, "%.1f");
            ImGui::Unindent();
        }
        ImGui::Separator();
        ImGui::Checkbox("Custom Stack Limit", &vars::bCustomStackLimit);
        if (vars::bCustomStackLimit) {
            ImGui::Indent();
            ImGui::SliderInt("Max Stack Size", &vars::iStackLimit, 20, 100);
            ImGui::Unindent();
        }
    }

    inline void Render()
    {
        // Toggle Logic
        if (GetAsyncKeyState(VK_HOME) & 1 || GetAsyncKeyState(VK_INSERT) & 1)
        {
            vars::bShowMenu = !vars::bShowMenu;

            // KEY FIX: Force the state immediately when toggled
            if (vars::bShowMenu) {
                hooks::ForceUnlock();
            }
            else {
                hooks::CursorHandler();
            }
        }

        ImGui::GetIO().MouseDrawCursor = vars::bShowMenu;

        if (!vars::bShowMenu) return;

        ImGui::StyleColorsDark();
        ImGui::SetNextWindowSize(ImVec2(550, 400), ImGuiCond_Once);

        if (ImGui::Begin("ScheduleX", &vars::bShowMenu))
        {
            if (ImGui::BeginTabBar("MainTabBar"))
            {
                if (ImGui::BeginTabItem("QoL"))
                {
                    RenderQoLTab();
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }
        }
        ImGui::End();
    }
}