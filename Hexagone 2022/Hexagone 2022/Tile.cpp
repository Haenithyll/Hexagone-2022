#include "Tile.hpp"
#include "Tilemap.hpp"

/*	Tile instantiates a new tile with a unique 'position' while adding its own reference to the tile map.
	All of the surrounding tiles are then initialized or retrieved if already existing.*/

Tile::Tile(std::array<int, 3> position) {
	_position_ = position;
	Tilemap::getInstance()->AddTile(this);
	InitSurroundingTiles();
}


#pragma region custom_operations

std::array<int, 3> AddArrays(std::array<int, 3> array1, std::array<int, 3> array2) {
	return std::array<int, 3> {
		array1[0] + array2[0],
			array1[1] + array2[1],
			array1[2] + array2[2],
	};
}

std::array<int, 3> MultiplyArray(std::array<int, 3> array, int coefficient) {
	return std::array<int, 3> {
		coefficient* array[0],
			coefficient* array[1],
			coefficient* array[2],
	};
}

bool InRadius(std::array<int, 3> array) {
	int radius{ Tilemap::getInstance()->Radius() };
	return abs(array[0]) <= radius && abs(array[1]) <= radius && abs(array[2]) <= radius;
}

#pragma endregion


// InitSurroundingTiles sets the surrounding tiles by retrieving existing tiles or creating new ones with respect to the tilemap's radius.
void Tile::InitSurroundingTiles() {
	std::vector<std::array<int, 3>> surroundingPositions;
	Tilemap* instance{ Tilemap::getInstance() };	// retrieval of the tilemap's instance to avoid further unnecessary calls.

	/*
	Only 3 unit vectors are necessary to define the position of the 6 surrounding tiles.
	Therefore, a forloop goes through both the unit vectors and their opposite.
	*/

	for (int i{ -1 }; i <= 1; i += 2)
		for (std::array<int, 3> unitVector : instance->UnitVectors()) {
			std::array<int, 3> potentialPosition{ AddArrays(_position_, MultiplyArray(unitVector, i)) };
			if (InRadius(potentialPosition))
				surroundingPositions.push_back(potentialPosition);
		}

	for (std::array<int, 3> coord : surroundingPositions) {
		if (instance->Tiles().contains(coord)) // Tests whether or not the coord corresponds to an existing tile. True if not found.
			_surroundingTiles_.push_back(instance->GetTile(coord));
		else
			_surroundingTiles_.push_back(new Tile(coord));
	}
}

// Position returns the tile's position.
std::array<int, 3> Tile::Position() {
	std::array<int, 3>& returnedPosition{ _position_ };
	return returnedPosition;
}

// Obstacle returns whether or not the tile is an obstacle.
bool Tile::Obstacle() {
	bool& returnedObstacle{ _obstacle_ };
	return returnedObstacle;
}

/*	Party returns whether or not the tile is a SafeZone or neutral.
	In the case of a SafeZone, the party holding the SafeZone is returned.
	Otherwise, the 'none' value is returned.*/
tmpParty Tile::Party() {
	tmpParty& returnedParty{ _party_ };
	return returnedParty;
}

// Character returns the reference of the character currently on the tile or nullptr if the tile is free.
BGCharacter* Tile::Character() {
	BGCharacter*& returnedCharacter{ _character_ };
	return returnedCharacter;
}

/*	SurroundingTiles returns a vector containing the references of all surrounding tiles.
	Its count depends on the tile location : 6 by default, 4 on an edge, 3 in a corner.*/
std::vector<Tile*> Tile::SurroundingTiles() {
	std::vector<Tile*>& returnedSurroundingTiles{ _surroundingTiles_ };
	return returnedSurroundingTiles;
}

// SetObstacle turns the tile into an obstacle.
void Tile::SetObstacle() {
	_obstacle_ = true;
}

// SetParty turns the tile into a SafeZone tile of the corresponding 'party'.
void Tile::SetParty(tmpParty party) {
	_party_ = party;
}

// SetCharacter makes the tile occupied by the corresponding 'character'.
void Tile::SetCharacter(BGCharacter* character) {
	_character_ = character;
}

// FreeTile resets the tile's character reference to nullptr.
void Tile::FreeTile() {
	_character_ = nullptr;
}