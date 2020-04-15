#pragma once
#include "BulletGameObject.h"
class GravityBullet :
	public BulletGameObject
{
public:
	GravityBullet(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, glm::vec3 direction, int damage);

	virtual void update(double deltaTime) override;

};

