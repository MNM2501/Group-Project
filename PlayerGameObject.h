#pragma once

#include "GameObject.h"

// Inherits from GameObject
class PlayerGameObject : public GameObject {
public:
	PlayerGameObject(glm::vec3 &entityPos, GLuint entityTexture, GLint entityNumElements);

	// Update function for moving the player object around
	virtual void update(double deltaTime) override;
	void decreaseDownTime() { downTime -= 1; }
	void resetDownTime() { downTime = 50; }
	void decreaseHealth() { health -= 1; }
	void resetIframes() { IF = 50; }
	void decreaseIFrames() { IF -= 1; }
	void setIFrames(int frames) { IF = frames; }


	int getDownTime() { return downTime; }
	int getHealth() { return health;  }
	int getIFrames() { return IF; }
	float getHitBox() { return hitBox; }
private:
	int downTime;
	int health;
	int IF;
	float hitBox;
};
