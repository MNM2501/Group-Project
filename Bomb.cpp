#include "Bomb.h"



Bomb::Bomb(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, int damage) :
	BulletGameObject(entityPos, entityTexture, entityNumElements, glm::vec3(0, -1, 0), damage)
{
	const double PI = 3.14159265358979323846;
	angle = -PI / 2;
}

