#include "StateVector.h"

float StateVector::deltaTime = 0.0f;

StateVector::StateVector()
{
	velocity = glm::vec3(0, 0, 0);
	momentum = glm::vec3(0, 0, 0);
	resting = true;
}


void StateVector::update(glm::vec3 force)
{
	glm::vec3 gravity = !resting ?  glm::vec3(0, -9.8f, 0) * deltaTime : glm::vec3(0,0,0);
	momentum += (gravity + force) * deltaTime ;
	velocity = minv * momentum;
	velocityRaw = velocity / deltaTime;
	position += glm::length(velocity) > maxSpeed * deltaTime ? glm::normalize(velocity) * maxSpeed * deltaTime : velocity;
}
