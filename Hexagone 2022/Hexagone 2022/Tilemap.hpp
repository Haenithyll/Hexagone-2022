#pragma once

#include <map>
#include "Tile.hpp"

class Tilemap {

public:
	static Tilemap* getInstance();

	static void InitTilemap(int radius = 2);

	int Radius();
	void AddTile(Tile*);
	Tile* GetTile(std::array<int, 3>);
	std::map<std::array<int, 3>, Tile*> Tiles();
	std::vector<std::array<int, 3>> UnitVectors();

private:
	static Tilemap* _instance_;

	int _radius_;
	std::vector<std::array<int, 3>> _unitVectors_{
		std::array<int, 3>{ 0,1,-1 },
		std::array<int, 3>{ 1,0,-1 },
		std::array<int, 3>{ 1,-1,0 }
	};
	std::map<std::array<int, 3>, Tile*> _tiles_;
	std::map<tmpParty, std::vector<Tile*>> _safeZoneTiles_;


	void GenerateSafeZones();
	void GenerateObstacles();
};