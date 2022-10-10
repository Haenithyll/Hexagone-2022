#include "Events.hpp"

namespace sw
{
	EventsData::EventsData()
	{
		for (int i = 0; i < Key::KeyCount; i++)
		{
			mKeys.insert(std::pair<Key, KeyState>((Key)i, KeyState::None));
		}
	}

	bool EventsData::IsKeyPressed(Key key)
	{
		return key == Key::Unknown ? keyPressed : mKeys[key] == KeyState::Pressed;
	}

	bool EventsData::IsKeyHeld(Key key)
	{
		return mKeys[key] == KeyState::Held;
	}

	bool EventsData::IsKeyReleased(Key key)
	{
		return mKeys[key] == KeyState::Released;
	}

	bool EventsData::IsKeyDown(Key key)
	{
		return mKeys[key] == KeyState::Pressed || mKeys[key] == KeyState::Held;
	}

	bool EventsData::IsKeyNone(Key key)
	{
		return mKeys[key] == KeyState::None;
	}

	KeyState EventsData::GetKeyState(Key key)
	{
		return mKeys[key];
	}

	void EventsHandler::StartHandling()
	{
		close = false;
		resized = false;
		keyPressed = false;
		keyReleased = false;
		mouseMove = false;
		leftClick = false;
		rightClick = false;
		mouseWheelDown = false;
		mouseWheelUp = false;
		textEntered = "";

		for (int i = 0; i < Key::KeyCount; i++)
		{
			if (mKeys[(Key)i] == KeyState::Released) mKeys[(Key)i] = KeyState::None;
			else if (mKeys[(Key)i] == KeyState::Pressed) mKeys[(Key)i] = KeyState::Held;
		}
	}

	void EventsHandler::UKeyPressed(Key key)
	{
		if (key < mKeys.size()) if (mKeys[key] != KeyState::Held) mKeys[key] = KeyState::Pressed;
	}

	void EventsHandler::UKeyReleased(sf::Keyboard::Key key)
	{
		if (key < mKeys.size()) mKeys[key] = KeyState::Released;
	}

	EventsData EventsHandler::FinishHandling()
	{
		return (EventsData)* this;
	}
}