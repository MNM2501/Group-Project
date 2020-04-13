#pragma once
#include <iostream>
#include <vector>

class Level
{
	friend class World;

public:
	Level(int id, std::vector<std::vector<int>> terrain);

private:
	int xHorizon;
	int yHorizon;
	int id;
	int rowSize;
	int colSize;
	std::vector<std::vector<int>> terrain;
};

