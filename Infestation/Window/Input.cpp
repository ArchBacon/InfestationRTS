#include "Input.h"
#include <X11/Xlib.h>
#include <imgui.h>

void Input::PollInputEvents(XWindow* window)
{
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
}
