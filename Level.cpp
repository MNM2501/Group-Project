#include "Level.h"
#include <fstream>
#include <sstream>

Level::Level(string fileName, std::vector<GLuint> entityTextures, glm::vec3 playerStart, UIElement* background)
{
	textures = entityTextures;
	this->playerStart = playerStart;
	this->background = background;

	//read cv data;
	ifstream myFile;
	myFile.open(fileName);

	//read in terrain
	int i = 0;
	string line;
	while (getline(myFile, line))
	{
		stringstream stream(line);
		this->terrain.push_back(std::vector<int>());
		while (getline(stream, line, ','))
		{
			this->terrain[i].push_back(stoi(line));
		}
		++i;
	}

	myFile.close();

	rowSize = terrain.size();
	colSize = terrain[0].size();
	xHorizon = 0;
	yHorizon = floor(rowSize / 2);
}



