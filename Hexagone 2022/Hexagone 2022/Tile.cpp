#include "Tile.hpp"
#include "Tilemap.hpp"

#define PI 3.14159265359

/*	Tile instantiates a new tile with a unique 'position' while adding its own reference to the tile map.
	All of the surrounding tiles are then initialized or retrieved if already existing.*/

Tile::Tile(sf::Vector3i coordinates) {
	_coordinates_ = coordinates;
	_position_ = sf::Vector2f{
		coordinates.x + coordinates.y * (float)cos(2 * PI / 3) + coordinates.z * (float)cos(-2 * PI / 3),
		coordinates.y * (float)sin(2 * PI / 3) + coordinates.z * (float)sin(-2 * PI / 3)
	};
}



void Tile::AddSurroundingTile(Tile* tile) {
	_surroundingTiles_.push_back(tile);
}

// Position returns the tile's position.
sf::Vector2f Tile::Position() {
	sf::Vector2f& returnedPosition{ _position_ };
	return returnedPosition;
}


// Position returns the tile's coordinates.
sf::Vector3i Tile::Coordinates() {
	sf::Vector3i& returnedCoordinates{ _coordinates_ };
	return returnedCoordinates;
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