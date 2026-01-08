#pragma once
#include "includes.h"
#include <string>

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

                        if (vars::bDrawBox) {
                            DrawBox(x, y, width, height, ImColor(vars::cNpcBox[0], vars::cNpcBox[1], vars::cNpcBox[2])); // draw npc box
                        }

                        std::string name = GetNameFromUnity(npc); // draw npc name

                        ImVec2 textSize = ImGui::CalcTextSize(name.c_str());
                        float textX = x + (width / 2.0f) - (textSize.x / 2.0f);
                        float textY = y - textSize.y - 2.0f; // 2px padding above head
						ImGui::GetBackgroundDrawList()->AddText(ImVec2(textX + 1, textY + 1), ImColor(0, 0, 0), name.c_str()); // black outline/shadow
                        ImGui::GetBackgroundDrawList()->AddText(ImVec2(textX, textY),ImColor(vars::cNpcName[0], vars::cNpcName[1], vars::cNpcName[2]),name.c_str());
                    }
                }
            }
        }
    }
}