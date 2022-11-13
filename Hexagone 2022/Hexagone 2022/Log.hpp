#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "SFML/System/Vector3.hpp"

#include <vector>

class Log
{
	public:
		static void Init();

		static void Print(const std::string& message);
		static void Print(const sf::Vector2f& message);
		static void Print(const sf::Vector3i& message);

		static const std::vector<std::string>& GetMessages();

	private:
		Log();

		std::vector<std::string> mMessages;

		static Log* mInstance;
};
