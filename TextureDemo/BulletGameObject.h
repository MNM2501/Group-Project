#pragma once
#include "GameObject.h"
#include "PlayerGameObject.h"

class BulletGameObject :
	public GameObject
{
	public:
		BulletGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, glm::vec3 direction);

		// Update function for moving the player object around
		virtual void update(double deltaTime) override;
		virtual void render(Shader& shader) override;

		//setters
		void setSpeed(float newSpeed) { speed = newSpeed; }
		void setAngle(float newAngle) { angle = newAngle; }

		//getters
		float getSpeed() { return speed; }
		float getAngle() { return angle; }
		float getHitBox() { return hitBox; }
		
		virtual void collide(string otherType, glm::vec3 normal, GameObject* otherObject) override;


	private:
		float speed;
		float angle;
};

