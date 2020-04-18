#include "Factory.h"

#include "GameObject.h"
#include "Tank.h"
#include "BulletGameObject.h"
#include "EnemyGameObject.h"
#include "World.h"
#include "Bomb.h"
#include "Powerup.h"
#include "GravityTank.h"
#include "GravityBullet.h"
#include "ChaserGameObject.h"
#include "KamikazeEnemy.h"



PlayerGameObject* Factory::player = NULL;
std::vector<GLuint> Factory::textures = std::vector<GLuint>();

int Factory::numElements = 6;

Factory::Factory()
{
}


void Factory::spawnGameObject(glm::vec3 &entityPosition, GLuint entityTexture)
{
	World::gameObjects.push_back(new GameObject(entityPosition, entityTexture, numElements));
}

void Factory::spawnBulletGameObject(glm::vec3& entityPos, GLuint entityTexture, glm::vec3 direction, string team, int damage)
{
	BulletGameObject* b = new BulletGameObject(entityPos, entityTexture, numElements, direction, damage);
	b->team = team;
	World::gameObjects.push_back(b);
}

void Factory::spawnPlayerGameObject(glm::vec3 &entityPos)
{
	PlayerGameObject* player = new PlayerGameObject(entityPos, textures[0], numElements);
	Factory::player = player;
	World::gameObjects.push_back(player);
}

void Factory::spawnEnemyGameObject(glm::vec3& entityPos, float theSpeed, int theHealth, int ap)
{
	std::vector<GLuint> enemySprites = { textures[7], textures[23] };
	World::gameObjects.push_back(new EnemyGameObject(entityPos, enemySprites, numElements, theSpeed, theHealth, ap, player));
}

void Factory::spawnTank(glm::vec3& entityPos, int ap)
{
	std::vector<GLuint> tankSprites = { textures[21], textures[23], textures[22] }; // body, bullet, turret
	World::gameObjects.push_back(new Tank(entityPos, tankSprites, numElements, ap, player));
}

void Factory::spawnBomb(glm::vec3& entityPos, int damage, string team)
{
	Bomb* b = new Bomb(entityPos, textures[24], numElements, damage);
	b->team = team;
	World::gameObjects.push_back(b);
}

void Factory::spwnPowerup(glm::vec3 &entityPosition)
{
	World::gameObjects.push_back(new Powerup(entityPosition, textures[25], numElements));
}

void Factory::spawnGravityTank(glm::vec3& entityPos, int ap)
{
	std::vector<GLuint> tankSprites = { textures[26], textures[23], textures[22] };
	GravityTank* g = new GravityTank(entityPos, tankSprites, numElements,ap, player);


	World::gameObjects.push_back(g);
}

void Factory::spawnGravityBullet(glm::vec3& entityPos, GLuint texture, glm::vec3 direction, int damage, string team)
{
	GravityBullet* g = new GravityBullet(entityPos, texture, numElements, direction, damage);
	g->team = team;
	World::gameObjects.push_back(g);

}

void Factory::spawnAlienBomb(glm::vec3 &entityPosition)
{
	GameObject* g = new GameObject(entityPosition, textures[27], numElements);
	g->type = ALIEN_BOMB;
	World::gameObjects.push_back(g);
}

void Factory::spawnChaser(glm::vec3 position, std::vector<std::vector<int>> grid)
{
	ChaserGameObject* c = new ChaserGameObject(position, textures[45], numElements, grid);
	World::gameObjects.push_back(c);
}

void Factory::spawnKamikaze(glm::vec3 position)
{
	std::vector<GLuint> kamikazesprites = { textures[8], textures[23] };

	KamikazeEnemy* k = new KamikazeEnemy(position, kamikazesprites, numElements, player);
	World::gameObjects.push_back(k);
}

void Factory::spawnLavaTile(glm::vec3 position)
{
	GameObject* g = new GameObject(position, textures[33], numElements);
	g->type = LAVA;
	World::gameObjects.push_back(g);
}
