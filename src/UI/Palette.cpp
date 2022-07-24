#include "UI/Palette.h"
#include <cstring>

namespace GLPaint::UI
{
    static const char* shapes[] = {
        "LINE", "ELLIPSE", "CIRCLE", "RECTANGLE", "TRIANGLE", "BEZIER3"};

    void RenderPalette(Canvas &canvas)
    {
        if (ImGui::Begin("Palette"))
        {
            ImGuiStyle& style = ImGui::GetStyle();
            ImVec2 button_sz(100, 33);
            int buttons_count = 6;
            float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;
            for (int i = 0; i < buttons_count; ++i)
            {
                ImGui::PushID(shapes[i]);
                ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(i / 7.0f, 0.6f, 0.6f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(i / 7.0f, 0.7f, 0.7f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(i / 7.0f, 0.8f, 0.8f));
                if (ImGui::Button(shapes[i], button_sz)) {
                    canvas.AddPrimitive(std::string(shapes[i]));
                }

                if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
                {
                    ImGui::SetDragDropPayload(
                            "PUSH_SHAPE", shapes[i], strlen(shapes[i]) + 1);

                    ImGui::EndDragDropSource();
                }

                float last_button_x2 = ImGui::GetItemRectMax().x;
                float next_button_x2 = last_button_x2 + style.ItemSpacing.x + button_sz.x; // Expected position if next button was on same line
                if (i + 1 < buttons_count && next_button_x2 < window_visible_x2)
                    ImGui::SameLine();

                ImGui::PopStyleColor(3);
                ImGui::PopID();
            }

            ImGui::End();
        }
    }
}
