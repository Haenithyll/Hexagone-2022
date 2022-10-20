#pragma once

#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Drawable.hpp"
#include <iostream>

namespace sw
{
	class Text : public Drawable
	{
		public:
			Text(Origin origin = Center, Reference reference = Parent, Unit unit = Percent);
			Text(const sf::Font& font, const std::string& text, Origin origin = Center, Reference reference = Parent, Unit unit = Percent);

			void Reset(const sf::Font& font, const std::string& text);

			void SetFont(const sf::Font& font);

			std::string GetText() const;
			void SetText(const std::string& text);
			
			sf::Color GetFillColor() const;
			void SetFillColor(const sf::Color& color);

			void SetOutline(float thickness, const sf::Color& color);

			float GetOutlineThickness() const;
			void SetOutlineThickness(float thickness);

			sf::Color GetOutlineColor() const;
			void SetOutlineColor(const sf::Color& color);

		private:
			sf::Text mText;
			sf::Font mFont;

		public:
				const sf::Vector2f& GetTruePosition() const;
				void SetTruePosition(const sf::Vector2f& position);

		private:
				const sf::Vector2f& GetTrueOrigin() const;
				void SetTrueOrigin(const sf::Vector2f& origin);

				sf::Vector2f GetTrueSize() const;
				void SetTrueSize(const sf::Vector2f& size);

		protected:
			sf::FloatRect GetLocalBounds() const;
			sf::FloatRect GetGlobalBounds() const;

			void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}