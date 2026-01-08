#pragma once
#include "includes.h"
#include <string>

namespace esp
{
    // =============================================================
    // HELPER FUNCTIONS
    // =============================================================

    // 1. Draw Box Helper
    inline void DrawBox(float x, float y, float w, float h, ImColor color)
    {
        ImGui::GetBackgroundDrawList()->AddRect(
            ImVec2(x, y),
            ImVec2(x + w, y + h),
            color,
            0.0f, 0, 1.5f
        );
    }

    // 2. Unity List Struct (For PlayerList)
    template<typename T>
    struct UnityList {
        void* unk0; void* unk1;
        T* items; int size;
    };

    // 3. Get Item Helper (For PlayerList)
    template<typename T>
    T GetItem(void* listPtr, int index) {
        if (!listPtr) return nullptr;
        UnityList<T>* list = (UnityList<T>*)listPtr;
        if (index < 0 || index >= list->size) return nullptr;
        void** rawArray = (void**)((uintptr_t)list->items + 0x20);
        return (T)rawArray[index];
    }

    // 4. Get Name Helper (Reads C# String)
    inline std::string GetNameFromUnity(void* obj)
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

        // Safety check on length to avoid reading garbage memory
        if (length <= 0 || length > 128) return "Unknown";

        char16_t* chars = (char16_t*)((uintptr_t)strPtr + 0x14);
        std::string result = "";

        // Convert Wide Char to Standard Char
        for (int i = 0; i < length; i++) {
            result += (char)chars[i];
        }
        return result;
    }

    // =============================================================
    // MAIN RENDER LOOP
    // =============================================================
    inline void Render()
    {
        // 1. Global Master Switch & Safety Checks
        if (!vars::bEspEnabled || !vars::pMainCamera) return;

        // Ensure we have the basic Unity functions needed
        if (!hooks::oGetTransform || !hooks::oGetPosition) return;

        // ---------------------------------------------------------
        // A. PLAYER ESP (Red Boxes)
        // ---------------------------------------------------------
        if (vars::bPlayerEsp && vars::pPlayerList)
        {
            auto list = (UnityList<void*>*)vars::pPlayerList;

            // Sanity check size
            if (list->size > 0 && list->size < 1000)
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
                                DrawBox(x, y, width, height, ImColor(255, 0, 0)); // RED
                            }
                        }
                    }
                }
            }
        }

        // ---------------------------------------------------------
        // B. NPC ESP (Yellow Boxes + Names)
        // ---------------------------------------------------------
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

                        // 1. Draw Box
                        if (vars::bDrawBox) {
                            DrawBox(x, y, width, height, ImColor(255, 255, 0)); // YELLOW
                        }

                        // 2. Draw Name
                        std::string name = GetNameFromUnity(npc);

                        // Calculate text centering
                        ImVec2 textSize = ImGui::CalcTextSize(name.c_str());
                        float textX = x + (width / 2.0f) - (textSize.x / 2.0f);
                        float textY = y - textSize.y - 2.0f; // 2px padding above head

                        // Draw Shadow (Black)
                        ImGui::GetBackgroundDrawList()->AddText(ImVec2(textX + 1, textY + 1), ImColor(0, 0, 0), name.c_str());
                        // Draw Text (White)
                        ImGui::GetBackgroundDrawList()->AddText(ImVec2(textX, textY), ImColor(255, 255, 255), name.c_str());
                    }
                }
            }
        }
    }
}