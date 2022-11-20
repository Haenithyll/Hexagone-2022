#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "SFML/System/Vector3.hpp"
#include "Character.hpp"

#include <vector>

class Message
{
	public:
		std::string Text;
		ImU32 Color;

		Message();
		Message(const std::string& message);
		Message(const std::string& message, Party party);	
};

class Log
{
	public:
		static void Init();

		static void Print(const std::string& message);
		static void Print(const std::string& message, Party party);
		static void Print(const sf::Vector2f& message);
		static void Print(const sf::Vector3i& message);

		static void BreakLine();

		static void Show();

	private:
		Log();

		bool mLookScroll = true;

		std::vector<Message> mMessages;

		static Log* mInstance;
};
