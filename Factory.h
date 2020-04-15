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
	static void spawnGameObject(glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements);
	static void spawnBulletGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, glm::vec3 direction, string team, int damage);
	static void spawnPlayerGameObject(glm::vec3 &entityPos, GLuint entityTexture, GLint entityNumElements);
	static void spawnEnemyGameObject(glm::vec3& entityPos, std::vector<GLuint> entityTextures, GLint entityNumElements, float theSpeed, int theHealth, int ap, 
		PlayerGameObject* player);
	static void spawnTank(glm::vec3& entityPos, std::vector<GLuint> entityTextures, GLint entityNumElements, int ap, PlayerGameObject* player);
	static void spawnBomb(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, int damage, string team);
	static void spwnPowerup(glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements);
	static void spawnGravityTank(glm::vec3& entityPos, std::vector<GLuint> entityTextures, GLint entityNumElements, int ap, PlayerGameObject* player);
	static void spawnGravityBullet(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, glm::vec3 direction, int damage, string team);

private:
	static PlayerGameObject* player;
};

