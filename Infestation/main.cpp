#include <GLES3/gl31.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Window/XWindow.h"

int main(int argc, char* argv[])
{
    // Create window and initialize EGL context
    const auto window = new XWindow(640, 480, "Hello Window!");

    const char* glsl_version = "#version 100";

    // Init ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.DisplaySize = ImVec2(window->GetWidth(), window->GetHeight());
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplOpenGL3_Init(glsl_version);

    while (window->IsValid())
    {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        // Poll input events
        Window window_returned;

        int root_x, root_y;
        int win_x, win_y;
        uint mask_return;
        XQueryPointer(
            window->GetNativeDisplay(),
            window->GetNativeWindow(),
            &window_returned, &window_returned, // Window in which the cursor position is taken from
            &root_x, &root_y,                   // cursor position on screen
            &win_x, &win_y,                     // cursor position on window
            &mask_return
        );

        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.MousePos = ImVec2(static_cast<float>(win_x), static_cast<float>(win_y));
        io.MouseDown[0] = mask_return & (1 << 8); // left
        io.MouseDown[1] = mask_return & (1 << 10); // right

        // Create ImGui windows
        ImGui::Begin("Another Window");
            ImGui::Text("Hello from another window!");
            ImGui::Button("Button");
        ImGui::End();

        // Render
        ImGui::Render();
        glViewport(0, 0, window->GetWidth(), window->GetHeight());
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap egl buffers
        window->SwapBuffers();
    }

    ImGui::DestroyContext();
    delete window;

    return 0;
}
