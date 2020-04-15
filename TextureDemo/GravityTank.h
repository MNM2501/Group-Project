#pragma once
#include "Tank.h"
class GravityTank :
	public Tank
{
public:
	GravityTank(glm::vec3& entityPos, std::vector<GLuint> entityTextures, GLint entityNumElements, int ap, PlayerGameObject* player);
	
	virtual void fire() override;

};

