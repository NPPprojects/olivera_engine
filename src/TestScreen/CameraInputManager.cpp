#include "CameraInputManager.h"
#include "FPSCamera.h"
#include <iostream>


  

  void CameraInputManager::CameraMovement()
  {
    keysHeld();
	  if (WASDPressed.w == true)
	  {
		  camera.lock()->ProcessKeyboard(camera.lock()->FORWARD, core.lock()->getEnvironment()->getDeltaTime() * 1);
		  std::cout << "Moved: FORWARD" << std::endl;
		  if (WASDReleased.w == true)
		  {
			  WASDPressed.w = false;
		  }
	  }
	 
	  if (WASDPressed.d == true)
	  {
		  camera.lock()->ProcessKeyboard(camera.lock()->RIGHT, core.lock()->getEnvironment()->getDeltaTime() * 1);
		  std::cout << "Moved: RIGHT" << std::endl;
		  if (WASDReleased.d == true)
		  {
			  WASDPressed.d = false;
		  }
	  }
	 
	  if (WASDPressed.a == true)
	  {
		  camera.lock()->ProcessKeyboard(camera.lock()->LEFT, core.lock()->getEnvironment()->getDeltaTime() * 1);
		  std::cout << "Moved: LEFT" << std::endl;
		  if (WASDReleased.a == true)
		  {
			  WASDPressed.a = false;
		  }
	  }
	  if (WASDPressed.s == true)
	  {
		  camera.lock()->ProcessKeyboard(camera.lock()->BACKWARD, core.lock()->getEnvironment()->getDeltaTime() * 1);
		  std::cout << "Moved: DOWN" << std::endl;
		  if (WASDReleased.s == true)
		  {
			  WASDPressed.s = false;
		  }
	  }
    
    if (core.lock()->getMouse()->getMouseState()==true)
    {
      mouse_callback(core.lock()->getMouse()->getXMotion(), core.lock()->getMouse()->getYMotion());
      core.lock()->getMouse()->setMouseState(false);
      
    }
    
  }

  void CameraInputManager::onInitialise()
  {
    core = getCore();
    
    std::cout << "Initialise Input Manager" << std::endl;
    
    entitySelf = getEntity();

    //Initial Camera XY coordinates
 
	
  }

  void CameraInputManager::onTick()
  {
    camera = entitySelf.lock()->getComponent<FPSCamera>();
    keyboard = core.lock()->getKeyboard();
    CameraMovement();
  }

  void CameraInputManager::mouse_callback(double xpos, double ypos)
  {

    xoffset = xpos - lastX;
    yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    
    //std::cout << xoffset<<": X offset" << std::endl;
   // std::cout << yoffset<< ": Y offset"<< std::endl;
    lastX = xpos;
    lastY = -ypos;
     
    camera.lock()->ProcessMouseMovement(lastX, lastY, true);
  }

  void CameraInputManager::keysHeld()
  {
	  if (keyboard.lock()->getKeyPressed().size() > 0)
	  {

		  for (int i = 0; i < keyboard.lock()->getKeyPressed().size(); i++)
		  {
			  if (keyboard.lock()->getKeyPressed().at(i) == SDL_SCANCODE_W)
			  {
				  WASDPressed.w = true;
			  }
			  if (keyboard.lock()->getKeyPressed().at(i) == SDL_SCANCODE_S)
			  {
				  WASDPressed.s = true;
			  }
			  if (keyboard.lock()->getKeyPressed().at(i) == SDL_SCANCODE_D)
			  {
				  WASDPressed.d = true;
			  }
			  if (keyboard.lock()->getKeyPressed().at(i) == SDL_SCANCODE_A)
			  {
				  WASDPressed.a = true;
			  }

		  }
	  }


	  if (keyboard.lock()->getKeyReleased().size() > 0)
	  {

		  for (int i = 0; i < keyboard.lock()->getKeyReleased().size(); i++)
		  {
			  if (keyboard.lock()->getKeyReleased().at(i) == SDL_SCANCODE_W)
			  {
				  WASDReleased.w = true;
			  }
			  if (keyboard.lock()->getKeyReleased().at(i) == SDL_SCANCODE_S)
			  {
				  WASDReleased.s = true;
			  }
			  if (keyboard.lock()->getKeyReleased().at(i) == SDL_SCANCODE_D)
			  {
				  WASDReleased.d = true;
			  }
			  if (keyboard.lock()->getKeyReleased().at(i) == SDL_SCANCODE_A)
			  {
				  WASDReleased.a = true;
			  }
			  

		  }
	  }
	  else if (keyboard.lock()->getKeyReleased().size() == 0)
	  {
		  WASDReleased.w = false;
		  WASDReleased.s = false;
		  WASDReleased.d = false;
		  WASDReleased.a = false;
	  }
  }

