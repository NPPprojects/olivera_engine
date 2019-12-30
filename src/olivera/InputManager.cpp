#include "InputManager.h"
#include "Keyboard.h"
#include "Core.h"
#include "Entity.h"
#include "Camera.h"

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
 
      if (keyboard->getKeyPressed().at(0) == SDL_SCANCODE_W)
      {
        camera->ProcessKeyboard(camera->FORWARD, 2.5);
      }
      
    }
  }

  void InputManager::onInitialise()
  {
    core = getCore();
    
    std::cout << "Sup";
    
    entitySelf = getEntity();
  }

  void InputManager::onTick()
  {
    camera = entitySelf->getComponent<Camera>();
    keyboard = core->getKeyboard();
    CameraMovement();
  }

}

//
//void processInput(GLFWwindow *window)
//{
//  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//    glfwSetWindowShouldClose(window, true);
//
//  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//    camera.ProcessKeyboard(FORWARD, deltaTime);
//  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//    camera.ProcessKeyboard(BACKWARD, deltaTime);
//  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//    camera.ProcessKeyboard(LEFT, deltaTime);
//  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//    camera.ProcessKeyboard(RIGHT, deltaTime);