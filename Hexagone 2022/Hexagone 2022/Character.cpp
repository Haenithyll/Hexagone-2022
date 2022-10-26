#include "Character.hpp"
#include "TextureManager.hpp"

void Character::ReceiveMessages(const std::vector<const std::string*>* newMessages, int amountToTake)
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
void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	int row = mIndex / 4;
	int column = mIndex % 4;

	sf::Sprite sprite(TextureManager::GetTexture("Character"), sf::IntRect(column * 50, row * 50, 50, 50));

	sprite.setOrigin(sf::Vector2f(25.f, 25.f));
	sprite.setPosition(sf::Vector2f());

	target.draw(sprite);
}
