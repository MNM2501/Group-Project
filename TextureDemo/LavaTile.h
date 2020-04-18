#pragma once
#include "GameObject.h"
class LavaTile :
	public GameObject
{
public:
	LavaTile(glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements);

	virtual void update(double deltaTime) override;
	virtual void receiveDmg(int dmg) override;
};

