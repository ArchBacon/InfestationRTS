#include "Window.h"
#include <cstdio>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include "Context.h"

MyWindow::MyWindow(const int width, const int height, const char* title)
    : props({0, 0, width, height, title})
{
    windowCreated = CreateWindow(width, height, title);
    eglContext = new Context(GetNativeWindow());
    InitializeImGui();
}

void MyWindow::Destroy()
{
    destroyed = true;
    ImGui::DestroyContext();
    XCloseDisplay(display);
}

bool MyWindow::IsValid() const
{
    return windowCreated && !destroyed;
}

void MyWindow::SwapBuffers() const
{
    eglSwapBuffers(eglContext->GetDisplay(), eglContext->GetSurface());
}

bool MyWindow::CreateWindow(int width, int height, const char* title)
{
    XSetWindowAttributes swa;
    swa.event_mask = ExposureMask | PointerMotionMask | KeyPressMask;

    display = XOpenDisplay(nullptr);
    if (display == nullptr)
    {
        printf("X11 ERROR: Could not get display. %i\n", eglGetError());
        return false;
    }

    window = XCreateWindow(
        display,
        DefaultRootWindow(display),
        props.x, props.y, // window position
        width, height, // window height
        2, // border width
        CopyFromParent, // depth
        CopyFromParent, // class
        CopyFromParent, // visual
        CopyFromParent, // value mask
        &swa // attributes
        );

    XMapWindow(display, window);
    XStoreName(display, window, title);

    XEvent xev = {};
    xev.type = ClientMessage;
    xev.xclient.window = window;
    xev.xclient.message_type = XInternAtom(display, "_NET_WM_STATE", 0);
    xev.xclient.format = 32;
    xev.xclient.data.l[0] = 1;
    xev.xclient.data.l[1] = 0;

    XSendEvent(display, DefaultRootWindow(display), 0, SubstructureNotifyMask, &xev);

    return true;
}

void MyWindow::InitializeImGui()
{
    // Init ImGui
    auto glsl_version = "#version 100";

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.DisplaySize = ImVec2(static_cast<float>(GetWidth()), static_cast<float>(GetHeight()));
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplOpenGL3_Init(glsl_version);
}
