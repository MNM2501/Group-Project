#include "World.h"




/*	WorldGrid value information

	Tiles		
	0 - Nothing
	1 - grass tile
	2 - dirt tile
	
	--------------------------------------

	Entities
	100 - Player
*/

//Initialize static members
int** World::worldGrid = NULL;
int World::rowSize = 0;
int World::colSize = 0;
std::vector<GLuint> World::textures = std::vector<GLuint>();
int World::numElements = 0;

	//boundaries
int World::leftBoundary = 0;
int World::rightBOundary = 0;
int World:: upperBoundary = 0;
int World::lowerBoundary = 0;



World::World(int _rowSize, int _colSize, int** entityGrid, std::vector<GLuint> entityTextures, GLint entityNumElements)
{
	worldGrid = entityGrid;
	textures = entityTextures;
	numElements = entityNumElements;

	//dimensions
	rowSize = _rowSize;
	colSize = _colSize;
}


//check for collision
/*
	0 - x axis
	1 - y axis
*/
bool World::checkForCollision(glm::vec3 futurePos, glm::vec3 offset, int axis)
{
	//determine future pos
	//This is a hotfix for a bug, should update later.
	//printf("axis : %d\n", axis);
	if (axis == 0)
	{
		futurePos = glm::vec3(futurePos.x, futurePos.y - offset.y, futurePos.z);
	}
	else if (axis == 1)
	{
		futurePos = glm::vec3(futurePos.x - offset.x, futurePos.y, futurePos.z);
	}
	else
	{
		//printf("axis passed in isn't valid in World.cpp -> checkForCollision()... check comments");
		return true;
	}


	//Potential grid positions of location we want to go to
	int i;
	int j;

	//If we're not in the grid, treat it as collision
	if (worldToGridPos(futurePos, i, j))
	{
		//printf("What is at future grid ? %d\n", worldGrid[i][j]);
		if (worldGrid[i][j] != 0)
		{
			//printf("returning true...\n");
			return true;
		}
		else
		{
			return false;
		}
	}

	//printf("returning false...\n");
	if (worldToGridPos(futurePos - offset, i, j))
	{
		return false;
	}
	else
		return true;

	

	
}


//convert grid position to world position
glm::vec3 World::gridToWorldPos(int i, int j)
{
	glm::vec3 position;

	int horizon = (int)(glm::floor((float)(rowSize / 2)));

	position = glm::vec3(j, -(i - horizon), 1);
	return position;
}


//convert world position to grid position
//returns true if found grid position, false otherwise
bool World::worldToGridPos(glm::vec3 worldPos, int& i, int& j)
{
	worldPos *= 1.01f;
	//If we're not in the grid, return false
	//printf("future pos : %f || %f\n", worldPos.x, worldPos.y);
	//printf("%f || %f\n", gridToWorldPos(0, 0).x, gridToWorldPos(0, colSize -1).x);
	bool inGrid = worldPos.x > gridToWorldPos(0, 0).x && worldPos.x < gridToWorldPos(0, colSize -1).x &&
		worldPos.y < gridToWorldPos(0, 0).y && worldPos.y > gridToWorldPos(rowSize -1 , 0).y;
	
	if (!inGrid) return false;

	//printf("IN GRID!!\n");


	//Compute grid positions
	int horizon = gridToWorldPos(0, 0).y;
	i = -((int)(glm::floor(worldPos.y + 0.5)) - horizon);
	j = (int)(glm::floor(worldPos.x + 0.5));

	//printf("world position %f || % f\n", worldPos.x, worldPos.y);
	//printf("grid coordinates : %d || %d\n\n\n", i, j);

	return true;
}

//checks for boundary detection
bool World::boundaryDetection(glm::vec3 pos)
{
	if (pos.x < leftBoundary || pos.x > rightBOundary || pos.y < lowerBoundary || pos.y > upperBoundary)
	{
		return true;
	}

	return false;
}

//renders terrain
void World::render(Shader& shader)
{
	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < colSize; j++)
		{
			//If there is supposed to be nothing, continue
			if (worldGrid[i][j] == 0) continue;


			//position of tile
			glm::vec3 position = gridToWorldPos(i, j);



			// Bind the entities texture
			glBindTexture(GL_TEXTURE_2D, textures[worldGrid[i][j]]);


			// Setup the transformation matrix for the shader
			// TODO: Add different types of transformations
			glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);


			// Set the transformation matrix in the shader
			// TODO: Multiply your new transformations to make the transformationMatrix
			glm::mat4 transformationMatrix = translationMatrix;
			shader.setUniformMat4("transformationMatrix", transformationMatrix);

			// Draw the entity
			glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
		}
	}
}



