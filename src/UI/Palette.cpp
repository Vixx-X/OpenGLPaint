#include "UI/Palette.h"
#include <cstring>

namespace GLPaint::UI
{
    static const char* shapes[] = {
        "LINE", "ELLIPSE", "CIRCLE", "RECTANGLE", "TRIANGLE", "BEZIER3"};
    static int width;

    void RenderShapeButtons(Canvas &canvas)
    {
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec2 button_sz(100, 33);
        int buttons_count = 6;
        float window_visible = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;
        width = window_visible;
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

            float last_button = ImGui::GetItemRectMax().x;
            float next_button = last_button + style.ItemSpacing.x + button_sz.x; // Expected position if next button was on same line
            if (i + 1 < buttons_count && next_button < window_visible)
                ImGui::SameLine();

            ImGui::PopStyleColor(3);
            ImGui::PopID();
        }
    }

    void RenderPalette(Canvas &canvas)
    {
        auto flags = ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoAlpha;
        if (ImGui::Begin("Palette"))
        {
            RenderShapeButtons(canvas);

            ImGui::Separator();

            ImGui::PushItemWidth(155);
            ImGui::BeginGroup();
            {
                ImGui::Text("Border Color");
                if (ImGui::ColorPicker3(
                        "##BorderColor", (float*)&canvas.m_border_color, flags))
                {
                    if (canvas.IsSelected()) {
                        auto c = canvas.m_border_color;
                        canvas.GetSelected()->SetColor(c.r, c.g, c.g);
                    }
                }
                ImGui::EndGroup();
            }
            ImGui::SameLine();
            ImGui::BeginGroup();
            {
                ImGui::Text("Filler Color");
                if (ImGui::ColorPicker3(
                        "##FillerColor", (float*)&canvas.m_filler_color, flags))
                {
                    if (canvas.IsSelected()) {
                        auto c = canvas.m_filler_color;
                        canvas.GetSelected()->SetFillColor(c.r, c.g, c.g);
                    }
                }
                ImGui::EndGroup();
            }

            ImGui::PopItemWidth();
            ImGui::End();
        }
    }
}
