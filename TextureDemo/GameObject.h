#pragma once

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>

#include "Shader.h"
#include "ObjectTypes.h"
#include "StateVector.h"

using namespace std;
class GameObject {
public:
	GameObject(glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements);

	string type;
	string team;

	// Updates the GameObject's state. Can be overriden for children
	virtual void update(double deltaTime);

	// Renders the GameObject using a shader
	virtual void render(Shader &shader);

	//handles collision
	virtual void collide(string otherType, glm::vec3 normal, GameObject* otherObject);

	//adds a force
	void addForce(glm::vec3 force);

	//receiving damage
	virtual void receiveDmg(int dmg);


	//stops object movement
	void stop();

	// Getters
	inline glm::vec3& getPosition() { return sv.position; }
	inline glm::vec3& getVelocity() { return sv.velocity; }
	inline int getxDirect() { return xDirection; }
	inline int getHealth() { return health; }
	inline float getHitBox() { return hitBox; }
	// Setters
	inline void setPosition(glm::vec3& newPosition) { sv.position = newPosition; }
	inline void setVelocity(glm::vec3& newVelocity) { sv.velocity = newVelocity; }


	void setTexture(GLuint t) { texture = t; }

	//plays hurt effect when hit.
	void hurtEffect(Shader& shader);

	bool shouldDie;

protected:
	// Object's Transform Variables
	// TODO: Add more transformation variables
	StateVector sv;
	int xDirection;
	int yDirection;
	float speed;
	float hitBox;

	// Object's details
	GLint numElements;
	float objectSize; // Not currently being used (will be needed for collision detection when objects have a different scale)

	// Object's texture
	GLuint texture;

	//handle damage taking
	int health;
	float prevDmg;
	float dmgCooldown;
	bool canReceiveDmg;


	//hurt effect
	bool shaderClockSet; // allows for hurt effect to happen over t = 0 when dmg is received
};