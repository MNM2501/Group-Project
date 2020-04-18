#include "World.h"
#include "Factory.h"
#include "GameController.h"

//Initialize static members
std::vector<GameObject*> World::gameObjects = std::vector<GameObject*>();
std::vector<std::vector<Cell*>> World::grid = std::vector<std::vector<Cell*>>();

int World::numElements = 0;
Level* World::currentLevel = NULL;


Cell::Cell() {}

World::World(GLint entityNumElements)
{
	numElements = entityNumElements;
}

void World::loadLevel(Level* level)
{
	currentLevel = level;

	Factory::spawnPlayerGameObject(level->playerStart);
	std::vector<std::vector<int>> terrain = currentLevel->terrain;

	for (int i = 0; i < currentLevel->rowSize; i++)
	{
		grid.push_back(std::vector<Cell*>());
		for (int j = 0; j < currentLevel->colSize; j++)
		{
			//Create Cell object and initialize its attributes
			Cell* cell = new Cell();
			if(terrain[i][j] < 100)
				cell->texture = currentLevel->textures[terrain[i][j]];
			cell->isTerrain = terrain[i][j] > 0 && terrain[i][j] < 100 ? true : false;

			cell->gridPos = glm::vec2(i, j);

			glm::vec3 worldPos;
			gridToWorldPos(i, j, &worldPos);
			cell->worldPos = worldPos;

			grid[i].push_back(cell);
		}
	}

	spawnInitialObjects();
}


void World::run()
{
	clear();
	updateObjects();
	checkForCollision();
	destroy();
}

void World::destroy()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->shouldDie)
		{
			GameController::souls += gameObjects[i]->soulDrop;
			if (gameObjects[i]->type == ALIEN_BOMB)
			{
				GameController::won = true;
				GameController::running = false;
				closeLevel();
				return;
			}
				
			else if (gameObjects[i]->type == PLAYER || gameObjects[i]->type == CHASER)
			{
				GameController::won = false;
				GameController::running = false;
				closeLevel();
				return;
			}
			delete gameObjects[i];
			gameObjects.erase(gameObjects.begin() + i);
			--i;
		}
	}
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

void World::clear()
{
	for (int i = 0; i < currentLevel->rowSize; i++)
	{
		for (int j = 0; j < currentLevel->colSize; j++)
		{
			grid[i][j]->objects.clear();
		}
	}
}

void World::spawnInitialObjects()
{
	std::vector<std::vector<int>> terrain = currentLevel->terrain;

	for (int i = 0; i < currentLevel->rowSize; i++)
	{
		for (int j = 0; j < currentLevel->colSize; j++)
		{
			glm::vec3 worldPos;
			gridToWorldPos(i, j, &worldPos);

			int val = terrain[i][j];

			if (val == ENEMY)
				Factory::spawnEnemyGameObject(worldPos, 1, 20, 5);
			else if (val == GRAVITY_TANK)
				Factory::spawnGravityTank(worldPos, 7);
			else if (val == ALIEN_BOMB)
				Factory::spawnAlienBomb(worldPos);
			else if (val == TANK)
				Factory::spawnTank(worldPos, 7);
			else if (val == POWERUP)
				Factory::spwnPowerup(worldPos);
			else if (val == CHASER)
				Factory::spawnChaser(worldPos, currentLevel->terrain);
			else if (val == KAMIKAZE)
				Factory::spawnKamikaze(worldPos);
			else if (val == LAVA)
				Factory::spawnLavaTile(worldPos);

		}
	}
}

void World::closeLevel()
{
	gameObjects.clear();
	grid = std::vector<std::vector<Cell*>>();
	currentLevel = NULL;
}


void  World::checkForCollision()
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

			//ignore same team collision
			if (currentGameObject->team == otherGameObject->team)
			{
				continue;
			}

			if (glm::length(currentGameObject->getPosition() - otherGameObject->getPosition()) < currentGameObject->getHitBox() || 
				glm::length(currentGameObject->getPosition() - otherGameObject->getPosition()) < otherGameObject->getHitBox())
			{
				currentGameObject->collide(otherGameObject->type, glm::vec3(), otherGameObject);
			}
		}


		//check for collision with objects and terrain in surroundoing cells
		for (int m = 0; m < 8; m++)
		{

			Cell* surCell = surroundingCells[m];
			if (surCell == NULL) {
				continue;
			}

			//collision with tile in surrounding cell
			if (surCell->isTerrain && glm::length(currentGameObject->getPosition() - surCell->worldPos) < currentGameObject->getHitBox() + 0.5f)
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
				currentGameObject->collide(TERRAIN, normal, NULL);
			}

			//Collision with object in surrounding cells
			for (int n = 0; n < surCell->objects.size(); n++)
			{
				GameObject* otherGameObject = surCell->objects[n];

				//ignore same team collision
				if (currentGameObject->team == otherGameObject->team)
				{
					continue;
				}

				if (glm::length(currentGameObject->getPosition() - otherGameObject->getPosition()) < currentGameObject->getHitBox() ||
					glm::length(currentGameObject->getPosition() - otherGameObject->getPosition()) < otherGameObject->getHitBox())
				{
					//colliding with other objects
					currentGameObject->collide(otherGameObject->type, glm::vec3(), otherGameObject);
				}

			}
		}
	}
}

bool World::worldToGridPos(glm::vec3 worldPos, int& i, int&j)
{
	int xHorizon = currentLevel->xHorizon;
	int yHorizon = currentLevel->yHorizon;

	j = worldPos.x + xHorizon;
	i = -(worldPos.y - yHorizon);

	if (outOfBounds(i, j)) return false;
	return true;
}

void World::gridToWorldPos(int i, int j, glm::vec3* worldPos)
{
	int xHorizon = currentLevel->xHorizon;
	int yHorizon = currentLevel->yHorizon;

	float x = j - xHorizon;
	float y = -(i - yHorizon);
	worldPos->x = x;
	worldPos->y = y;
	worldPos->z = 0;
}

bool World::outOfBounds(int i, int j)
{
	return i < 0 || i > currentLevel->rowSize - 1 || j < 0 || j > currentLevel->colSize - 1;
}

void World::render(Shader& shader)
{
	if (currentLevel == NULL) return;
	shader.setUniform1f("isTile", 1.0f);

	for (int i = 0; i < currentLevel->rowSize; i++)
	{
		for (int j = 0; j < currentLevel->colSize; j++)
		{
			Cell* cell = grid[i][j];

			//Set texture based on tile value
			if (!cell->isTerrain) continue;

			//position of tile
			glm::vec3 position = glm::vec3();
			gridToWorldPos(i, j, &position);

			// Bind the entities texture
			glBindTexture(GL_TEXTURE_2D, cell->texture);

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
	Level*l = currentLevel;
	currentLevel->background->render(shader);
}
