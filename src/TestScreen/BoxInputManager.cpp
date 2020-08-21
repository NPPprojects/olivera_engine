#include "BoxInputManager.h"

#include <iostream>




void BoxInputManager::BoxMovement()
{
  keysHeld();
  if (UDLRPressed.up == true)
  {
    entitySelf.lock()->getComponent<olivera::Transform>()->setPosition(entitySelf.lock()->getComponent<olivera::Transform>()->getPosition() + glm::vec3(0.0, 0.1f, 0.0f));
  //  std::cout << "Moved: FORWARD" << std::endl;
    if (UDLRReleased.up == true)
    {
      UDLRPressed.up = false;
    }
  }

  if (UDLRPressed.right == true)
  {
    entitySelf.lock()->getComponent<olivera::Transform>()->setPosition(entitySelf.lock()->getComponent<olivera::Transform>()->getPosition() + glm::vec3(0.1f, 0.0f, 0.0f));
  //  std::cout << "Moved: RIGHT" << std::endl;
    if (UDLRReleased.right == true)
    {
      UDLRPressed.right = false;
    }
  }

  if (UDLRPressed.left == true)
  {
    entitySelf.lock()->getComponent<olivera::Transform>()->setPosition(entitySelf.lock()->getComponent<olivera::Transform>()->getPosition() - glm::vec3(0.1f,0.0f,0.0f));
  //  std::cout << "Moved: LEFT" << std::endl;
    if (UDLRReleased.left == true)
    {
      UDLRPressed.left = false;
    }
  }
  if (UDLRPressed.down == true)
  {
    entitySelf.lock()->getComponent<olivera::Transform>()->setPosition(entitySelf.lock()->getComponent<olivera::Transform>()->getPosition() - glm::vec3(0.0,0.1f,0.0f));
  //  std::cout << "Moved: DOWN" << std::endl;
    if (UDLRReleased.down == true)
    {
      UDLRPressed.down = false;
    }
  }


}

void BoxInputManager::onInitialise()
{
  core = getCore();

  std::cout << "Initialise Input Manager" << std::endl;

  entitySelf = getEntity();




}

void BoxInputManager::onTick()
{
 
 
  keyboard = core.lock()->getKeyboard();
  BoxMovement();
}



void BoxInputManager::keysHeld()
{
  if (keyboard.lock()->getKeyPressed().size() > 0)
  {

    for (int i = 0; i < keyboard.lock()->getKeyPressed().size(); i++)
    {
      if (keyboard.lock()->getKeyPressed().at(i) == SDL_SCANCODE_UP)
      {
        UDLRPressed.up = true;
      }
      if (keyboard.lock()->getKeyPressed().at(i) == SDL_SCANCODE_DOWN)
      {
        UDLRPressed.down = true;
      }
      if (keyboard.lock()->getKeyPressed().at(i) == SDL_SCANCODE_RIGHT)
      {
        UDLRPressed.right = true;
      }
      if (keyboard.lock()->getKeyPressed().at(i) == SDL_SCANCODE_LEFT)
      {
        UDLRPressed.left = true;
      }

    }
  }


  if (keyboard.lock()->getKeyReleased().size() > 0)
  {

    for (int i = 0; i < keyboard.lock()->getKeyReleased().size(); i++)
    {
      if (keyboard.lock()->getKeyReleased().at(i) == SDL_SCANCODE_UP)
      {
        UDLRReleased.up = true;
      }
      if (keyboard.lock()->getKeyReleased().at(i) == SDL_SCANCODE_DOWN)
      {
        UDLRReleased.down = true;
      }
      if (keyboard.lock()->getKeyReleased().at(i) == SDL_SCANCODE_RIGHT)
      {
        UDLRReleased.right = true;
      }
      if (keyboard.lock()->getKeyReleased().at(i) == SDL_SCANCODE_LEFT)
      {
        UDLRReleased.left = true;
      }


    }
  }
  else if (keyboard.lock()->getKeyReleased().size() == 0)
  {
    UDLRReleased.up = false;
    UDLRReleased.down = false;
    UDLRReleased.right = false;
    UDLRReleased.left = false;
  }
}

