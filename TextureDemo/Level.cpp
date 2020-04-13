#include "Level.h"



Level::Level(int id, std::vector<std::vector<int>> terrain)
{
	this->terrain = terrain;

	rowSize = terrain.size();
	colSize = terrain[0].size();

	xHorizon = 0;
	yHorizon = floor(rowSize / 2);
}



