#include "Window.hpp"

#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

namespace sw
{
	Window::Window(const std::string& title, const sf::Vector2u& size, const sf::Vector2i& position)
	{
		mTitle = title;
		mSize = size;
		mPosition = position;

		mWindow = new sf::RenderWindow();

		ImGui::SFML::Init(*mWindow);

		if (mMain == nullptr)
			mMain = this;
	}

	Window::Window(const std::string& title, unsigned int sizeX, unsigned int sizeY, int posX, int posY)
	{
		mTitle = title;
		mSize = sf::Vector2u(sizeX, sizeY);
		mPosition = sf::Vector2i(posX, posY);

		mWindow = new sf::RenderWindow();

		ImGui::SFML::Init(*mWindow);

		if (mMain == nullptr)
			mMain = this;
	}

	void Window::Create(bool fullscreen, unsigned int antialiasing, unsigned int framerate)
	{
		sf::ContextSettings cs;

		cs.antialiasingLevel = antialiasing;

		sf::VideoMode size = fullscreen ? sf::VideoMode::getFullscreenModes()[0] : sf::VideoMode(mSize.x, mSize.y);

		mWindow->create(size, mTitle, fullscreen ? sf::Style::Fullscreen : (sf::Style::Titlebar | sf::Style::Close), cs);
		mWindow->setFramerateLimit(framerate);
	}

	void Window::Destroy()
	{
		mWindow->close();
	}

	bool Window::IsOpen()
	{
		mDeltaTime = mClock.restart();

		return mWindow->isOpen();
	}

	float Window::GetDeltaTime() const
	{
		return mDeltaTime.asSeconds();
	}

	EventsData Window::HandleEvents()
	{
		mEvents.StartHandling();

		sf::Event event;

		while (mWindow->pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(*mWindow, event);

			switch (event.type)
			{
				case sf::Event::EventType::Closed:
					mEvents.close = true;

					break;

				case sf::Event::EventType::Resized:
					mEvents.resized = true;
					break;

				case sf::Event::EventType::KeyPressed:
					mEvents.keyPressed = true;

					mEvents.UKeyPressed(event.key.code);

					break;

				case sf::Event::EventType::KeyReleased:
					mEvents.keyReleased = true;

					mEvents.UKeyReleased(event.key.code);

					break;

				case sf::Event::EventType::MouseMoved:
					mEvents.mouseMove = true;

					break;

				case sf::Event::EventType::MouseWheelScrolled:
					mEvents.mouseWheelDown = event.mouseWheelScroll.delta < 0;
					mEvents.mouseWheelUp = event.mouseWheelScroll.delta > 0;

					break;

				case sf::Event::EventType::MouseButtonPressed:
					mEvents.leftClick = event.mouseButton.button == sf::Mouse::Button::Left;
					mEvents.rightClick = event.mouseButton.button == sf::Mouse::Button::Right;

					break;

				case sf::Event::EventType::TextEntered:
					mEvents.textEntered += event.text.unicode;

				default:
					break;
			}
		}

		ImGui::SFML::Update(*mWindow, mDeltaTime);

		return mEvents.FinishHandling();
	}

	void Window::Clear(const sf::Color& color)
	{
		mWindow->clear(color);
	}

	void Window::Draw(const sf::Drawable& drawable)
	{
		mWindow->draw(drawable);
	}

	void Window::Display() const
	{
		ImGui::SFML::Render(*mWindow);

		mWindow->display();
	}

	sf::Vector2u Window::GetSize() const
	{
		return mWindow->getSize();
	}

	sf::Vector2f Window::GetMousePosition(bool useView) const
	{
		return useView ? MapToCoord(sf::Vector2f(sf::Mouse::getPosition(*mWindow))) : sf::Vector2f(sf::Mouse::getPosition(*mWindow));
	}

	View Window::GetDefaultView() const
	{
		return sw::View(mWindow->getDefaultView());
	}

	void Window::ResetView()
	{
		SetView(GetDefaultView());
	}

	void Window::SetView(const sf::View& view)
	{
		mWindow->setView(view);
	}

	sf::Vector2f Window::MapToCoord(const sf::Vector2f& point) const
	{
		return mWindow->mapPixelToCoords(sf::Vector2i(point));
	}

	sf::Vector2f Window::CoordToMap(const sf::Vector2f& point) const
	{
		return sf::Vector2f(mWindow->mapCoordsToPixel(point));
	}

	const Window* Window::Main()
	{
		return mMain;
	}

	Window* Window::mMain;
}