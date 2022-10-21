#pragma once

#include <string>

#include "Events.hpp"
#include "View.hpp"
#include "Drawable.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

namespace sw
{
	class Window
	{
		public:
			Window(const std::string& title, const sf::Vector2u& size, const sf::Vector2i& position);
			Window(const std::string& title, unsigned int sizeX, unsigned int sizeY, int positionX, int positionY);

			void Create(bool fullscreen = false, unsigned int antialiasing = 0u, unsigned int framerate = 60u);
			void Destroy();

			bool IsOpen();
			float GetDeltaTime() const;

			EventsData HandleEvents();
			void Clear(const sf::Color& color);

			void Draw(const sf::Drawable& drawable);
			void Display() const;

			sf::Vector2u GetSize() const;
			
			sf::Vector2f GetMousePosition(bool useView = false) const;

			View GetDefaultView() const;

			void ResetView();
			void SetView(const sf::View& view);

			sf::Vector2f MapToCoord(const sf::Vector2f& point) const;
			sf::Vector2f CoordToMap(const sf::Vector2f& point) const;

			static const Window* Main();

		private:
			sf::RenderWindow* mWindow;
			EventsHandler mEvents;

			std::string mTitle;
			sf::Vector2u mSize;
			sf::Vector2i mPosition;

			sf::Time mDeltaTime;
			sf::Clock mClock;

			static Window* mMain;
	};
}