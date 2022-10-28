#include "Character.hpp"
#include "AssetManager.hpp"

void Character::ReceiveMessages(const Messages* newMessages, int amountToTake)
{
	for (const std::string* message : *newMessages)
	{
		if (std::find(_messages.begin(), _messages.end(), message) == _messages.end())//message not in _messages
		{
			_messages.push_back(message);
			if (--amountToTake < 1)
				break;
		}
	}
}

void Character::AddMessage(const std::string* message)
{
	_messages.push_back(message);
}

void Character::DeleteMessage(int index)
{
	_messages.erase(_messages.begin() + index);
}

bool Character::LoseEnergy()
{
	return _energyPoints-- <= 0;
}

void Character::SetDrawState(bool idle)
{
	mIdle = idle;
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	const int nColumns = 4;
	const int frameSize = 50;

	const float dotRadius = 5.f;
	const float dotGap = 5.f;

	int row = mIndex / nColumns;
	int column = mIndex % nColumns;

	if (IsMoving())
		column += nColumns;

	sf::Sprite sprite(AssetManager::GetTexture("Character"), sf::IntRect(column * frameSize, row * frameSize, frameSize, frameSize));
	sprite.setOrigin(sf::Vector2f(frameSize / 2.f, frameSize / 2.f));

	sf::Vector2f center = GetDrawPosition();

	sprite.setPosition(center);
	sprite.setRotation(GetDrawRotation());

	sf::CircleShape dot(dotRadius);
	dot.setOrigin(0.f, dotRadius / 2.f);
	dot.setFillColor(sf::Color::Red);

	sf::Text name(_name, AssetManager::GetFont("Default"), 12u);
	name.setOrigin(0.f, name.getGlobalBounds().height / 2.f);
	name.setFillColor(sf::Color::White);
	name.setOutlineThickness(0.5f);
	name.setOutlineColor(sf::Color::Black);

	float dotSpace = dotRadius  * 2.f + dotGap;
	float width = dotSpace + name.getGlobalBounds().width;

	dot.setPosition(center.x - width / 2.f, center.y - 50.f);
	name.setPosition(center.x - width / 2.f + dotSpace, center.y - 50.f);

	target.draw(sprite, states);
	target.draw(dot, states);
	target.draw(name, states);
}
