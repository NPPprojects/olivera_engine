#include "Flashlight.h"
#include "FPSCamera.h"

void Flashlight::onInitialise()
{
  std::cout << "Initialise Flashlight" << std::endl;

}

void Flashlight::onTick()
{

  if (!gameObjects.empty())
  {
    for (int i = 0; i < gameObjects.size(); i++)
    {
      gameObjects.at(i)->getComponent<olivera::Light>()->setFlashlight(entity.lock()->getComponent<FPSCamera>()->getFlashlight());
    }
  }
}

void Flashlight::AddToList(std::shared_ptr<olivera::Entity> _entity)
{
  gameObjects.push_back(_entity);
}

