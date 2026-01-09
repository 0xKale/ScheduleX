#pragma once
#include "includes.h"

namespace gui
{
    inline void RenderQoLTab()
    {
        ImGui::Checkbox("Debug", &vars::bDebug);
        ImGui::Checkbox("Show Watermark", &vars::bWatermark);

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

    inline void RenderSelfTab()
    {
		ImGui::Checkbox("God Mode", &vars::bCanTakeDamage);
    }

    inline void RenderPoliceTab()
    {
        // Future Police Tab Features
	}

    inline void RenderCasinoTab()
    {
        ImGui::Spacing();
        ImGui::TextDisabled("SLOT MACHINES");
        ImGui::Separator();
        ImGui::Checkbox("Always Jackpot", &vars::bAlwaysJackpot);
        ImGui::Spacing();
        ImGui::Checkbox("Custom Bet Amount", &vars::bCustomBet);
        if (vars::bCustomBet)
        {
            ImGui::Indent();
            ImGui::InputInt("Amount", &vars::iBetAmount, 100, 1000000);
            if (vars::iBetAmount < 0) vars::iBetAmount = 0;
            ImGui::Unindent();
        }
        ImGui::Separator();
        ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "Current Status:");
        ImGui::Text("Next Spin: %s", vars::bAlwaysJackpot ? "JACKPOT" : "Random");
        ImGui::Text("Bet Value: %d", vars::bCustomBet ? vars::iBetAmount : -1);
    }

    inline void RenderEspTab()
    {
        ImGui::Checkbox("Enable ESP", &vars::bEspEnabled);
        if (vars::bEspEnabled)
        {
            ImGui::Spacing();
            ImGui::Checkbox("Show NPCs", &vars::bNpcEsp);
            if (vars::bNpcEsp)
            {
                ImGui::Indent(); 
                ImGui::Checkbox("Draw Boxes", &vars::bDrawNpcBox);
                if (vars::bDrawNpcBox) {
                    ImGui::SameLine();
                    ImGui::ColorEdit4("##NpcBoxColor", vars::cNpcBox, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
                }
                ImGui::Checkbox("Draw Name", &vars::bDrawNpcName);
                if (vars::bDrawNpcName) {
                    ImGui::SameLine();
                    ImGui::ColorEdit4("##NpcNameColor", vars::cNpcName, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
                }

                ImGui::Unindent();
            }
        }
    }

    inline void RenderPlayersTab()
    {
        ImGui::Checkbox("Show Players", &vars::bPlayerEsp);
        if (vars::bPlayerEsp) {
            ImGui::Indent();
            ImGui::ColorEdit4("Box Color", vars::cPlayerBox, ImGuiColorEditFlags_NoInputs);
            ImGui::Unindent();
        }
        ImGui::Separator();
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "debug shit");

        if (vars::pPlayerList)
        {
            int count = *(int*)((uintptr_t)vars::pPlayerList + 0x18);
            ImGui::Text("List Address: %p", vars::pPlayerList);
            ImGui::Text("Players Detected: %d", count);
        }
        else
        {
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "Searching for PlayerList...");
        }
    }

    inline void Render()
    {
        if (GetAsyncKeyState(VK_HOME) & 1 || GetAsyncKeyState(VK_INSERT) & 1)
        {
            vars::bShowMenu = !vars::bShowMenu;
            if (!vars::bShowMenu) {
                hooks::CursorHandler();
            }
        }
        if (vars::bShowMenu) {
            hooks::ForceUnlock();
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

                if (ImGui::BeginTabItem("Self"))
                {
                    RenderSelfTab();
                    ImGui::EndTabItem();
				}

                if (ImGui::BeginTabItem("Police"))
                {
                    RenderPoliceTab();
                    ImGui::EndTabItem();
				}

                if (ImGui::BeginTabItem("Casino"))
                {
                    RenderCasinoTab();
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("ESP"))
                {
                    RenderEspTab();
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Players"))
                {
                    RenderPlayersTab();
                    ImGui::EndTabItem();
                }

                ImGui::EndTabBar();
            }
        }
        ImGui::End();
    }
}