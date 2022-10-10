#pragma once

#include "Window.hpp"

class Screen
{
	public:
		virtual int Run(sw::Window& window) = 0;
};