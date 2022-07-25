#include "Gizmo.h"

#include <iostream>

void DrawCircle(float x, float y, float size, Vec4 color)
{
    float aux_size;
    glGetFloatv(GL_POINT_SIZE, &aux_size);
    glPointSize(size);
    glColor3f(color.x, color.y, color.z);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
    glPointSize(aux_size);
}

void Gizmo::PutCircle(float x, float y)
{
    DrawCircle(x, y, *m_circle_size + 2, Vec4());
    DrawCircle(x, y, *m_circle_size, *m_color);
}

bool Gizmo::Select(float x, float y)
{
    auto points = shape->GetVertex();
    Vec2 pos = {x, y};
    for (int i=0; i < points.size(); i+=2) {
        Vec2 p = {points[i], points[i + 1]};
        if (p.dist(pos) <= *m_circle_size) {
            m_editing_idx = i;
            return true;
        }
    }
    if (shape->OnClick(pos.x, pos.y)) {
        m_editing_idx = -2;
        return true;
    }
    m_editing_idx = -1;
    return false;
}

void Gizmo::Render()
{
    auto points = shape->GetVertex();
    bool didEdit = false;
    bool canEdit = ImGui::IsMouseDown(0);

    ImGuiIO& io = ImGui::GetIO();
    int h = (GLsizei)io.DisplaySize.y;
    Vec2 pos = {ImGui::GetMousePos().x, h - ImGui::GetMousePos().y};

    if (m_prev.x == -1) {
        m_prev = {pos.x, pos.y};
    }

    for (int i=0; i < points.size(); i+=2) {
        Vec2 p = {points[i], points[i + 1]};
        if (!didEdit and canEdit and m_editing_idx != -2 and
            (p.dist(pos) <= *m_circle_size or m_editing_idx == i)) {
            points[i    ].get() = pos.x;
            points[i + 1].get() = pos.y;
            didEdit = true;
            m_editing_idx = i;
        }
        PutCircle(p.x, p.y);
    }

    IsEditing = didEdit;

    if (!didEdit and m_editing_idx != -2) {
        m_editing_idx = -1;
    }

    if (!didEdit and canEdit) {
        if (shape->OnClick(pos.x, pos.y) or m_editing_idx == -2) {
            shape->OnMove(
                pos.x - m_prev.x,
                pos.y - m_prev.y
            );
            m_prev = {pos.x, pos.y};
            m_editing_idx = -2;
            return;
        }
    }

    m_prev = {-1, -1};
    m_editing_idx = -1;
}
