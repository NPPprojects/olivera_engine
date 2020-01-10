#include "Transform.h"
#include "glm/gtx/transform.hpp"

glm::mat4 olivera::Transform::getModel()
{
	return model;
}

void olivera::Transform::updateModel()
{
	glm::mat4 model = glm::mat4(1.0f);	
	model = glm::translate(model, position);
	model = glm::scale(model, scale);
}

void olivera::Transform::setPosition(glm::vec3 _position)
{
	position += _position;
}

void olivera::Transform::setRotation(glm::vec3 _rotation)
{
	rotation += _rotation;
}

void olivera::Transform::setScale(glm::vec3 _scale)
{
	scale += _scale;
}

glm::vec3 olivera::Transform::getPosition()
{
	return position;
}

glm::vec3 olivera::Transform::getRotation()
{
	return rotation;
}

glm::vec3 olivera::Transform::setScale()
{
	return scale;
}

void olivera::Transform::onTick()
{
	updateModel();
}

void olivera::Transform::onInitialise()
{
	
	position = glm::vec3(0.0f);
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(0.0f);
}
