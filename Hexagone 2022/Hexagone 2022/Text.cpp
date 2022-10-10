#include "Text.hpp"

namespace sw
{
	Text::Text(Origin origin, Reference reference, Unit unit)
	{
		SetOrigin(origin);
		SetReference(reference);
		SetUnit(unit);

		SetSize(0, 0);
		SetPosition(0, 0);
	}

	Text::Text(const sf::Font& font, const std::string& text, Origin origin, Reference reference, Unit unit)
	{
		mText.setFont(font);

		mText.setString(text);

		SetOrigin(origin);
		SetReference(reference);
		SetUnit(unit);

		SetSize(0, 0);
		SetPosition(0, 0);
	}

	void Text::Reset(const sf::Font& font, const std::string& text)
	{
		mText.setFont(font);

		mText.setString(text);
	}

	void Text::SetFont(const sf::Font& font)
	{
		mText.setFont(font);
	}

	std::string Text::GetText() const
	{
		return mText.getString();
	}

	void Text::SetText(const std::string& text)
	{
		mText.setString(text);
	}

	sf::Color Text::GetFillColor() const
	{
		return mText.getFillColor();
	}

	void Text::SetFillColor(const sf::Color& color)
	{
		mText.setFillColor(color);
	}

	void Text::SetOutline(float thickness, const sf::Color& color)
	{
		mText.setOutlineThickness(thickness);
		mText.setOutlineColor(color);
	}

	float Text::GetOutlineThickness() const
	{
		return mText.getOutlineThickness();
	}

	void Text::SetOutlineThickness(float thickness)
	{
		mText.setOutlineThickness(thickness);
	}

	sf::Color Text::GetOutlineColor() const
	{
		return mText.getOutlineColor();
	}

	void Text::SetOutlineColor(const sf::Color& color)
	{
		mText.setOutlineColor(color);
	}

	const sf::Vector2f& Text::GetTruePosition() const
	{
		return mText.getPosition();
	}

	void Text::SetTruePosition(const sf::Vector2f& position)
	{
		mText.setPosition(position);
	}

	const sf::Vector2f& Text::GetTrueOrigin() const
	{
		return mText.getOrigin();
	}

	void Text::SetTrueOrigin(const sf::Vector2f& origin)
	{
		mText.setOrigin(origin);
	}

	sf::Vector2f Text::GetTrueSize() const
	{
		return sf::Vector2f(mText.getGlobalBounds().width, mText.getGlobalBounds().height);
	}

	void Text::SetTrueSize(const sf::Vector2f& size)
	{
		mText.setCharacterSize((unsigned)size.y);
		if (mText.getGlobalBounds().width > size.x) mText.setCharacterSize((unsigned)(mText.getCharacterSize() * size.x / mText.getGlobalBounds().width));
	}

	sf::FloatRect Text::GetLocalBounds() const
	{
		return mText.getLocalBounds();
	}

	sf::FloatRect Text::GetGlobalBounds() const
	{
		return mText.getGlobalBounds();
	}

	void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(mText, states);
	}
}