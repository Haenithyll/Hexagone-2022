#pragma once

#include <vector>
#include <array>
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

	Tile(std::array<int, 3> position);
	void InitSurroundingTiles();

	std::array<int, 3> Position();
	bool Obstacle();
	tmpParty Party();
	BGCharacter* Character();
	std::vector<Tile*> SurroundingTiles();

	void SetObstacle();
	void SetParty(tmpParty);
	void SetCharacter(BGCharacter*);
	void FreeTile();

private:
	std::array<int, 3> _position_;
	std::vector<Tile*> _surroundingTiles_;

	bool _obstacle_{ false };
	tmpParty _party_{ none };
	BGCharacter* _character_{ nullptr };

};

