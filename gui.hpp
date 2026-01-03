#pragma once
#include "includes.h"
#include "vars.hpp"

namespace gui
{
    inline bool bShowMenu = true;

    inline void RenderQoLTab()
    {
        ImGui::Text("Quality Of Life Mods");
        ImGui::Separator();

        ImGui::Checkbox("Custom FOV", &vars::bCustomFieldOfView);
        if (vars::bCustomFieldOfView)
        {
            ImGui::Indent();
            ImGui::SliderFloat("FOV Amount", &vars::fFieldOfView, 60.0f, 120.0f, "%.1f");
            ImGui::Unindent();
        }
        ImGui::Separator();
        ImGui::Checkbox("Custom Stack Limit", &vars::bCustomStackLimit);
        if (vars::bCustomStackLimit)
        {
            ImGui::Indent();
            ImGui::SliderInt("Max Stack Size", &vars::iStackLimit, 20, 100);
            ImGui::Unindent();
        }
    }

    inline void Render()
    {
        if (GetAsyncKeyState(VK_HOME) & 1 || GetAsyncKeyState(VK_INSERT) & 1)
            bShowMenu = !bShowMenu;

        ImGui::GetIO().MouseDrawCursor = bShowMenu;

        if (!bShowMenu) return;

        ImGui::StyleColorsDark();
        ImGui::SetNextWindowSize(ImVec2(550, 400), ImGuiCond_Once);

        if (ImGui::Begin("ScheduleX", &bShowMenu))
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