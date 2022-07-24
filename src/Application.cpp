#include "Application.h"
#include <iostream>

namespace GLPaint
{

    static Canvas canvas; // app states and/or stores
    static ImGuiDockNodeFlags dockspace_flags =
        ImGuiDockNodeFlags_PassthruCentralNode;

    void RenderUI()
    {
        ImGui::DockSpaceOverViewport(NULL, dockspace_flags);
        ImGui::ShowDemoWindow(NULL);

        UI::RenderMenuBar(canvas);
        UI::RenderPalette(canvas);
        UI::RenderShapesProperties(canvas);
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
        auto clear_color = canvas.m_bg_color;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, w/2, 0, h/2, -1, 1);

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

        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

        glutSwapBuffers();
        glutPostRedisplay();
    }

    void HandlingKeyEvents(unsigned char key, int x, int y)
    {
        switch(key) {
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

        ImGui_ImplGLUT_KeyboardFunc(key, x, y); // calling ImGui handler
        glutPostRedisplay();
    }

    void ImGui_ImplGLUT_InstallCustomFuncs()
    {
        glutReshapeFunc(ImGui_ImplGLUT_ReshapeFunc);
        glutMotionFunc(ImGui_ImplGLUT_MotionFunc);
        glutPassiveMotionFunc(ImGui_ImplGLUT_MotionFunc);
        glutMouseFunc(ImGui_ImplGLUT_MouseFunc);
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
