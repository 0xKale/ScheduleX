#pragma once
#include "includes.h"

namespace gui
{
    void ResetSpeed() {
        vars::fSkateTopSpeed = defaults::topSpeed;
        vars::fSkateReverseSpeed = defaults::reverseSpeed;
        vars::fSkatePushForce = defaults::pushForce;
        vars::fSkatePushDur = defaults::pushDur;
    }

    void ResetHandling() {
        vars::fSkateTurnForce = defaults::turnForce;
        vars::fSkateResponse = defaults::response;
        vars::fSkateSnappiness = defaults::snappiness;
        vars::fSkateBoost = defaults::boost;
        vars::fSkateSpinLimit = defaults::spinLimit;
    }

    void ResetPhysics() {
        vars::fSkateGravity = defaults::gravity;
        vars::fSkateBrake = defaults::brake;
        vars::fSkateLongFriction = defaults::longFriction;
        vars::fSkateLatFriction = defaults::latFriction;
        vars::bSkateSlowOnGrass = defaults::slowOnGrass;
    }

    void ResetJumpAndAir() {
        vars::fSkateJumpBase = defaults::jumpBase;
        vars::fSkateJumpFwd = defaults::jumpFwd;
        vars::fSkateJumpMult = defaults::jumpMult;
        vars::bSkateAirControl = defaults::airControl;
        vars::fSkateAirForce = defaults::airForce;
    }


    void ResetHover() {
        vars::bHoverMode = defaults::hoverMode;
        vars::fHoverHeight = defaults::hoverHeight;
    }

    void ResetAll() {
        ResetSpeed();
        ResetHandling();
        ResetPhysics();
        ResetJumpAndAir();
        ResetHover();
    }

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
        ImGui::Separator();
        ImGui::Checkbox("Better Trash Grabber", &vars::bBetterTrashGrabber);
        if (vars::bBetterTrashGrabber) {
            ImGui::Indent();
            ImGui::SliderInt("Capacity", &vars::iTrashGrabberCapacityAmount, 10, 9999);
            ImGui::Unindent();
        }
    }

    inline void RenderEconomyTab()
    {
        ImGui::TextColored(ImColor(0, 255, 0), "Dealer & NPC Hacks");
        ImGui::Separator();

        ImGui::Checkbox("High Item Value", &vars::bCustomItemValue);
        if (vars::bCustomItemValue) {
            ImGui::Indent();
            ImGui::SliderFloat("Value Per Item", &vars::fItemValue, 1.0f, 100000.0f, "$%.0f");
            ImGui::TextColored(ImColor(255, 255, 0), "Note: NPCs now have infinite buying power.");
            ImGui::Unindent();
        }

        ImGui::Separator();
        ImGui::Checkbox("Dealer Multiplier", &vars::bDealerPriceMultiplier);
        if (vars::bDealerPriceMultiplier) {
            ImGui::SliderFloat("Multiplier", &vars::fDealerMultiplier, 1.0f, 100.0f, "x%.1f");
        }
    }

    inline void RenderSelfTab()
    {
        ImGui::TextColored(ImVec4(0, 1, 1, 1), "MOVEMENT");
        ImGui::Separator();
        ImGui::Checkbox("Enable Movement", &vars::bModifyMovement);
        if (vars::bModifyMovement) {
            ImGui::SliderFloat("Run Speed", &vars::fWalkSpeed, 1.0f, 15.0f, "%.1f x");
            ImGui::SliderFloat("Jump Velocity", &vars::fJumpVelocity, 5.0f, 50.0f, "%.1f m/s");
            ImGui::Checkbox("Unlimited Jumps (Air Hop)", &vars::bInfiniteJump);
            if (ImGui::IsItemHovered()) ImGui::SetTooltip("If disabled, you can only use the custom jump height when standing on the ground.");
            ImGui::SliderFloat("Gravity Scale", &vars::fGravityScale, 0.0f, 2.0f, "%.2f G");
        }
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Checkbox("God Mode", &vars::bCanTakeDamage);
    }

    inline void RenderPoliceTab()
    {
        // Future Police Tab Features
	}

    inline void RenderWorldTab()
    {
        ImGui::TextColored(ImVec4(0, 1, 0.5f, 1), "GROWTH OVERCLOCK");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Checkbox("Enable World Hacks", &vars::bModifyWorld);

        if (vars::bModifyWorld) {
            ImGui::Indent();

            ImGui::Text("Temperature Efficiency Multiplier");

            ImGui::SliderFloat("##Speed", &vars::fGrowMultiplier, 1.0f, 100.0f, "%.2f x");

            if (vars::fGrowMultiplier >= 10.0f) {
                ImGui::TextColored(ImVec4(0, 1, 0, 1), "Plants will grow in seconds.");
            }

            ImGui::Unindent();
        }
        ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), "TONY HAWK MODE");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Checkbox("Enable Skate Mods", &vars::bModifySkate);

        if (vars::bModifySkate) {
            ImGui::Indent();

            if (ImGui::Button("RESET ALL TO DEFAULTS", ImVec2(-1, 0))) { 
                ResetAll();
            }
            ImGui::Separator();
			// speed & acceleration
            ImGui::Spacing();
            ImGui::TextColored(ImVec4(0, 1, 0, 1), "[ SPEED & ACCELERATION ]");
            if (ImGui::SmallButton("Reset Speed")) ResetSpeed();
            ImGui::SliderFloat("Top Speed", &vars::fSkateTopSpeed, 50.0f, 500.0f, "%.0f km/h");
            if (ImGui::IsItemHovered()) ImGui::SetTooltip("Absolute max speed limit.");

            ImGui::SliderFloat("Reverse Speed", &vars::fSkateReverseSpeed, 10.0f, 200.0f, "%.0f km/h");

            ImGui::SliderFloat("Kick Power", &vars::fSkatePushForce, 1.0f, 20.0f, "%.1f x");
            if (ImGui::IsItemHovered()) ImGui::SetTooltip("Acceleration per kick. Set to 10 for instant launch.");

            ImGui::SliderFloat("Kick Glide", &vars::fSkatePushDur, 1.0f, 5.0f, "%.1f s");
            if (ImGui::IsItemHovered()) ImGui::SetTooltip("How long the acceleration lasts after a kick.");

			// handling & turning
            ImGui::Spacing();
            ImGui::TextColored(ImVec4(1, 0, 1, 1), "[ HANDLING & TURNING ]");
            if (ImGui::SmallButton("Reset Handling")) ResetHandling();

            ImGui::SliderFloat("Turn Radius", &vars::fSkateTurnForce, 10.0f, 300.0f, "%.0f");
            if (ImGui::IsItemHovered()) ImGui::SetTooltip("Higher = Tighter turns.");

            ImGui::SliderFloat("Responsiveness", &vars::fSkateResponse, 1.0f, 100.0f, "%.0f");
            if (ImGui::IsItemHovered()) ImGui::SetTooltip("Input Lag. Higher = Instant reaction.");

            ImGui::SliderFloat("Snappiness", &vars::fSkateSnappiness, 1.0f, 100.0f, "%.0f");
            if (ImGui::IsItemHovered()) ImGui::SetTooltip("How fast the board centers itself.");

            ImGui::SliderFloat("Spin Limit", &vars::fSkateSpinLimit, 1.0f, 1000.0f, "%.0f");
            if (ImGui::IsItemHovered()) ImGui::SetTooltip("Max rotation speed. Set to 1000 for instant Reverts/360s.");

            ImGui::SliderFloat("Carve Boost", &vars::fSkateBoost, 0.0f, 100.0f, "%.1f");
            if (ImGui::IsItemHovered()) ImGui::SetTooltip("Speed gained by turning. Wiggle to accelerate.");

			// physics & drift
            ImGui::Spacing();
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "[ PHYSICS & DRIFT ]");
			if (ImGui::SmallButton("Reset Physics")) ResetPhysics();

            ImGui::SliderFloat("Gravity", &vars::fSkateGravity, 0.0f, 50.0f, "%.1f");
            if (ImGui::IsItemHovered()) ImGui::SetTooltip("Earth = 9.8. Moon = 1.6. Zero = Space.");

            ImGui::SliderFloat("Brake Force", &vars::fSkateBrake, 0.0f, 20.0f, "%.1f");
            if (ImGui::IsItemHovered()) ImGui::SetTooltip("Rolling resistance. 0.0 = Infinite Roll.");

            ImGui::SliderFloat("Drift Grip", &vars::fSkateLatFriction, 0.0f, 2.0f, "%.2f");
            if (ImGui::IsItemHovered()) ImGui::SetTooltip("Sideways friction. 0.1 = Ice/Drift. 2.0 = Rails.");

            ImGui::SliderFloat("Fwd Grip", &vars::fSkateLongFriction, 0.0f, 2.0f, "%.2f");

            ImGui::Checkbox("Grass Slows You Down", &vars::bSkateSlowOnGrass);

            // jump & air
            ImGui::Spacing();
            ImGui::TextColored(ImVec4(0, 1, 1, 1), "[ JUMP & AIR ]");
			if (ImGui::SmallButton("Reset Jump & Air")) ResetJumpAndAir();

            ImGui::SliderFloat("Jump Height", &vars::fSkateJumpBase, 1.0f, 50.0f, "%.1f");
            ImGui::SliderFloat("Jump Fwd Boost", &vars::fSkateJumpFwd, 0.0f, 50.0f, "%.1f");
            ImGui::SliderFloat("Charge Multiplier", &vars::fSkateJumpMult, 1.0f, 20.0f, "%.1f x");
            if (ImGui::IsItemHovered()) ImGui::SetTooltip("Instantly fills the jump charge meter X times over.");

            ImGui::Checkbox("Enable Air Steering", &vars::bSkateAirControl);
            if (vars::bSkateAirControl) {
                ImGui::SameLine();
                ImGui::SetNextItemWidth(100);
                ImGui::SliderFloat("Force", &vars::fSkateAirForce, 0.0f, 100.0f, "%.1f");
            }
            // hover
            ImGui::Spacing();
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "[ SPECIALS ]");
            if (ImGui::SmallButton("Reset Physics")) ResetHover();

            ImGui::Checkbox("HOVERBOARD MODE", &vars::bHoverMode);
            if (vars::bHoverMode) {
                ImGui::Indent();
                ImGui::SliderFloat("Hover Height", &vars::fHoverHeight, 0.1f, 10.0f, "%.1f m");
                ImGui::TextDisabled("Floats over water & obstacles!");
                ImGui::Unindent();
            }

            ImGui::Unindent();
        }
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
                ImGui::Checkbox("Draw Boxes 2D", &vars::bDrawNpcBox2D);
                if (vars::bDrawNpcBox2D) {
                    ImGui::SameLine();
                    ImGui::ColorEdit4("##NpcBoxColor", vars::cNpcBox, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
                }
                ImGui::Checkbox("Draw Boxes 3D (Scuffed)", &vars::bDrawNpcBox3D);
                if (vars::bDrawNpcBox3D) {
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

    inline void RenderOtherTab()
    {
        ImGui::Checkbox("Show Watermark", &vars::bWatermark);
        ImGui::Separator();
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

                if (ImGui::BeginTabItem("Economy"))
                {
                    RenderEconomyTab();
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Police"))
                {
                    RenderPoliceTab();
                    ImGui::EndTabItem();
				}

                if (ImGui::BeginTabItem("World"))
                {
                    RenderWorldTab();
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

                if (ImGui::BeginTabItem("Other"))
                {
                    RenderOtherTab();
                    ImGui::EndTabItem();
                }

                ImGui::EndTabBar();
            }
        }
        ImGui::End();
    }
}