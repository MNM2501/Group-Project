#pragma once
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include "PlayerGameObject.h"

using namespace std;

class GameObject;

class Factory
{
public:
	Factory();

	static std::vector<GLuint> textures;

	static void spawnGameObject(glm::vec3 &entityPosition, GLuint entityTexture);
	static void spawnBulletGameObject(glm::vec3& entityPos, GLuint entityTexture, glm::vec3 direction, string team, int damage);
	static void spawnPlayerGameObject(glm::vec3 &entityPos);
	static void spawnEnemyGameObject(glm::vec3& entityPos, float theSpeed, int theHealth, int ap);
	static void spawnTank(glm::vec3& entityPos, int ap);
	static void spawnBomb(glm::vec3& entityPos, int damage, string team);
	static void spwnPowerup(glm::vec3 &entityPosition);
	static void spawnGravityTank(glm::vec3& entityPos, int ap);
	static void spawnGravityBullet(glm::vec3& entityPos, GLuint texture, glm::vec3 direction, int damage, string team);
	static void spawnAlienBomb(glm::vec3 &entityPosition);
	static void spawnChaser(glm::vec3 position, std::vector<std::vector<int>> grid);
	static void spawnKamikaze(glm::vec3 position);
	static void spawnLavaTile(glm::vec3 position);

private:
	static int numElements;
	static PlayerGameObject* player;
};

