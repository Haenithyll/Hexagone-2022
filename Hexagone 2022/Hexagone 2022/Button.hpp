#pragma once
#include "Text.hpp"
#include "Rectangle.hpp"

namespace sw
{
	class Button : public Rectangle
	{
		public:
			Button(Origin origin = Center, Reference reference = Parent, Unit unit = Percent);

			Button(const sf::FloatRect& rect);
			Button(const sf::Vector2f& position, const sf::Vector2f& size);
			Button(float posX, float posY, float width, float height);

			Button(const sf::FloatRect& rect, const sf::Font& font, const std::string& text, float textSize = 0.9f);
			Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font, const std::string& text, float textSize = 0.9f);
			Button(float posX, float posY, float width, float height, const sf::Font& font, const std::string& text, float textSize = 0.9f);

			std::string GetText() const;
			void SetText(const std::string& text);

			float GetTextSize() const;
			void SetTextSize(float textSize);

			sf::Color GetTextColor();
			void SetTextColor(const sf::Color& color);

			bool IsMouseHover();
			bool IsMouseClick();

		private:
			Text mText;
			float mTextSize = 0.9f;

			void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}