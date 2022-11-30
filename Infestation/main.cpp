#include <GLES3/gl31.h>
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "Window/XWindow.h"
#include "Window/Input.h"

int main(int argc, char* argv[])
{
    // Create window and initialize EGL context
    const auto window = new XWindow(640, 480, "Hello Window!");
    const auto input = new Input();

    while (window->IsValid())
    {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        // Poll input events
        input->PollInputEvents(window);

        // Render
        ImGui::Render();
        glViewport(0, 0, window->GetWidth(), window->GetHeight());
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap egl buffers
        window->SwapBuffers();
    }

    delete window;

    return 0;
}
