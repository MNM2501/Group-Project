#pragma once

#include "GameObject.h"
#include "World.h"
#include "Powerup.h"

// Inherits from GameObject
class PlayerGameObject : public GameObject {

public:

	PlayerGameObject(glm::vec3 &entityPos, GLuint entityTexture, GLint entityNumElements);

	int damage;

	// Update function for moving the player object around
	virtual void update(double deltaTime) override;
	
	virtual void collide(int  otherType, glm::vec3 normal, GameObject* otherObject) override;

	virtual void receiveDmg(int dmg) override;

	virtual void render(Shader& shader) override;

	bool getCanFire() { return canFire; }

	void setCooldown(float newCooldown) { fireCooldown = newCooldown; }
	void setPowerup(Powerup* p);

	//tells player it has fired
	void fire();

	float getHitBox() { return hitBox; }
	float getFireCooldown() { return fireCooldown; }
	glm::vec3 getFuturePos() { return futurePos; }

private:
	//powerup
	bool hasPowerup;
	float startTimePowerup;
	float powerupDuration;

	//handles firing
	float prevFire;
	float fireCooldown;
	float startFireCooldown;
	bool canFire;
	glm::vec3 futurePos;

	

};
