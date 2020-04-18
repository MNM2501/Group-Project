#include "LavaTile.h"



LavaTile::LavaTile(glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements):
	GameObject(entityPosition, entityTexture, entityNumElements)
{
	type = LAVA;
}

void LavaTile::update(double deltaTime)
{
	//--
}

void LavaTile::receiveDmg(int dmg)
{
	//--
}

