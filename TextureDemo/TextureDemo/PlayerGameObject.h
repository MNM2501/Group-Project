#pragma once

#include "GameObject.h"

// Inherits from GameObject
class PlayerGameObject : public GameObject {
public:
	PlayerGameObject(glm::vec3 &entityPos, GLuint entityTexture, GLint entityNumElements);

	// Update function for moving the player object around
	virtual void update(double deltaTime) override;
	void decreaseDownTime() { downTime -= 1; }
	int getDownTime() { return downTime; }
	void resetDownTime() { downTime = 50; }
private:
	int downTime; 
};
