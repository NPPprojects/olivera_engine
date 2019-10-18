#include "Core.h"
#include "Entity.h"
#include "Component.h"
void Core::start()
{
	running = true;
}
void Core::stop()
{
	running = false;
}

std::shared_ptr<Core> Core::initialise()
{
	std::shared_ptr<Core> core = std::make_shared<Core>();
	return core;
}

std::shared_ptr<Entity> Core::addEntity()
{
	std::shared_ptr<Entity> entity = std::make_shared<Entity>();
	this->entity.push_back(entity);

	return entity;
}