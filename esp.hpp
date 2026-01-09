#pragma once
#include "includes.h"


namespace esp
{
    // Draw Box func
    inline void DrawBox(float x, float y, float w, float h, ImColor color)
    {
        ImGui::GetBackgroundDrawList()->AddRect(
            ImVec2(x, y),
            ImVec2(x + w, y + h),
            color,
            0.0f, 0, 1.5f
        );
    }

    void Draw3DBox(Vector3 center, float w, float h, float d, ImColor color) {
        // Define the 8 corners of the cube in 3D space
        Vector3 corners[8] = {
            { center.x - w, center.y, center.z - d }, { center.x + w, center.y, center.z - d },
            { center.x - w, center.y, center.z + d }, { center.x + w, center.y, center.z + d },
            { center.x - w, center.y + h, center.z - d }, { center.x + w, center.y + h, center.z - d },
            { center.x - w, center.y + h, center.z + d }, { center.x + w, center.y + h, center.z + d }
        };

        ImVec2 screenCorners[8];
        for (int i = 0; i < 8; i++) {
            // Use your existing GetScreenPos function
            if (!hooks::GetScreenPos(corners[i], screenCorners[i])) return;
        }

        // Draw the 12 lines connecting the corners
        auto drawList = ImGui::GetBackgroundDrawList();
        for (int i = 0; i < 4; i++) {
            drawList->AddLine(screenCorners[i], screenCorners[i + 4], color); // Vertical pillars
            drawList->AddLine(screenCorners[i], screenCorners[(i + 1) % 4], color); // Bottom square
            drawList->AddLine(screenCorners[i + 4], screenCorners[((i + 1) % 4) + 4], color); // Top square
        }
    }

    Vector3 RotateVectorByQuaternion(Vector3 v, Quaternion q) {
        Vector3 u = { q.x, q.y, q.z };
        float s = q.w;

        Vector3 cross_uv = {
            u.y * v.z - u.z * v.y,
            u.z * v.x - u.x * v.z,
            u.x * v.y - u.y * v.x
        };
        Vector3 cross_u_uv = {
            u.y * cross_uv.z - u.z * cross_uv.y,
            u.z * cross_uv.x - u.x * cross_uv.z,
            u.x * cross_uv.y - u.y * cross_uv.x
        };
        return {
            v.x + 2.0f * (s * cross_uv.x + cross_u_uv.x),
            v.y + 2.0f * (s * cross_uv.y + cross_u_uv.y),
            v.z + 2.0f * (s * cross_uv.z + cross_u_uv.z)
        };
    }

    void DrawOriented3DBox(void* npc, float w, float h, float d, ImColor color) {
        void* transform = hooks::oGetTransform(npc);
        if (!transform) return;

        Vector3 origin = hooks::oGetPosition(transform);
        Quaternion rotation = hooks::oGetRotation(transform);

        // Define 8 corners relative to the origin (Local Space)
        Vector3 localCorners[8] = {
            { -w, 0, -d }, { w, 0, -d }, { -w, 0, d }, { w, 0, d },
            { -w, h, -d }, { w, h, -d }, { -w, h, d }, { w, h, d }
        };

        ImVec2 screenCorners[8];
        for (int i = 0; i < 8; i++) {
            // 1. Rotate the point
            Vector3 rotated = RotateVectorByQuaternion(localCorners[i], rotation);
            // 2. Translate to world position
            Vector3 worldPos = { origin.x + rotated.x, origin.y + rotated.y, origin.z + rotated.z };
            // 3. Project to screen
            if (!hooks::GetScreenPos(worldPos, screenCorners[i])) return;
        }

        // Draw lines (same logic as previous 3D box)
        auto drawList = ImGui::GetBackgroundDrawList();
        for (int i = 0; i < 4; i++) {
            drawList->AddLine(screenCorners[i], screenCorners[i + 4], color);
            drawList->AddLine(screenCorners[i], screenCorners[(i + 1) % 4], color);
            drawList->AddLine(screenCorners[i + 4], screenCorners[((i + 1) % 4) + 4], color);
        }
    }

    // Unity List Struct (For PlayerList)
    template<typename T>
    struct UnityList {
        void* unk0; void* unk1;
        T* items; int size;
    };

    template<typename T>
    T GetItem(void* listPtr, int index) { // Get Item Helper (For PlayerList)
        if (!listPtr) return nullptr;
        UnityList<T>* list = (UnityList<T>*)listPtr;
        if (index < 0 || index >= list->size) return nullptr;
        void** rawArray = (void**)((uintptr_t)list->items + 0x20);
        return (T)rawArray[index];
    }

    inline std::string GetNameFromUnity(void* obj)// Get Name Helper (Reads C# String)
    {
        // Ensure the object and the hook exist
        if (!obj || !hooks::oGetName) return "Unknown";

        // Call the game function to get the string object pointer
        void* strPtr = hooks::oGetName(obj);
        if (!strPtr) return "Unknown";

        // Unity String structure:
        // [0x10] = int32 length
        // [0x14] = start of wide characters (char16_t)
        int length = *(int*)((uintptr_t)strPtr + 0x10);

        if (length <= 0 || length > 128) return "Unknown";// Safety check on length to avoid reading garbage memory

        char16_t* chars = (char16_t*)((uintptr_t)strPtr + 0x14);
        std::string result = "";
        for (int i = 0; i < length; i++) {
            result += (char)chars[i]; // Convert Wide Char to Standard Char
        }
        return result;
    }

    inline void Render()
    {
        if (vars::bWatermark)
        {
            time_t rawtime;
            struct tm timeinfo;
            char timeBuffer[80];
            time(&rawtime);
            localtime_s(&timeinfo, &rawtime);
            strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", &timeinfo);
            std::string redText = "[DEV BUILD]";
            char whiteBuffer[128];
            sprintf_s(whiteBuffer, sizeof(whiteBuffer), " | %d FPS | %s | ScheduleX | By Dismay & Kingsley", (int)ImGui::GetIO().Framerate, timeBuffer);
            std::string whiteText = whiteBuffer;
            ImVec2 redSize = ImGui::CalcTextSize(redText.c_str());
            ImVec2 whiteSize = ImGui::CalcTextSize(whiteText.c_str());

            float totalWidth = redSize.x + whiteSize.x;
            float padding = 5.0f;
			float x = ImGui::GetIO().DisplaySize.x - totalWidth - 15.0f; // 15 px from right edge
            float y = 15.0f; // Keep top margin the same
            ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x - padding, y - padding),ImVec2(x + totalWidth + padding, y + redSize.y + padding),ImColor(0, 0, 0, 200),4.0f);// 4. Draw Black Background Bar
            ImGui::GetBackgroundDrawList()->AddText(ImVec2(x + 1, y + 1), ImColor(0, 0, 0), redText.c_str());
            ImGui::GetBackgroundDrawList()->AddText(ImVec2(x, y), ImColor(255, 0, 0), redText.c_str());
            ImGui::GetBackgroundDrawList()->AddText(ImVec2(x + redSize.x + 1, y + 1), ImColor(0, 0, 0), whiteText.c_str());
            ImGui::GetBackgroundDrawList()->AddText(ImVec2(x + redSize.x, y), ImColor(255, 255, 255), whiteText.c_str());
        }
        if (!vars::bEspEnabled || !vars::pMainCamera) return;//Global Master Switch & Safety Checks
        if (!hooks::oGetTransform || !hooks::oGetPosition) return;// Ensure we have the basic Unity functions needed

        //player esp
        if (vars::bPlayerEsp && vars::pPlayerList)
        {
            auto list = (UnityList<void*>*)vars::pPlayerList;
            if (list->size > 0 && list->size < 1000)// Sanity check size
            {
                for (int i = 0; i < list->size; i++)
                {
                    void* player = GetItem<void*>(vars::pPlayerList, i);
                    if (!player) continue;

                    void* transform = hooks::oGetTransform(player);
                    if (!transform) continue;

                    Vector3 worldPos = hooks::oGetPosition(transform);

                    ImVec2 footPos;
                    if (hooks::GetScreenPos(worldPos, footPos))
                    {
                        Vector3 headWorld = worldPos;
                        headWorld.y += 1.8f; // Player Height

                        ImVec2 headPos;
                        if (hooks::GetScreenPos(headWorld, headPos))
                        {
                            float height = footPos.y - headPos.y;
                            float width = height / 2.0f;
                            float x = footPos.x - (width / 2.0f);
                            float y = headPos.y;

                            if (vars::bDrawBox) {
                                DrawBox(x, y, width, height, ImColor(vars::cPlayerBox[0], vars::cPlayerBox[1], vars::cPlayerBox[2])); // draw player box
                            }
                        }
                    }
                }
            }
        }

		// npc esp
        if (vars::bNpcEsp && !vars::vNpcList.empty())
        {
            for (size_t i = 0; i < vars::vNpcList.size(); i++)
            {
                void* npc = vars::vNpcList[i];
                if (!npc) continue;

                void* transform = hooks::oGetTransform(npc);
                if (!transform) continue;

                Vector3 worldPos = hooks::oGetPosition(transform);



                ImVec2 footPos;
                if (hooks::GetScreenPos(worldPos, footPos))
                {
                    Vector3 headWorld = worldPos;
                    headWorld.y += 1.8f; // NPC Height

                    ImVec2 headPos;
                    if (hooks::GetScreenPos(headWorld, headPos))
                    {
                        float height = footPos.y - headPos.y;
                        float width = height / 2.0f;
                        float x = footPos.x - (width / 2.0f);
                        float y = headPos.y;

                        if (vars::bDrawNpcBox2D) {
                            DrawBox(x, y, width, height, ImColor(vars::cNpcBox[0], vars::cNpcBox[1], vars::cNpcBox[2])); // draw npc box
                        }
                        if (vars::bDrawNpcBox3D) {
                            Draw3DBox(worldPos, 0.4f, 1.8f, 0.4f, ImColor(vars::cNpcBox[0], vars::cNpcBox[1], vars::cNpcBox[2])); // draw npc box 3d
                        }
                        if (vars::bDrawNpcName)
                        {
                            std::string name = GetNameFromUnity(npc);ImVec2 textSize = ImGui::CalcTextSize(name.c_str());
                            float textX = x + (width / 2.0f) - (textSize.x / 2.0f);
							float textY = y - textSize.y - 2.0f; // Slightly above the box
                            ImGui::GetBackgroundDrawList()->AddText(ImVec2(textX + 1, textY + 1), ImColor(0, 0, 0), name.c_str()); // shadow
							ImGui::GetBackgroundDrawList()->AddText(ImVec2(textX, textY), ImColor(vars::cNpcName[0], vars::cNpcName[1], vars::cNpcName[2]), name.c_str()); // draw npc name
                        }
                    }
                }
            }
        }
        //vars::vNpcList.clear();
    }
}