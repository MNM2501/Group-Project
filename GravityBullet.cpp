#include "GravityBullet.h"

GravityBullet::GravityBullet(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, glm::vec3 direction, int damage):
	BulletGameObject(entityPos, entityTexture, entityNumElements, direction, damage)
{
	sv.hasMaxSpeed = false;
	sv.minv = 1;
	sv.noGravity = false;
	sv.velocity = glm::vec3(0);
	addForce(glm::normalize(direction) * 8.0f);
}

void GravityBullet::update(double deltaTime)
{
	//determine angle
	glm::vec3 direction = glm::normalize(sv.velocity);
	angle = atan2(direction.y, direction.x);

	sv.update(glm::vec3(0));
}
