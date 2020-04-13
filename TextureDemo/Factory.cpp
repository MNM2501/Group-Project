#include "Factory.h"

#include "PlayerGameObject.h"
#include "GameObject.h"
#include "Tank.h"
#include "BulletGameObject.h"
#include "EnemyGameObject.h"
#include "World.h"

PlayerGameObject* Factory::player = NULL;

Factory::Factory()
{
}


void Factory::spawnGameObject(glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements)
{
	World::gameObjects.push_back(new GameObject(entityPosition, entityTexture, entityNumElements));
}

void Factory::spawnBulletGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, glm::vec3 direction, string team)
{
	BulletGameObject* b = new BulletGameObject(entityPos, entityTexture, entityNumElements, direction);
	b->team = team;
	World::gameObjects.push_back(b);
}

void Factory::spawnPlayerGameObject(glm::vec3 &entityPos, GLuint entityTexture, GLint entityNumElements)
{
	PlayerGameObject* player = new PlayerGameObject(entityPos, entityTexture, entityNumElements);
	Factory::player = player;
	World::gameObjects.push_back(player);
}

void Factory::spawnEnemyGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, float theSpeed, int theHealth, int ap,
	PlayerGameObject* player)
{
	World::gameObjects.push_back(new EnemyGameObject(entityPos, entityTexture, entityNumElements, theSpeed, theHealth, ap, player));
}

void Factory::spawnTank(glm::vec3& entityPos, GLuint entityTextures[3], GLint entityNumElements, int ap, PlayerGameObject* player)
{
	World::gameObjects.push_back(new Tank(entityPos, entityTextures, entityNumElements, ap, player));
}
