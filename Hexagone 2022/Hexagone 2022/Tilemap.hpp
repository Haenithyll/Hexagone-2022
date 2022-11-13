#pragma once

#include <map>
#include "Tile.hpp"

typedef std::vector<sf::Vector3i> patternCenters;

class Tilemap {

public:
	static void Init(int, patternCenters(Tilemap::* )());
	

	static int Radius();
	static void AddTile(Tile*);
	static Tile* GetTile(sf::Vector3i);
	static std::map<std::array<int, 3>, Tile*>& Tiles();
	static std::vector<sf::Vector3i> UnitVectors();
	static sf::Vector2f CoordToPosition(sf::Vector3i);
	static sf::Vector2f CoordToPosition(std::array<int, 3>);
	static sf::Vector3i GetSafeZoneCenter(Party);

	static std::array<int, 3> Vector3ToArray(const sf::Vector3i& position);

	static bool OutofMap(sf::Vector3i);

	patternCenters FlowerPattern();

private:
	Tilemap() {};

	static Tilemap* _instance_;

	int _radius_{0};
	std::vector<sf::Vector3i> _unitVectors_{
		sf::Vector3i{ 0,1,-1 },
		sf::Vector3i{ 1,0,-1 },
		sf::Vector3i{ 1,-1,0 }
	};
	std::map<std::array<int, 3>, Tile*> _tiles_;
	std::map<Party, Tile*> _safeZoneTiles_;

	static void GenerateTiles();
	static void InitSurroundingTiles();

	static void GenerateSafeZones(patternCenters(Tilemap::*)());
	static void GenerateObstacles(int nbObst);
};