#include "Component.h"
#include "Entity.h"
namespace olivera
{
  Component::~Component() { }

  std::shared_ptr<Entity> Component::getEntity()
  {
    return entity.lock();
  }
  std::shared_ptr<Core> Component::getCore()
  {
    return getEntity()->getCore();
  }

  void Component::onInitialise()
  {

  }
  void Component::onStart()
  {

  }
  void Component::onTick()
  {

  }
  void Component::onDisplay()
  {

  }
}