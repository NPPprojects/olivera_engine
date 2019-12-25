#include "Core.h"
#include "Entity.h"
#include "Component.h"
namespace olivera
{
  std::shared_ptr<Core> Core::initialise()
  {
    std::shared_ptr<Core> core = std::make_shared<Core>();
    core->running = false;
    core->self = core;

    return core;
  }

  void Core::start()
  {
    running = true;

    while (running)
    {
      for (std::vector<std::shared_ptr<Entity> >::iterator it = entities.begin();
        it != entities.end(); it++)
      {
        (*it)->tick();
      }

      for (std::vector<std::shared_ptr<Entity> >::iterator it = entities.begin();
        it != entities.end(); it++)
      {
        (*it)->display();
      }
    }
  }
  void Core::stop()
  {
    running = false;
  }

  std::shared_ptr<Entity> Core::addEntity()
  {
    std::shared_ptr<Entity> entity = std::make_shared<Entity>();
    entities.push_back(entity);
    entity->self = entity;
    entity->core = self;

    return entity;
  }
}