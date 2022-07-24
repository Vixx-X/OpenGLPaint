#include "UI/Menu.h"
#include <iostream>

namespace GLPaint::UI
{
    static void ShowFileMenu(Canvas &canvas)
    {
        if (ImGui::MenuItem("New", "x (Clear)")) {
            canvas.Clear();
        }
        if (ImGui::MenuItem("Open", "L")) {
            canvas.Load();
        }
        if (ImGui::MenuItem("Save As..", "s")) {
            canvas.Save();
        }
    }

    static void ShowRenderMenu(Canvas &canvas)
    {
        if (ImGui::MenuItem(
                    "Hardware Accelerated", NULL, canvas.m_hardware_acc)) {
            canvas.ToggleHardwareAcceleration();
        }
        if (ImGui::BeginMenu("Background Color")) {
            ImGui::ColorPicker4(
                    "Background Color", (float*)&canvas.m_bg_color);
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Point Size")) {
            ImGui::SliderFloat(
                    "Point Size", &canvas.m_psize, 1.0f, 100.0f);
            ImGui::EndMenu();
        }
    }

    void RenderMenuBar(Canvas &canvas)
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                ShowFileMenu(canvas);
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Render"))
            {
                ShowRenderMenu(canvas);
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }
}
