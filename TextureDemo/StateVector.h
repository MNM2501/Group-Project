#pragma once
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>

class StateVector
{
public:
	StateVector();
	
	void update(glm::vec3 force = glm::vec3());


	static float deltaTime;
	float minv;
	float maxSpeed;

	glm::vec3 position;
	glm::vec3 momentum;
	glm::vec3 velocity;
	glm::vec3 velocityRaw;

	// regulate max speed and apply gravity
	bool hasMaxSpeed;
	bool noGravity;

};

