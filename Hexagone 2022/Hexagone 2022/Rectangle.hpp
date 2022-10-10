#pragma once
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Drawable.hpp"

namespace sw
{
	class Rectangle : public Drawable
	{
		public:
			Rectangle(Origin origin = Center, Reference reference = Parent, Unit unit = Percent);
			Rectangle(const sf::FloatRect& rect, Origin origin = Center, Reference reference = Parent, Unit unit = Percent);
			Rectangle(const sf::Vector2f& position, const sf::Vector2f& size, Origin origin = Center, Reference reference = Parent, Unit unit = Percent);
			Rectangle(float posX, float posY, float width, float height, Origin origin = Center, Reference reference = Parent, Unit unit = Percent);

			void Reset(const sf::FloatRect& rect);
			void Reset(const sf::Vector2f& position, const sf::Vector2f& size);
			void Reset(float posX, float posY, float width, float height);

			sf::Color GetFillColor() const;
			void SetFillColor(const sf::Color& color);

			void SetOutline(float thickness, const sf::Color& color);

			float GetOutlineThickness() const;
			void SetOutlineThickness(float thickness);

			sf::Color GetOutlineColor() const;
			void SetOutlineColor(const sf::Color& color);

		private:
			sf::RectangleShape mRectangle;

			const sf::Vector2f& GetTruePosition() const;
			void SetTruePosition(const sf::Vector2f& position);

			const sf::Vector2f& GetTrueOrigin() const;
			void SetTrueOrigin(const sf::Vector2f& origin);

			sf::Vector2f GetTrueSize() const;
			void SetTrueSize(const sf::Vector2f& size);

		protected:
			sf::FloatRect GetLocalBounds() const;
			sf::FloatRect GetGlobalBounds() const;

			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}