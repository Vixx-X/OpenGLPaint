#include "UI/Shapes.h"
#include "Shapes/Base.h"
#include <iostream>

namespace GLPaint::UI {

    void ShapeTable(Canvas &canvas)
    {
        int &curr_idx = canvas.m_idx;
        for (size_t n = 0; n < canvas.m_primitives.size(); n++)
        {
            const bool is_selected = (curr_idx == n);
            auto item = canvas.m_primitives[n];
            auto value = item->to_string();

            if (ImGui::Selectable(value.c_str(), is_selected,
                        ImGuiSelectableFlags_AllowDoubleClick))
                if (ImGui::IsMouseDoubleClicked(0))
                    curr_idx = n;

            if (ImGui::IsItemActive() and !ImGui::IsItemHovered())
            {
                int n_next = n + (ImGui::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
                if (n_next >= 0 && n_next < canvas.m_primitives.size())
                {
                    canvas.m_primitives[n] = canvas.m_primitives[n_next];
                    canvas.m_primitives[n_next] = item;
                    if (is_selected) curr_idx = n_next;
                    ImGui::ResetMouseDragDelta();
                }
            }
        }
    }

    void ShapeSelector(Canvas &canvas)
    {
        int &curr_idx = canvas.m_idx;
        std::string selected = canvas.IsSelected() ?
            canvas.GetSelected()->to_string() : "";
        if (ImGui::BeginCombo("Selecciona la figura", selected.c_str()))
        {
            for (size_t n = 0; n < canvas.m_primitives.size(); n++)
            {
                const bool is_selected = (curr_idx == n);
                std::string value = canvas.m_primitives[n]->to_string() +
                    " ##Figure" + std::to_string(n);
                if (ImGui::Selectable(
                            value.c_str(),
                            is_selected))
                    curr_idx = n;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
    }

    void ShapeProperty(Canvas &canvas)
    {
        auto p = canvas.GetSelected();
        p->ui();

        if (ImGui::Button("Send Foreground")) {
            canvas.Foreground();
        }
        if (ImGui::Button("Send Background")) {
            canvas.Background();
        }
        if (ImGui::Button("Delete")) {
            canvas.Delete();
        }
    }

    void RenderShapesProperties(Canvas &canvas) {
        if (ImGui::Begin("Entities")) {
            ShapeTable(canvas);

            if (canvas.IsSelected()) {
                ShapeProperty(canvas);
            }

            ImGui::End();
        }
    }
}

void Shape::ui(bool allowFiller)
{
    if (allowFiller) {
        ImGui::Checkbox("Fill", &m_filled);
    }

    ImGui::ColorEdit3(
            "Border Color", (float*)&m_border_color);
    if (m_filled) {
        ImGui::ColorEdit4(
                "Filler Color", (float*)&m_filler_color);
    }
}

void Line::ui(bool allowFiller)
{
    Shape::ui(true);

    ImGuiIO& io = ImGui::GetIO();
    int w = (GLsizei)io.DisplaySize.x;
    int h = (GLsizei)io.DisplaySize.y;

    ImGui::SliderFloat("X0", &m_coords.x, 0.00f, w);
    ImGui::SliderFloat("Y0", &m_coords.y, 0.00f, h);

    ImGui::SliderFloat("X1", &m_coords.z, 0.00f, w);
    ImGui::SliderFloat("Y1", &m_coords.w, 0.00f, h);
}

void Triangle::ui(bool allowFiller)
{
    Shape::ui(true);

    ImGuiIO& io = ImGui::GetIO();
    int w = (GLsizei)io.DisplaySize.x;
    int h = (GLsizei)io.DisplaySize.y;

    for (int i=0; i<m_coords.size(); ++i) {
        std::string xLabel = "X" + std::to_string(i);
        ImGui::SliderFloat(xLabel.c_str(), &m_coords[i].x, 0.00f, w);
        std::string yLabel = "Y" + std::to_string(i);
        ImGui::SliderFloat(yLabel.c_str(), &m_coords[i].y, 0.00f, h);
    }
}

void Rectangle::ui(bool allowFiller)
{
    Shape::ui(true);

    ImGuiIO& io = ImGui::GetIO();
    int w = (GLsizei)io.DisplaySize.x;
    int h = (GLsizei)io.DisplaySize.y;

    ImGui::SliderFloat("X0", &m_coords.x, 0.00f, w);
    ImGui::SliderFloat("Y0", &m_coords.y, 0.00f, h);

    ImGui::SliderFloat("X1", &m_coords.z, 0.00f, w);
    ImGui::SliderFloat("Y1", &m_coords.w, 0.00f, h);
}

void Ellipse::ui(bool allowFiller)
{
    Shape::ui(true);

    ImGuiIO& io = ImGui::GetIO();
    int w = (GLsizei)io.DisplaySize.x;
    int h = (GLsizei)io.DisplaySize.y;

    ImGui::SliderFloat("X0", &m_coords.x, 0.00f, w);
    ImGui::SliderFloat("Y0", &m_coords.y, 0.00f, h);

    ImGui::SliderFloat("X1", &m_coords.z, 0.00f, w);
    ImGui::SliderFloat("Y1", &m_coords.w, 0.00f, h);
}

void Circle::ui(bool allowFiller)
{
    Shape::ui(true);

    ImGuiIO& io = ImGui::GetIO();
    int w = (GLsizei)io.DisplaySize.x;
    int h = (GLsizei)io.DisplaySize.y;

    ImGui::SliderFloat("X0", &m_coords.x, 0.00f, w);
    ImGui::SliderFloat("Y0", &m_coords.y, 0.00f, h);

    ImGui::SliderFloat("X1", &m_coords.z, 0.00f, w);
    ImGui::SliderFloat("Y1", &m_coords.w, 0.00f, h);
}

void Bezier::ui(bool allowFiller)
{
    Shape::ui(false);

    ImGui::SliderInt("N Sample", &m_sample, 1, 10000);

    ImGuiIO& io = ImGui::GetIO();
    int w = (GLsizei)io.DisplaySize.x;
    int h = (GLsizei)io.DisplaySize.y;

    int N = m_size;
    for (int i=0; i<N; ++i) {
        std::string xLabel = "X" + std::to_string(i);
        ImGui::SliderFloat(xLabel.c_str(), &m_coords[i].x, 0.00f, w);
        std::string yLabel = "Y" + std::to_string(i);
        ImGui::SliderFloat(yLabel.c_str(), &m_coords[i].y, 0.00f, h);
    }

    if (ImGui::Button("-")) {
        SetSize(N-1);
    }

    if (ImGui::Button("+")) {
        SetSize(N+1);
    }
}
