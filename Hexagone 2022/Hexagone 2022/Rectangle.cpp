#include "Rectangle.hpp"
#include "Rectangle.hpp"
#include <iostream>

namespace sw
{
	Rectangle::Rectangle(Origin origin, Reference reference, Unit unit)
	{
		SetSize(0.f, 0.f);

		SetOrigin(origin);
		SetReference(reference);
		SetUnit(unit);

		SetPosition(0.f, 0.f);
	}

	Rectangle::Rectangle(const sf::FloatRect& rect, Origin origin, Reference reference, Unit unit)
	{
		SetSize(rect.width, rect.height);

		SetOrigin(origin);
		SetReference(reference);
		SetUnit(unit);

		SetPosition(rect.left, rect.top);
	}

	Rectangle::Rectangle(const sf::Vector2f& position, const sf::Vector2f& size, Origin origin, Reference reference, Unit unit)
	{
		SetSize(size);

		SetOrigin(origin);
		SetReference(reference);
		SetUnit(unit);

		SetPosition(position);
	}

	Rectangle::Rectangle(float posX, float posY, float width, float height, Origin origin, Reference reference, Unit unit)
	{
		SetSize(width, height);

		SetOrigin(origin);
		SetReference(reference);
		SetUnit(unit);

		SetPosition(posX, posY);
	}

	void Rectangle::Reset(const sf::FloatRect& rect)
	{
		SetPosition(rect.left, rect.top);
		SetSize(rect.width, rect.height);
	}

	void Rectangle::Reset(const sf::Vector2f& position, const sf::Vector2f& size)
	{
		SetPosition(position);
		SetSize(size);
	}

	void Rectangle::Reset(float posX, float posY, float width, float height)
	{
		SetPosition(posX, posY);
		SetSize(width, height);
	}

	sf::Color Rectangle::GetFillColor() const
	{
		return mRectangle.getFillColor();
	}

	void Rectangle::SetFillColor(const sf::Color& color)
	{
		mRectangle.setFillColor(color);
	}

	void Rectangle::SetOutline(float thickness, const sf::Color& color)
	{
		mRectangle.setOutlineThickness(thickness);
		mRectangle.setOutlineColor(color);
	}
	
	float Rectangle::GetOutlineThickness() const
	{
		return mRectangle.getOutlineThickness();
	}

	void Rectangle::SetOutlineThickness(float thickness)
	{
		mRectangle.setOutlineThickness(thickness);
	}

	sf::Color Rectangle::GetOutlineColor() const
	{
		return mRectangle.getOutlineColor();
	}

	void Rectangle::SetOutlineColor(const sf::Color& color)
	{
		mRectangle.setOutlineColor(color);
	}

	const sf::Vector2f& Rectangle::GetTruePosition() const
	{
		return mRectangle.getPosition();
	}

	void Rectangle::SetTruePosition(const sf::Vector2f& position)
	{
		mRectangle.setPosition(position);
	}

	const sf::Vector2f& Rectangle::GetTrueOrigin() const
	{
		return mRectangle.getOrigin();
	}

	void Rectangle::SetTrueOrigin(const sf::Vector2f& origin)
	{
		mRectangle.setOrigin(origin);
	}

	sf::Vector2f Rectangle::GetTrueSize() const
	{
		return sf::Vector2f(mRectangle.getGlobalBounds().width, mRectangle.getGlobalBounds().height);
	}

	void Rectangle::SetTrueSize(const sf::Vector2f& size)
	{
		mRectangle.setSize(size);
	}

	sf::FloatRect Rectangle::GetLocalBounds() const
	{
		return mRectangle.getLocalBounds();
	}

	sf::FloatRect Rectangle::GetGlobalBounds() const
	{
		return mRectangle.getGlobalBounds();
	}

	void Rectangle::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(mRectangle, states);
	}
}