#include "GravityTank.h"

GravityTank::GravityTank(glm::vec3& entityPos, std::vector<GLuint> entityTextures, GLint entityNumElements, int ap, PlayerGameObject* player):
	Tank(entityPos, entityTextures, entityNumElements, ap, player)
{
	cooldown = 5.0f;
}

void GravityTank::fire()
{
	Factory::spawnGravityBullet(getPosition() + glm::vec3(0, 0.0f, 0), bulletTexture, numElements,
		glm::normalize(player->getPosition() - getPosition()), 10, team);

	prevTime = glfwGetTime();
}