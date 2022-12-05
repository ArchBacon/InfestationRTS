#pragma once

#include "Window/Window.h"

class Input
{
public:
    Input() = default;
    ~Input() = default;

    void PollInputEvents(MyWindow* window);
};
