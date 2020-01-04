#include "InputManager.h"
#include "FPSCamera.h"
#include <iostream>


  

  void InputManager::CameraMovement()
  {
 //   const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

    if (keyboard->getKeyPressed().size() > 0)
    {
      

        if (keyboard->getKeyPressed().at(0) == SDL_SCANCODE_W)
        {
          camera->ProcessKeyboard(camera->FORWARD, core->getEnvironment()->getDeltaTime()*2.5);
          std::cout << "Moved: Forward" << std::endl;
        }
        if (keyboard->getKeyPressed().at(0) == SDL_SCANCODE_S)
        {
          camera->ProcessKeyboard(camera->BACKWARD, core->getEnvironment()->getDeltaTime()*2.5);
          std::cout << "Moved: Backward" << std::endl;
        }
        if (keyboard->getKeyPressed().at(0) == SDL_SCANCODE_A)
        {
          camera->ProcessKeyboard(camera->LEFT, core->getEnvironment()->getDeltaTime()*2.5);
          std::cout << "Moved: Left" << std::endl;
        }
        if (keyboard->getKeyPressed().at(0) == SDL_SCANCODE_D)
        {
          camera->ProcessKeyboard(camera->RIGHT, core->getEnvironment()->getDeltaTime()*2.5);
          std::cout << "Moved: Right" << std::endl;
        }
      
    }


    mouse_callback(core->getMouse()->getXCoordinate(), core->getMouse()->getYCoordinate());
  }

  void InputManager::onInitialise()
  {
    core = getCore();
    
    std::cout << "Initialise Input Manager" << std::endl;
    
    entitySelf = getEntity();

    //Initial Camera XY coordinates
     lastX = 800 / 2.0f;
     lastY = 600 / 2.0f;
  }

  void InputManager::onTick()
  {
    camera = entitySelf->getComponent<FPSCamera>();
    keyboard = core->getKeyboard();
    CameraMovement();
  }

  void InputManager::mouse_callback(double xpos, double ypos)
  {
    if (firstMouse)
    {
      lastX = xpos;
      lastY = ypos;
      firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera->ProcessMouseMovement(xoffset, yoffset, true);
  }

