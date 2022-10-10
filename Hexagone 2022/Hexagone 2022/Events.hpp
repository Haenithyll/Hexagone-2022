#pragma once
#include <map>
#include "SFML/Window/Event.hpp"

namespace sw
{
	typedef sf::Keyboard::Key Key;

	enum KeyState
	{
		Pressed,
		Held,
		Released,
		None
	};

	struct EventsData
	{
		public:
			EventsData();

			bool IsKeyPressed(Key key);
			bool IsKeyHeld(Key key);
			bool IsKeyReleased(Key key);
			bool IsKeyDown(Key key);
			bool IsKeyNone(Key key);

			KeyState GetKeyState(Key key);

			bool close = false;
			bool resized = false;
			bool keyPressed = false;
			bool keyReleased = false;
			bool mouseMove = false;
			bool leftClick = false;
			bool rightClick = false;
			bool mouseWheelUp = false;
			bool mouseWheelDown = false;
			std::string textEntered;

		protected:
			std::map<Key, KeyState> mKeys;
	};

	struct EventsHandler : public EventsData
	{
		void StartHandling();

		void UKeyPressed(Key key);
		void UKeyReleased(Key key);

		EventsData FinishHandling();
	};
}