#include "Tilemap.hpp"
#include "Log.hpp"

#define PI 3.14159265359f

Tilemap* Tilemap::_instance_ = nullptr;

/*	Tilemap generates a new tile map according to 'radius' whose default value is 5 (ignoring the center tile).
	The center tile is instantiated, which causes the others to generate. */
void Tilemap::Init(int radius, patternCenters(Tilemap::* pattern)()) {
	if (_instance_ == nullptr) {
		_instance_ = new Tilemap();

		_instance_->_radius_ = radius;
		GenerateTiles();
		InitSurroundingTiles();
		GenerateSafeZones(pattern);
	}
}


void Tilemap::GenerateTiles() {
	int radius{ _instance_->_radius_ };
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

	for (const auto& [_, tile] : _instance_->_tiles_)
		/*
		Only 3 unit vectors are necessary to define the position of the 6 surrounding tiles.
		Therefore, a forloop goes through both the unit vectors and their opposite.
		*/
		for (int i{ -1 }; i <= 1; i += 2)
			for (const sf::Vector3i& unitVector : _instance_->_unitVectors_) {
				sf::Vector3i potentialCoords{ tile->Coordinates() + i * unitVector };
				if (abs(potentialCoords.x) <= _instance_->_radius_ &&
					abs(potentialCoords.y) <= _instance_->_radius_ &&
					abs(potentialCoords.z) <= _instance_->_radius_)
					tile->AddSurroundingTile(GetTile(potentialCoords));
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
	return _instance_->_radius_;
}

// Tiles returns the tile map.
std::map<std::array<int, 3>, Tile*>& Tilemap::Tiles() {
	return _instance_->_tiles_;
}

// UnitVectors returns the unit vectors.
std::vector<sf::Vector3i> Tilemap::UnitVectors() {
	return _instance_->_unitVectors_;
}

sf::Vector2f Tilemap::CoordToPosition(sf::Vector3i coordinates) {
	return sf::Vector2f{
		coordinates.x + coordinates.y * cosf(2.f * PI / 3.f) + coordinates.z * cosf(-2.f * PI / 3.f),
		coordinates.y * sinf(2.f * PI / 3.f) + coordinates.z * sinf(-2.f * PI / 3.f)
	};
}

void Tilemap::GenerateSafeZones(patternCenters(Tilemap::* pattern)()) {
	for (int i{ -1 }; i <= 1; i += 2)
		for (sf::Vector3i center : (_instance_->*pattern)()) {
			Tile* SZTile = _instance_->_tiles_[std::array<int, 3>{i* center.x, i* center.y, i* center.z}];
			if (SZTile == nullptr)
				throw std::invalid_argument("Failed attempt to setup safezone tiles : out of map");
			SZTile->SetParty(Reprise);
			for (Tile* tile : SZTile->SurroundingTiles())
				tile->SetParty(Reprise);
		}
}

void Tilemap::GenerateObstacles() {
	// TODO
}

patternCenters Tilemap::FlowerPattern() {
	int radius{ _instance_->_radius_ };
	return patternCenters {
		sf::Vector3i{ radius - 2, 3 - radius, -1 },
			sf::Vector3i{ radius / 2 - 1, radius - 1 + -radius / 2, -radius + 2 }
	};
}

