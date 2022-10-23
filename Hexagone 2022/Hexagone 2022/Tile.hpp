#pragma once

#include <vector>
#include <array>

#include "Drawable.hpp"
#include "SFML/System/Vector3.hpp"
#include "Character.hpp"


class Tile {
public:

	Tile(const sf::Vector3i& coordinates);

	sf::Vector2f Position() const;
	sf::Vector3i Coordinates() const;
	bool Obstacle() const;
	Party GetParty() const;
	const Character* GetCharacter() const;
	const std::vector<Tile*>& SurroundingTiles();

	void AddSurroundingTile(Tile*);
	void SetObstacle();
	void SetParty(Party);
	void SetCharacter(Character*);
	void FreeTile();

private:
	sf::Vector2f _position_;
	sf::Vector3i _coordinates_;
	std::vector<Tile*> _surroundingTiles_;

	bool _obstacle_{ false };
	Party _party_{ None };
	Character* _character_{ nullptr };
};

