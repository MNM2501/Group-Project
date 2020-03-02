#pragma once
#include "GameObject.h"
class BulletGameObject :
	public GameObject
{
	public:
		BulletGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, float theSpeed,float theAngle);

		// Update function for moving the player object around
		virtual void update(double deltaTime) override;
		virtual void render(Shader& shader) override;

		//setters
		void setSpeed(float newSpeed) { speed = newSpeed; }
		void setAngle(float newAngle) { angle = newAngle; }
		void decreaseLifeSpan() { lifeSpan -= 1; }
		void setDead(bool flatline) { dead = flatline; }

		//getters
		float getSpeed() { return speed; }
		float getAngle() { return angle; }
		float getHitBox() { return hitBox; }
		bool isDead() { return dead; }



	private:
		float speed;
		float angle;//in degrees
		float hitBox;//radius of hitbox
		int lifeSpan;//represent how much time left the bullet has until despawn
		bool dead;
};

