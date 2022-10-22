#pragma once

#include <vector>
#include <array>

#include "Drawable.hpp"
#include "BGCharacter.hpp"
#include "SFML/System/Vector3.hpp"

enum tmpParty {
	none,
	parti1,
	parti2,
	parti3,
	parti4
};

class Tile {
public:

	Tile(sf::Vector3i coordinates);

	sf::Vector2f Position();
	sf::Vector3i Coordinates();
	bool Obstacle();
	tmpParty Party();
	BGCharacter* Character();
	std::vector<Tile*> SurroundingTiles();

	void AddSurroundingTile(Tile*);
	void SetObstacle();
	void SetParty(tmpParty);
	void SetCharacter(BGCharacter*);
	void FreeTile();

private:
	sf::Vector2f _position_;
	sf::Vector3i _coordinates_;
	std::vector<Tile*> _surroundingTiles_;

	bool _obstacle_{ false };
	tmpParty _party_{ none };
	BGCharacter* _character_{ nullptr };

};

