#pragma once
#include "includes.h"

namespace esp
{
    // color helper
    inline ImColor GetColor(float* col) {
        return ImColor(col[0], col[1], col[2], col[3]);
    }

    // drawing
    inline void DrawBox(float x, float y, float w, float h, ImColor color)
    {
        ImGui::GetBackgroundDrawList()->AddRect(
            ImVec2(x, y),
            ImVec2(x + w, y + h),
            color,
            0.0f, 0, 1.5f
        );
    }

    // 3d box drawing logic
    void Draw3DBox(Vector3 center, float w, float h, float d, ImColor color)
    {
        // bottom vertices
        Vector3 p1 = { center.x - w, center.y, center.z - d };
        Vector3 p2 = { center.x + w, center.y, center.z - d };
        Vector3 p3 = { center.x + w, center.y, center.z + d };
        Vector3 p4 = { center.x - w, center.y, center.z + d };

        // top vertices
        Vector3 p5 = { center.x - w, center.y + h, center.z - d };
        Vector3 p6 = { center.x + w, center.y + h, center.z - d };
        Vector3 p7 = { center.x + w, center.y + h, center.z + d };
        Vector3 p8 = { center.x - w, center.y + h, center.z + d };

        ImVec2 s1, s2, s3, s4, s5, s6, s7, s8;

        // project and draw lines
        if (hooks::GetScreenPos(p1, s1) && hooks::GetScreenPos(p2, s2) &&
            hooks::GetScreenPos(p3, s3) && hooks::GetScreenPos(p4, s4) &&
            hooks::GetScreenPos(p5, s5) && hooks::GetScreenPos(p6, s6) &&
            hooks::GetScreenPos(p7, s7) && hooks::GetScreenPos(p8, s8))
        {
            ImDrawList* list = ImGui::GetBackgroundDrawList();

            // bottom ring
            list->AddLine(s1, s2, color, 1.0f);
            list->AddLine(s2, s3, color, 1.0f);
            list->AddLine(s3, s4, color, 1.0f);
            list->AddLine(s4, s1, color, 1.0f);

            // top ring
            list->AddLine(s5, s6, color, 1.0f);
            list->AddLine(s6, s7, color, 1.0f);
            list->AddLine(s7, s8, color, 1.0f);
            list->AddLine(s8, s5, color, 1.0f);

            // vertical connections
            list->AddLine(s1, s5, color, 1.0f);
            list->AddLine(s2, s6, color, 1.0f);
            list->AddLine(s3, s7, color, 1.0f);
            list->AddLine(s4, s8, color, 1.0f);
        }
    }

    // unity helpers
    std::string GetNameFromUnity(void* obj)
    {
        if (!obj || !hooks::oGetName) return "none";
        void* nameObj = hooks::oGetName(obj);
        if (!nameObj) return "none";

        // mono string to std string offset
        return std::string((char*)((uintptr_t)nameObj + 0x14));
    }

    // watermark
    inline void DrawWatermark()
    {
        if (!vars::bWatermark) return;

        time_t rawtime;
        struct tm timeinfo;
        char timeBuffer[80];
        time(&rawtime);
        localtime_s(&timeinfo, &rawtime);
        strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", &timeinfo);

        // split text for coloring
        std::string redText = "[DEV BUILD]";
        char middleBuffer[128];
        sprintf_s(middleBuffer, sizeof(middleBuffer), " | %d FPS | %s | ScheduleX | By ", (int)ImGui::GetIO().Framerate, timeBuffer);
        std::string rainbowText = "Dismay & Kingsley";

        ImVec2 redSize = ImGui::CalcTextSize(redText.c_str());
        ImVec2 midSize = ImGui::CalcTextSize(middleBuffer);
        ImVec2 rainbowSize = ImGui::CalcTextSize(rainbowText.c_str());

        float totalWidth = redSize.x + midSize.x + rainbowSize.x;
        float padding = 5.0f;
        float x = ImGui::GetIO().DisplaySize.x - totalWidth - 15.0f;
        float y = 15.0f;

        // rainbow color logic
        float t = (float)ImGui::GetTime();
        ImColor rainbowColor = ImColor::HSV(t * 0.5f, 1.0f, 1.0f);

        auto drawList = ImGui::GetBackgroundDrawList();

        // draw background bar
        drawList->AddRectFilled(ImVec2(x - padding, y - padding), ImVec2(x + totalWidth + padding, y + redSize.y + padding), ImColor(0, 0, 0, 200), 4.0f);

        // red tag
        drawList->AddText(ImVec2(x + 1, y + 1), ImColor(0, 0, 0), redText.c_str());
        drawList->AddText(ImVec2(x, y), ImColor(255, 0, 0), redText.c_str());

        // middle white text
        drawList->AddText(ImVec2(x + redSize.x + 1, y + 1), ImColor(0, 0, 0), middleBuffer);
        drawList->AddText(ImVec2(x + redSize.x, y), ImColor(255, 255, 255), middleBuffer);

        // rainbow names
        drawList->AddText(ImVec2(x + redSize.x + midSize.x + 1, y + 1), ImColor(0, 0, 0), rainbowText.c_str());
        drawList->AddText(ImVec2(x + redSize.x + midSize.x, y), rainbowColor, rainbowText.c_str());
    }

    // loop
    inline void Render()
    {
        DrawWatermark();

        if (!vars::bEspEnabled) return;

        // npc section
        if (vars::bNpcEsp)
        {
            float listX = 15.0f;
            float listY = 100.0f;

            for (void* npc : vars::vNpcList)
            {
                if (!npc) continue;

                void* transform = hooks::oGetTransform(npc);
                if (!transform) continue;

                Vector3 worldPos = hooks::oGetPosition(transform);
                ImVec2 screenPos;

                if (hooks::GetScreenPos(worldPos, screenPos))
                {
                    if (vars::bDrawNpcBox2D) {
                        DrawBox(screenPos.x - 20, screenPos.y - 40, 40, 80, GetColor(vars::cNpcBox));
                    }

                    if (vars::bDrawNpcBox3D) {
                        Draw3DBox(worldPos, 0.4f, 1.8f, 0.4f, GetColor(vars::cNpcBox));
                    }

                    std::string name = GetNameFromUnity(npc);

                    if (vars::bDrawNpcName)
                    {
                        ImVec2 textSize = ImGui::CalcTextSize(name.c_str());
                        ImGui::GetBackgroundDrawList()->AddText(ImVec2(screenPos.x - (textSize.x / 2) + 1, screenPos.y - 50 + 1), ImColor(0, 0, 0), name.c_str());
                        ImGui::GetBackgroundDrawList()->AddText(ImVec2(screenPos.x - (textSize.x / 2), screenPos.y - 50), GetColor(vars::cNpcName), name.c_str());
                    }

                    if (vars::bDrawNPCList) {
                        ImGui::GetForegroundDrawList()->AddText(ImVec2(listX, listY), GetColor(vars::cNpcName), name.c_str());
                        listY += 15.0f;
                    }
                }
            }
        }

        // player section
        if (vars::bPlayerEsp && vars::pPlayerList)
        {
            uintptr_t list = (uintptr_t)vars::pPlayerList;
            uintptr_t items = *(uintptr_t*)(list + offsets::player::ListItems);
            int size = *(int*)(list + offsets::player::ListSize);

            // check bounds
            if (items && size > 0 && size < 100)
            {
                for (int i = 0; i < size; i++)
                {
                    void* player = *(void**)(items + offsets::player::ArrayStart + (i * offsets::player::PointerStep));
                    if (!player || player == vars::pLocalPlayer) continue;

                    void* transform = hooks::oGetTransform(player);
                    if (!transform) continue;

                    Vector3 worldPos = hooks::oGetPosition(transform);
                    ImVec2 screenPos;

                    if (hooks::GetScreenPos(worldPos, screenPos))
                    {
                        if (vars::bDrawPlayerBox2D) {
                            DrawBox(screenPos.x - 20, screenPos.y - 40, 40, 80, GetColor(vars::cPlayerBox));
                        }

                        if (vars::bDrawPlayerBox3D) {
                            Draw3DBox(worldPos, 0.4f, 1.8f, 0.4f, GetColor(vars::cPlayerBox));
                        }

                        std::string name = GetNameFromUnity(player);

                        if (vars::bDrawPlayerName)
                        {
                            ImVec2 textSize = ImGui::CalcTextSize(name.c_str());
                            ImGui::GetBackgroundDrawList()->AddText(ImVec2(screenPos.x - (textSize.x / 2) + 1, screenPos.y - 50 + 1), ImColor(0, 0, 0), name.c_str());
                            ImGui::GetBackgroundDrawList()->AddText(ImVec2(screenPos.x - (textSize.x / 2), screenPos.y - 50), GetColor(vars::cPlayerName), name.c_str());
                        }
                    }
                }
            }
        }
    }
}