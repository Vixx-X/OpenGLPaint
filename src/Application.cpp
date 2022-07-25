#include "Application.h"
#include <iostream>

namespace GLPaint
{

    static Canvas canvas; // app states and/or stores
    static Gizmo* gizmo;
    static ImGuiDockNodeFlags dockspace_flags =
        ImGuiDockNodeFlags_PassthruCentralNode;

    void RenderUI()
    {
        ImGui::PushID("MainWindow");
        ImGui::DockSpaceOverViewport(NULL, dockspace_flags);
        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(
                        "PUSH_SHAPE"))
                canvas.AddPrimitive(std::string((char*)payload));

            ImGui::EndDragDropTarget();
        }
        ImGui::PopID();

        ImGui::ShowDemoWindow(NULL);

        UI::RenderMenuBar(canvas);
        UI::RenderPalette(canvas);
        UI::RenderShapesProperties(canvas);

        if (gizmo and (!canvas.IsSelected() or
                    (canvas.GetSelected() != gizmo->shape))) {
            delete gizmo;
            gizmo = nullptr;
        }

        if (canvas.IsSelected() and !gizmo) {
            gizmo = new Gizmo(canvas.GetSelected(),
                    &canvas.m_gizmo_color, &canvas.m_gizmo_psize);
        }
    }

    void Render()
    {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGLUT_NewFrame();

        RenderUI();

        // Rendering
        ImGui::Render();
        ImGuiIO& io = ImGui::GetIO();

        int w = (GLsizei)io.DisplaySize.x;
        int h = (GLsizei)io.DisplaySize.y;
        canvas.m_W = w, canvas.m_H = h;
        auto clear_color = canvas.m_bg_color;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(canvas.m_Wx, w*canvas.m_D, canvas.m_Hy, h*canvas.m_D, -1, 1);

        glViewport(0, 0, w, h);
        glClearColor(
                clear_color.x * clear_color.w,
                clear_color.y * clear_color.w,
                clear_color.z * clear_color.w,
                clear_color.w
                );
        glClear(GL_COLOR_BUFFER_BIT);

        // render the actual canvas
        glPointSize(canvas.m_psize);
        glLineWidth(canvas.m_psize);
        canvas.Render();
        if (gizmo) gizmo->Render();

        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

        glutSwapBuffers();
        glutPostRedisplay();
    }

    void HandlingKeyEvents(unsigned char key, int x, int y)
    {
        ImGui_ImplGLUT_KeyboardFunc(key, x, y); // calling ImGui handler

        ImGuiIO& io = ImGui::GetIO();
        if (!io.WantCaptureKeyboard) {
            switch(key) {
                case '1':
                    // Line
                    canvas.AddPrimitive("LINE");
                    break;
                case '2':
                    // Circle
                    canvas.AddPrimitive("CIRCLE");
                    break;
                case '3':
                    // Ellipse
                    canvas.AddPrimitive("ELLIPSE");
                    break;
                case '4':
                    // Rectangle
                    canvas.AddPrimitive("RECTANGLE");
                    break;
                case '5':
                    // Triangle
                    canvas.AddPrimitive("TRIANGLE");
                    break;
                case '6':
                    // Bezier3
                    canvas.AddPrimitive("Bezier3");
                    break;
                case 's':
                    // save
                    canvas.Save();
                    break;
                case 'L':
                    // load
                    canvas.Load();
                    break;
                case 'x':
                    // clear
                    canvas.Clear();
                    break;
                case 'c':
                    // change border color
                    if (canvas.IsSelected()) {}
                    break;
                case 'r':
                    // change filler color
                    if (canvas.IsSelected()) {}
                    break;
                case 'h':
                    // toggle hardware acc
                    canvas.ToggleHardwareAcceleration();
                    break;
                case 'f':
                    // send to foreground
                    if (canvas.IsSelected())
                        canvas.Foreground();
                    break;
                case 'b':
                    // send to background
                    if (canvas.IsSelected())
                        canvas.Background();
                    break;
                case '-':
                    // send to foreground
                    if (canvas.IsSelected())
                        canvas.Up();
                    break;
                case '+':
                    // send to background
                    if (canvas.IsSelected())
                        canvas.Down();
                    break;
                case 'u':
                    // unselect
                    canvas.Unselect(); // dont need to check
                    break;
                    /* case 8: */
                case 127:
                    // delete
                    if (canvas.IsSelected())
                        canvas.Delete();
                    break;
                default:
                    break;
            }
        }

        glutPostRedisplay();
    }

    void HandlingMouseEvent(int glut_button, int state, int x, int y)
    {
        ImGui_ImplGLUT_MouseFunc(glut_button, state, x, y);

        ImGuiIO& io = ImGui::GetIO();
        int h = (GLsizei)io.DisplaySize.y;

        if (!io.WantCaptureMouse and glut_button == GLUT_LEFT_BUTTON) {
            if (!(gizmo and (gizmo->IsEditing or gizmo->Select(x, h - y)))) {
                canvas.Select(x, h - y);
            }
        }
    }

    void ImGui_ImplGLUT_InstallCustomFuncs()
    {
        glutReshapeFunc(ImGui_ImplGLUT_ReshapeFunc);
        glutMotionFunc(ImGui_ImplGLUT_MotionFunc);
        glutPassiveMotionFunc(ImGui_ImplGLUT_MotionFunc);
        glutMouseFunc(HandlingMouseEvent);
#ifdef __FREEGLUT_EXT_H__
        glutMouseWheelFunc(ImGui_ImplGLUT_MouseWheelFunc);
#endif
        glutKeyboardFunc(HandlingKeyEvents);
        glutKeyboardUpFunc(ImGui_ImplGLUT_KeyboardUpFunc);
        glutSpecialFunc(ImGui_ImplGLUT_SpecialFunc);
        glutSpecialUpFunc(ImGui_ImplGLUT_SpecialUpFunc);
    }

    void Start(const char* title, int argc, char** argv)
    {
        // Create GLUT window
        glutInit(&argc, argv);
        glutKeyboardFunc(HandlingKeyEvents);
#ifdef __FREEGLUT_EXT_H__
        glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
#endif
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
        glutInitWindowSize(1280, 720);
        glutCreateWindow(title);

        // Setup GLUT display function
        glutDisplayFunc(Render);

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

        ImGui::StyleColorsDark();

        ImGui_ImplGLUT_Init();
        ImGui_ImplGLUT_InstallCustomFuncs(); // Overrided with custom hanlders
        ImGui_ImplOpenGL2_Init();

        glutMainLoop();

        // Cleanup
        ImGui_ImplOpenGL2_Shutdown();
        ImGui_ImplGLUT_Shutdown();
        ImGui::DestroyContext();
    }
}
