#pragma once

#include <vector>
#include <array>

#include "Drawable.hpp"
#include "BGCharacter.hpp"

enum tmpParty {
	none,
	parti1,
	parti2,
	parti3,
	parti4
};

class Tile {
public:

	Tile(std::array<int, 3> coordinates);
	void InitSurroundingTiles();

	sf::Vector2f Position();
	std::array<int, 3> Coordinates();
	bool Obstacle();
	tmpParty Party();
	BGCharacter* Character();
	std::vector<Tile*> SurroundingTiles();

	void SetObstacle();
	void SetParty(tmpParty);
	void SetCharacter(BGCharacter*);
	void FreeTile();

private:
	sf::Vector2f _position_;
	std::array<int, 3> _coordinates_;
	std::vector<Tile*> _surroundingTiles_;

	bool _obstacle_{ false };
	tmpParty _party_{ none };
	BGCharacter* _character_{ nullptr };

};

