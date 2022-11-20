#include "Tile.hpp"
#include "Tilemap.hpp"

/*	Tile instantiates a new tile with a unique 'position' while adding its own reference to the tile map.
	All of the surrounding tiles are then initialized or retrieved if already existing.*/

Tile::Tile(const sf::Vector3i& coordinates) {
	_coordinates_ = coordinates;
	_position_ = Tilemap::CoordToPosition(coordinates);
}


void Tile::AddSurroundingTile(Tile* tile) {
	_surroundingTiles_.push_back(tile);
}

// Position returns the tile's position.
sf::Vector2f Tile::Position() const {
	return _position_;
}


// Position returns the tile's coordinates.
sf::Vector3i Tile::Coordinates() const {
	return _coordinates_;
}

// Obstacle returns whether or not the tile is an obstacle.
bool Tile::Obstacle() const {
	return _obstacle_;
}

/*	Party returns whether or not the tile is a SafeZone or neutral.
	In the case of a SafeZone, the party holding the SafeZone is returned.
	Otherwise, the 'none' value is returned.*/
Party Tile::GetParty() const {
	return _party_;
}

// Character returns the reference of the character currently on the tile or nullptr if the tile is free.
const Character* Tile::GetCharacter() const {
	return _character_;
}

/*	SurroundingTiles returns a vector containing the references of all surrounding tiles.
	Its count depends on the tile location : 6 by default, 4 on an edge, 3 in a corner.*/
const std::vector<Tile*>& Tile::SurroundingTiles() {
	return _surroundingTiles_;
}

// SetObstacle turns the tile into an obstacle depending on the input.
void Tile::SetObstacle(bool isObstacle) {
	_obstacle_ = isObstacle;
}

// SetParty turns the tile into a SafeZone tile of the corresponding 'party'.
void Tile::SetParty(Party party) {
	_party_ = party;
}

// SetCharacter makes the tile occupied by the corresponding 'character'.
void Tile::SetCharacter(Character* character) {
	_character_ = character;
}

// FreeTile resets the tile's character reference to nullptr.
void Tile::FreeTile() {
	_character_ = nullptr;
}