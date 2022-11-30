#pragma once

#include "XWindow.h"

class Input
{
public:
	Input() = default;
	~Input() = default;

	void PollInputEvents(XWindow* window);
};
