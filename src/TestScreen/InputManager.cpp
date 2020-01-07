#include "InputManager.h"
#include "FPSCamera.h"
#include <iostream>


  

  void InputManager::CameraMovement()
  {

	  KeysHeld();
	  if (WASDPressed.w == true)
	  {
		  camera->ProcessKeyboard(camera->FORWARD, core->getEnvironment()->getDeltaTime() * 1);
		  std::cout << "Moved: FORWARD" << std::endl;
		  if (WASDReleased.w == true)
		  {
			  WASDPressed.w = false;
		  }
	  }
	 
	  if (WASDPressed.d == true)
	  {
		  camera->ProcessKeyboard(camera->RIGHT, core->getEnvironment()->getDeltaTime() * 1);
		  std::cout << "Moved: RIGHT" << std::endl;
		  if (WASDReleased.d == true)
		  {
			  WASDPressed.d = false;
		  }
	  }
	 
	  if (WASDPressed.a == true)
	  {
		  camera->ProcessKeyboard(camera->LEFT, core->getEnvironment()->getDeltaTime() * 1);
		  std::cout << "Moved: LEFT" << std::endl;
		  if (WASDReleased.a == true)
		  {
			  WASDPressed.a = false;
		  }
	  }
	  if (WASDPressed.s == true)
	  {
		  camera->ProcessKeyboard(camera->BACKWARD, core->getEnvironment()->getDeltaTime() * 1);
		  std::cout << "Moved: DOWN" << std::endl;
		  if (WASDReleased.s == true)
		  {
			  WASDPressed.s = false;
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

  void InputManager::KeysHeld()
  {
	  if (keyboard->getKeyPressed().size() > 0)
	  {

		  for (int i = 0; i < keyboard->getKeyPressed().size(); i++)
		  {
			  if (keyboard->getKeyPressed().at(i) == SDL_SCANCODE_W)
			  {
				  WASDPressed.w = true;
			  }
			  if (keyboard->getKeyPressed().at(i) == SDL_SCANCODE_S)
			  {
				  WASDPressed.s = true;
			  }
			  if (keyboard->getKeyPressed().at(i) == SDL_SCANCODE_D)
			  {
				  WASDPressed.d = true;
			  }
			  if (keyboard->getKeyPressed().at(i) == SDL_SCANCODE_A)
			  {
				  WASDPressed.a = true;
			  }

		  }
	  }


	  if (keyboard->getKeyReleased().size() > 0)
	  {

		  for (int i = 0; i < keyboard->getKeyReleased().size(); i++)
		  {
			  if (keyboard->getKeyReleased().at(i) == SDL_SCANCODE_W)
			  {
				  WASDReleased.w = true;
			  }
			  if (keyboard->getKeyReleased().at(i) == SDL_SCANCODE_S)
			  {
				  WASDReleased.s = true;
			  }
			  if (keyboard->getKeyReleased().at(i) == SDL_SCANCODE_D)
			  {
				  WASDReleased.d = true;
			  }
			  if (keyboard->getKeyReleased().at(i) == SDL_SCANCODE_A)
			  {
				  WASDReleased.a = true;
			  }
			  

		  }
	  }
	  else if (keyboard->getKeyReleased().size() == 0)
	  {
		  WASDReleased.w = false;
		  WASDReleased.s = false;
		  WASDReleased.d = false;
		  WASDReleased.a = false;
	  }
  }