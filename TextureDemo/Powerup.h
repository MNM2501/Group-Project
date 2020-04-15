#pragma once
#include "GameObject.h"
class Powerup :
	public GameObject
{
public:
	Powerup(glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements);

	virtual void collide(int otherType, glm::vec3 normal, GameObject* otherObject) override;

	virtual void receiveDmg(int dmg) override;

	float duration;
	float cooldownDivider;
};

