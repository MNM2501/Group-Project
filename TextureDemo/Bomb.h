#pragma once
#include "BulletGameObject.h"
class Bomb :
	public BulletGameObject
{
public:
	Bomb(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, int damage);
	~Bomb();
};

