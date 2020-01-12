#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>


namespace olivera
{

	glm::mat4 Transform::getModel()
	{
		return model;
	}

	void Transform::updateModel()
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, position);	
	}

	void Transform::setPosition(glm::vec3 _position)
	{
		position = _position;
	}

	void Transform::setRotation(glm::vec3 _rotation)
	{
		rotation = _rotation;
	}

	void Transform::setScale(glm::vec3 _scale)
	{
		scale = _scale;
	}

	glm::vec3 Transform::getPosition()
	{
		return position;
	}

	glm::vec3 Transform::getRotation()
	{
		return rotation;
	}

	glm::vec3 Transform::setScale()
	{
		return scale;
	}

	void Transform::onTick()
	{
		updateModel();
	} 

	void Transform::onInitialise()
	{

		position = glm::vec3(0.0f);
		rotation = glm::vec3(0.0f);
		scale = glm::vec3(1.0f);
	}


}