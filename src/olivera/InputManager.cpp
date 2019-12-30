#include "InputManager.h"
#include "Keyboard.h"
#include "Core.h"
#include <iostream>
namespace olivera
{


  void InputManager::CameraMovement()
  {
    if (keyboard->getKeyPressed().size() > 0)
    {
      if (keyboard->getKeyPressed().at(0) == SDL_SCANCODE_W)
      {
        std::cout << "Sick";
      }
    }
  }

  void InputManager::onInitialise(std::shared_ptr<Core> _core)
  {
    core = _core;
  }

  void InputManager::onTick()
  {
    keyboard = core->getKeyboard();
    CameraMovement();
  }

}