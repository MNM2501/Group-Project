#include "Powerup.h"
#include "PlayerGameObject.h";



Powerup::Powerup(glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements) :
	GameObject(entityPosition, entityTexture, entityNumElements)
{
	type = POWERUP;
	health = 1;
	duration = 7;
	cooldownDivider = 2;
}

void Powerup::receiveDmg(int dmg)
{
	return;
}

void Powerup::collide(int otherType, glm::vec3 normal, GameObject* otherObject)
{
	if (otherType == PLAYER)
	{
		PlayerGameObject* player = dynamic_cast<PlayerGameObject*>(otherObject);
		player->setPowerup(this);
		shouldDie = true;
	}

}

