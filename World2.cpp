#include "World2.h"


Tile::Tile() : value(0) {}

Tile::Tile(int value)
{
	this->value = value;

	if (this->value == 1) color = glm::vec4(102, 51, 0, 255) / 255.0f;
	else if (this->value == 2) color = glm::vec4(192, 192, 192, 255) / 255.0f;
	else if (this->value == 3) color = glm::vec4(40, 40, 40, 255) / 255.0f;
}

void Tile::updateColor()
{
	if (this->value == 1) color = glm::vec4(102, 51, 0, 255) / 255.0f;
	else if (this->value == 2) color = glm::vec4(192, 192, 192, 255) / 255.0f;
	else if (this->value == 3) color = glm::vec4(40, 40, 40, 255) / 255.0f;
}


Cell::Cell() : objects(std::vector<GameObject*>()) {}


World::World(GLuint entitytexture, GLint entityNumElements)
{
	texture = entitytexture;
	numElements = entityNumElements;
	horizon = 10;
	rowSize = 20;
	colSize = 20;

	int terrain[20][20] = 
	{
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,1,2,2,2,1,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,1,2,2,2,1,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,1,3,3,3,1,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0 },
		{ 0,0,0,0,3,2,2,1,1,1,1,1,1,1,1,0,0,0,0,0 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,2,1,1,1,1,2,0,1,1,1,2,1,1,2,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
		{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
		{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
		{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
		{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
		{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },

	};



	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			//Create Cell object and initialize its attributes
			Cell* cell = new Cell();
			cell->tile = Tile(terrain[i][j]);
			cell->gridPos = glm::vec2(i, j);
			glm::vec3 worldPos;
			gridToWorldPos(i, j, &worldPos);
			cell->worldPos = worldPos;
			grid[i][j] = cell;
		}
	}

	
}

void World::clear()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			grid[i][j]->objects.clear();
		}
	}
}


bool World::outOfBounds(int i, int j)
{
	return i < 0 || i > rowSize-1 || j < 0 || j > colSize-1;
}

void World::updateObjects()
{
	for (int k = 0; k < gameObjects.size(); k++)
	{
		glm::vec3 worldPos = gameObjects[k]->getPosition();
		int i, j;

		
		worldToGridPos(worldPos, i, j);

		//Destroy object if it is out of bounds
		if (outOfBounds(i, j))
		{
			gameObjects.erase(gameObjects.begin() + k);
			--k;
			continue;
		}

		//add object to our grid
		grid[i][j]->objects.push_back(gameObjects[k]);
	}
}

void World::checkForCollision()
{
	for (int k = 0; k < gameObjects.size(); k++)
	{
		GameObject* currentGameObject = gameObjects[k];
		glm::vec3 worldPos = gameObjects[k]->getPosition();
		
		int i, j;
		worldToGridPos(worldPos, i, j);

		Cell* currentCell = grid[i][j];

		/*  The surrounding cells
			0 - left
			1 - right
			2 - up
			3 - down
			4 - top left 
			5 - top right
			6 - bottom left 
			7 - bottom right
		*/
		Cell* surroundingCells[8] =
		{
			!outOfBounds(i,j - 1) ? grid[i][j - 1] : NULL, // left
			!outOfBounds(i,j + 1) ? grid[i][j + 1] : NULL, //right
			!outOfBounds(i - 1,j) ? grid[i - 1][j] : NULL, //up
			!outOfBounds(i + 1,j) ? grid[i + 1][j] : NULL, //down
			!outOfBounds(i - 1,j - 1) ? grid[i - 1][j - 1] : NULL, // top left
			!outOfBounds(i - 1,j + 1) ? grid[i - 1][j + 1] : NULL, // top right
			!outOfBounds(i + 1,j - 1) ? grid[i + 1][j - 1] : NULL, // bottom left
			!outOfBounds(i + 1,j + 1) ? grid[i + 1][j + 1] : NULL, // bottom right
		};
		

		//check for collision with objects in same cell
		for (int m = 0; m < currentCell->objects.size(); m++)
		{
			GameObject* otherGameObject = currentCell->objects[m];

			//ignore player-bullet or collision with self collision
			if ((currentGameObject->type == "player" && otherGameObject->type == "bullet") ||
				(currentGameObject->type == "bullet" && otherGameObject->type == "player")||
				currentGameObject->type == otherGameObject->type)
			{
				continue;
			}

			if (glm::length(currentGameObject->getPosition() - otherGameObject->getPosition()) < 0.5f)
			{
				currentGameObject->collide(glm::vec3(), 0);
			}
		}

		
		//check for collision with objects and terrain in surroundoing cells
		for (int m = 0; m < 8; m++)
		{
			
			Cell* surCell = surroundingCells[m];
			if (surCell == NULL) {
				continue;
			}

			//printf(" bullet : %f || %f || %f\n", currentGameObject->getPosition().x, currentGameObject->getPosition().y, currentGameObject->getPosition().z);
			//printf(" surCell : %f || %f || %f\n", surCell->worldPos.x, surCell->worldPos.y, surCell->worldPos.z);

			//collision with tile in surrounding cell
			if (surCell->tile.value != 0 && glm::length(currentGameObject->getPosition() - surCell->worldPos) < 1)
			{
				glm::vec3 normal;

				glm::vec3 diff = currentGameObject->getPosition() - surCell->worldPos;
				diff = glm::normalize(diff);

				//determine collision normal based on what surface of terrain we're colliding with
				if (diff.y > sqrt(2.0f) / 2.0f)
				{
					normal = glm::vec3(0, 1, 0);
				}
				else if (diff.y < sqrt(2.0f) / 2.0f && diff.y > -(sqrt(2.0f) / 2.0f) && diff.x > 0)
				{
					normal = glm::vec3(1, 0, 0);
				}
				else if (diff.y < sqrt(2.0f) / 2.0f && diff.y > -(sqrt(2.0f) / 2.0f) && diff.x < 0)
				{
					normal = glm::vec3(-1, 0, 0);
				}
				else if (diff.y < -(sqrt(2.0f) / 2.0f))
				{
					normal = glm::vec3(0, -1, 0);
				}
				currentGameObject->collide(normal, surCell->tile.value);
			}

			//Collision with object in surrounding cells
			for (int n = 0; n < surCell->objects.size(); n++)
			{
				GameObject* otherGameObject = surCell->objects[n];

				//ignore player-bullet collision
				if ((currentGameObject->type == "player" && otherGameObject->type == "bullet") ||
					(currentGameObject->type == "bullet" && otherGameObject->type == "player"))
				{
					continue;
				}

				if (glm::length(currentGameObject->getPosition() - otherGameObject->getPosition()) < 0.5)
				{
					//colliding with other objects
					currentGameObject->collide(glm::vec3(), 0);
				}

			}
		}
	}
}

void World::explodeBullet(glm::vec3 pos, float radius)
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			float distance = glm::distance(pos, grid[i][j]->worldPos);
			if (distance < radius && grid[i][j]->tile.value > 0 && grid[i][j]->tile.value < 3)
			{
				grid[i][j]->tile.value--;
				grid[i][j]->tile.updateColor();
			}
		}
	}
}


void World::destroy()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->shouldDie)
		{
			if (gameObjects[i]->type == "bullet")
			{
				explodeBullet(gameObjects[i]->getPosition(), 3);
			}
			gameObjects.erase(gameObjects.begin() + i);
			--i;
		}
	}
}



bool World::worldToGridPos(glm::vec3 worldPos, int& i, int&j)
{
	j = worldPos.x + horizon;
	i = -(worldPos.y - horizon);

	if (outOfBounds(i, j)) return false;
	return true;
}

void World::gridToWorldPos(int i, int j, glm::vec3* worldPos)
{
	float x = j - horizon;
	float y = -(i - horizon);
	worldPos->x = x;
	worldPos->y = y;
	worldPos->z = 0;
}


void World::render(Shader& shader)
{
	shader.setUniform1f("isTile", 1.0f);

	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < colSize; j++)
		{
			Cell* cell = grid[i][j];

			//Set color based on tile's value
			if (cell->tile.value == 0) continue;
			shader.setUniform4f("tileColor", cell->tile.color );

			//position of tile
			glm::vec3 position = glm::vec3();
			gridToWorldPos(i, j, &position);

			//printf("%f || %f || %f \n", position.x, position.y, position.z);

			// Bind the entities texture
			glBindTexture(GL_TEXTURE_2D, texture);
			


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

	shader.setUniform1f("isTile", -1.0f);

}
