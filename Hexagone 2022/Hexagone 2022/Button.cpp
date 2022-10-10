#include "Button.hpp"
#include "Window.hpp"

namespace sw
{
	Button::Button(Origin origin, Reference reference, Unit unit) :
	Rectangle(origin, reference, unit)
	{
		mText.SetParent(this);
		mText.SetTransform(sw::Center, sw::Percent, sw::Parent);
		mText.SetSize(90 * mTextSize, 90 * mTextSize);
		mText.SetPosition(50.f, 50.f);
	}

	Button::Button(const sf::FloatRect& rect) :
	Rectangle(rect)
	{
		mText.SetParent(this);
		mText.SetTransform(sw::Center, sw::Percent, sw::Parent);
		mText.SetSize(90 * mTextSize, 90 * mTextSize);
		mText.SetPosition(50.f, 50.f);
	}

	Button::Button(const sf::Vector2f& position, const sf::Vector2f& size) :
	Rectangle(position, size)
	{
		mText.SetParent(this);
		mText.SetTransform(sw::Center, sw::Percent, sw::Parent);
		mText.SetSize(90 * mTextSize, 90 * mTextSize);
		mText.SetPosition(50.f, 50.f);
	}

	Button::Button(float posX, float posY, float width, float height) :
	Rectangle(posX, posY, width, height)
	{
		mText.SetParent(this);
		mText.SetTransform(sw::Center, sw::Percent, sw::Parent);
		mText.SetSize(90 * mTextSize, 90 * mTextSize);
		mText.SetPosition(50.f, 50.f);
	}

	Button::Button(const sf::FloatRect& rect, const sf::Font& font, const std::string& text, float textSize) :
	Rectangle(rect)
	{
		mText.SetFont(font);
		mText.SetText(text);
		mTextSize = textSize;
		mText.SetParent(this);
		mText.SetTransform(sw::Center, sw::Percent, sw::Parent);
		mText.SetSize(90 * mTextSize, 90 * mTextSize);
		mText.SetPosition(50.f, 50.f);
	}

	Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font, const std::string& text, float textSize) :
	Rectangle(position, size)
	{
		mText.SetFont(font);
		mText.SetText(text);
		mTextSize = textSize;
		mText.SetParent(this);
		mText.SetTransform(sw::Center, sw::Percent, sw::Parent);
		mText.SetSize(90 * mTextSize, 90 * mTextSize);
		mText.SetPosition(50.f, 50.f);
	}

	Button::Button(float posX, float posY, float width, float height, const sf::Font& font, const std::string& text, float textSize) :
	Rectangle(posX, posY, width, height)
	{
		mText.SetFont(font);
		mText.SetText(text);
		mTextSize = textSize;
		mText.SetParent(this);
		mText.SetTransform(sw::Center, sw::Percent, sw::Parent);
		mText.SetSize(90 * mTextSize, 90 * mTextSize);
		mText.SetPosition(50.f, 50.f);
	}

	std::string Button::GetText() const
	{
		return mText.GetText();
	}

	void Button::SetText(const std::string& text)
	{
		mText.SetText(text);
		mText.SetSize(90 * mTextSize, 90 * mTextSize);
		mText.SetPosition(50.f, 50.f);
	}

	float Button::GetTextSize() const
	{
		return mTextSize;
	}

	void Button::SetTextSize(float textSize)
	{
		mTextSize = textSize;
		mText.SetSize(90 * mTextSize, 90 * mTextSize);
		mText.SetPosition(50.f, 50.f);
	}

	sf::Color Button::GetTextColor()
	{
		return mText.GetFillColor();
	}

	void Button::SetTextColor(const sf::Color& color)
	{
		mText.SetFillColor(color);
	}

	bool Button::IsMouseHover()
	{
		return sw::Window::Main() == nullptr ? false : GetGlobalBounds().contains(sf::Vector2f(sw::Window::Main()->GetMousePosition()));
	}

	bool Button::IsMouseClick()
	{
		return IsMouseHover() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		Rectangle::draw(target, states);
		target.draw(mText);
	}
}