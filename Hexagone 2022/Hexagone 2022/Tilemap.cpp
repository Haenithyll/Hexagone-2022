#include "Tilemap.hpp"
#include "Log.hpp"


Tilemap* Tilemap::_instance_ = nullptr;

/*	Tilemap generates a new tile map according to 'radius' whose default value is 5 (ignoring the center tile).
	The center tile is instantiated, which causes the others to generate. */
void Tilemap::Init(int radius) {
	if (_instance_ == nullptr)
		_instance_ = new Tilemap();

	_instance_->_radius_ = radius;
	GenerateTiles();
	InitSurroundingTiles();
}


void Tilemap::GenerateTiles() {
	int radius{ Tilemap::Radius() };
	int y, startingY, count, index;
	for (int x{ -radius }; x <= radius; ++x) {
		startingY = x > 0 ? radius - x : radius;
		count = 2 * radius - abs(x) + 1;
		index = 0;
		y = startingY;
		while (index < count) {
			AddTile(new Tile(sf::Vector3i{ x, y, -(x + y) }));
			--y;
			++index;
		}
	}
}

// InitSurroundingTiles sets the surrounding tiles of a specific 'tile' by retrieving all existing tiles with respect to the tilemap's radius.
void Tilemap::InitSurroundingTiles() {

	for (const auto& [coord, tile] : Tilemap::Tiles())
		/*
		Only 3 unit vectors are necessary to define the position of the 6 surrounding tiles.
		Therefore, a forloop goes through both the unit vectors and their opposite.
		*/
		for (int i{ -1 }; i <= 1; i += 2)
			for (sf::Vector3i unitVector : Tilemap::UnitVectors()) {
				sf::Vector3i potentialCoords{ tile->Coordinates() + i * unitVector };
				if (abs(potentialCoords.x) <= Tilemap::Radius() &&
					abs(potentialCoords.y) <= Tilemap::Radius() &&
					abs(potentialCoords.z) <= Tilemap::Radius())
					tile->AddSurroundingTile(Tilemap::GetTile(potentialCoords));
			}
}


// AddTile adds the 'tile' reference to the tile map according to the tile's coordinates.
void Tilemap::AddTile(Tile* tile) {
	sf::Vector3i tileCoordinates{ tile->Coordinates() };
	_instance_->_tiles_.insert(std::pair<std::array<int, 3>, Tile*>(std::array<int, 3>{
		tileCoordinates.x,
			tileCoordinates.y,
			tileCoordinates.z
	}, tile));
}

// GetTile returns the tile whose position matches 'position'.
Tile* Tilemap::GetTile(sf::Vector3i position) {
	Tile*& returnedTile{ _instance_->_tiles_[std::array{position.x, position.y, position.z}] };
	return returnedTile;
}

// Radius returns the Hexmap radius (ignoring the center tile).
int Tilemap::Radius() {
	int& returnedRadius{ _instance_->_radius_ };
	return returnedRadius;
}

// Tiles returns the tile map.
std::map<std::array<int, 3>, Tile*> Tilemap::Tiles() {
	std::map<std::array<int, 3>, Tile*>& returnedTiles{ _instance_->_tiles_ };
	return returnedTiles;
}

// UnitVectors returns the unit vectors.
std::vector<sf::Vector3i> Tilemap::UnitVectors() {
	std::vector<sf::Vector3i>& returnedUnitVectors{ _instance_->_unitVectors_ };
	return returnedUnitVectors;
}

void Tilemap::GenerateSafeZones() {
	// TODO
}

void Tilemap::GenerateObstacles() {
	// TODO
}