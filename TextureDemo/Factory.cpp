#include "Factory.h"

#include "PlayerGameObject.h"
#include "GameObject.h"
#include "Tank.h"
#include "BulletGameObject.h"
#include "EnemyGameObject.h"
#include "World.h"
#include "Bomb.h"
#include "Powerup.h"
#include "GravityTank.h"
#include"GravityBullet.h"

PlayerGameObject* Factory::player = NULL;

Factory::Factory()
{
}


void Factory::spawnGameObject(glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements)
{
	World::gameObjects.push_back(new GameObject(entityPosition, entityTexture, entityNumElements));
}

void Factory::spawnBulletGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, glm::vec3 direction, string team, int damage)
{
	BulletGameObject* b = new BulletGameObject(entityPos, entityTexture, entityNumElements, direction, damage);
	b->team = team;
	World::gameObjects.push_back(b);
}

void Factory::spawnPlayerGameObject(glm::vec3 &entityPos, GLuint entityTexture, GLint entityNumElements)
{
	PlayerGameObject* player = new PlayerGameObject(entityPos, entityTexture, entityNumElements);
	Factory::player = player;
	World::gameObjects.push_back(player);
}

void Factory::spawnEnemyGameObject(glm::vec3& entityPos, std::vector<GLuint> entityTextures, GLint entityNumElements, float theSpeed, int theHealth, int ap,
	PlayerGameObject* player)
{
	World::gameObjects.push_back(new EnemyGameObject(entityPos, entityTextures, entityNumElements, theSpeed, theHealth, ap, player));
}

void Factory::spawnTank(glm::vec3& entityPos, std::vector<GLuint> entityTextures, GLint entityNumElements, int ap, PlayerGameObject* player)
{
	World::gameObjects.push_back(new Tank(entityPos, entityTextures, entityNumElements, ap, player));
}

void Factory::spawnBomb(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, int damage, string team)
{
	Bomb* b = new Bomb(entityPos, entityTexture, entityNumElements, damage);
	b->team = team;
	World::gameObjects.push_back(b);
}

void Factory::spwnPowerup(glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements)
{
	World::gameObjects.push_back(new Powerup(entityPosition, entityTexture, entityNumElements));
}

void Factory::spawnGravityTank(glm::vec3& entityPos, std::vector<GLuint> entityTextures, GLint entityNumElements, int ap, PlayerGameObject* player)
{
	World::gameObjects.push_back(new GravityTank(entityPos, entityTextures, entityNumElements, ap, player));
}

void Factory::spawnGravityBullet(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, glm::vec3 direction, int damage, string team)
{
	GravityBullet* g = new GravityBullet(entityPos, entityTexture, entityNumElements, direction, damage);
	g->team = team;
	World::gameObjects.push_back(g);

}
