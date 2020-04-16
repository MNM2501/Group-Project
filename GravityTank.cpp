#include "GravityTank.h"

GravityTank::GravityTank(glm::vec3& entityPos, std::vector<GLuint> entityTextures, GLint entityNumElements, int ap, PlayerGameObject* player):
	Tank(entityPos, entityTextures, entityNumElements, ap, player)
{
	type = GRAVITY_TANK;
	cooldown = 5.0f;
	soulDrop = 15;
}

void GravityTank::fire()
{
	Factory::spawnGravityBullet(getPosition() + glm::vec3(0, 0.0f, 0), bulletTexture,
		glm::normalize(player->getPosition() - getPosition()), 10, team);

	prevTime = glfwGetTime();
}