#include "Tilemap.hpp"

Tilemap* Tilemap::_instance_ = nullptr;

// Retrieves the tilemap's instance.
Tilemap* Tilemap::getInstance() {
	if (_instance_ == nullptr)
		_instance_ = new Tilemap();

	return _instance_;
}

/*	Tilemap generates a new tile map according to 'radius' whose default value is 5 (ignoring the center tile).
	The center tile is instantiated, which causes the others to generate. */
void Tilemap::InitTilemap(int radius) {
	_radius_ = radius;
	new Tile(std::array<int, 3>{ 0, 0, 0 });
}

// AddTile adds the 'tile' reference to the tile map according to the tile's coordinates.
void Tilemap::AddTile(Tile* tile) {
	_tiles_.insert(std::pair<std::array<int, 3>, Tile*>(tile->Position(), tile));
}

// GetTile returns the tile whose position matches 'position'.
Tile* Tilemap::GetTile(std::array<int, 3> position) {
	Tile*& returnedTile{ _tiles_[position] };
	return returnedTile;
}

// Radius returns the Hexmap radius (ignoring the center tile).
int Tilemap::Radius() {
	int& returnedRadius{ _radius_ };
	return returnedRadius;
}

// Tiles returns the tile map.
std::map<std::array<int, 3>, Tile*> Tilemap::Tiles() {
	std::map<std::array<int, 3>, Tile*>& returnedTiles{ _tiles_ };
	return returnedTiles;
}

// UnitVectors returns the unit vectors.
std::vector<std::array<int, 3>> Tilemap::UnitVectors() {
	std::vector<std::array<int, 3>>& returnedUnitVectors{ _unitVectors_ };
	return returnedUnitVectors;
}

void Tilemap::GenerateSafeZones() {
	// TODO
}

void Tilemap::GenerateObstacles() {
	// TODO
}