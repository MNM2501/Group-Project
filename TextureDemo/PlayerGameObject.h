#pragma once

#include "GameObject.h"
#include "World.h"
#include "BulletGameObject.h"

// Inherits from GameObject
class PlayerGameObject : public GameObject {
public:
	PlayerGameObject(glm::vec3 &entityPos, GLuint entityTexture, GLint entityNumElements);

	// Update function for moving the player object around
	virtual void update(double deltaTime) override;
	
	virtual void collide(string otherType, glm::vec3 normal, GameObject* otherObject) override;

	virtual void receiveDmg(int dmg) override;

	bool getCanFire() { return canFire; }

	//tells player it has fired
	void fire();

	float getHitBox() { return hitBox; }


private:
	//handles firing
	float prevFire;
	float fireCooldown;
	bool canFire;

	

};
