#include "Entity.h"

namespace olivera
{
  std::shared_ptr<Core> Entity::getCore()
  {
    return core.lock();
  }

  void Entity::tick()
  {
    for (std::vector<std::shared_ptr<Component> >::iterator it = components.begin();
      it != components.end(); it++)
    {
      if (!(*it)->began)
      {
        (*it)->onStart();
        (*it)->began = true;
      }

      (*it)->onTick();
    }

  }

  void Entity::shadowDisplay()
  {
    for (std::vector<std::shared_ptr<Component> >::iterator it = components.begin();
      it != components.end(); it++)
    {
      (*it)->onShadowDisplay();
    }
  }

  void Entity::display()
  {
    for (std::vector<std::shared_ptr<Component> >::iterator it = components.begin();
      it != components.end(); it++)
    {
      (*it)->onDisplay();
    }
  }

}