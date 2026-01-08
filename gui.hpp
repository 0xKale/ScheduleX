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
		if (GetAsyncKeyState(VK_HOME) & 1 || GetAsyncKeyState(VK_INSERT) & 1) // insert and home key to toggle menu
        {
            vars::bShowMenu = !vars::bShowMenu;
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
				if (ImGui::BeginTabBar("ESPTabBar"))
                {
                    if (ImGui::BeginTabItem("ESP"))
                    {
                        ImGui::Checkbox("Enable ESP", &vars::bEspEnabled);

                        if (vars::bEspEnabled)
                        {
                            ImGui::Indent();
                            ImGui::Checkbox("Show Players", &vars::bPlayerEsp);
                            ImGui::Checkbox("Show NPCs", &vars::bNpcEsp); // <--- ADD THIS
                            ImGui::Unindent();
                        }
                        ImGui::Checkbox("Draw Boxes", &vars::bDrawBox);
                        ImGui::Separator();
                        ImGui::TextColored(ImVec4(1, 1, 0, 1), "--- DEBUG INFO ---");

                        // 1. Check if we found the list
                        if (vars::pPlayerList)
                        {
                            // 2. Read the size directly from memory (Offset 0x18 is standard for C# Lists)
                            int count = *(int*)((uintptr_t)vars::pPlayerList + 0x18);

                            ImGui::Text("List Address: %p", vars::pPlayerList);
                            ImGui::Text("Players Detected: %d", count);
                        }
                        else
                        {
                            ImGui::TextColored(ImVec4(1, 0, 0, 1), "Searching for PlayerList...");
                        }
                        ImGui::EndTabItem();
                    }
                    ImGui::EndTabBar();
                }
                ImGui::EndTabBar();
            }
        }
        ImGui::End();
    }
}