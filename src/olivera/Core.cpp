#include "Core.h"
#include "Entity.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Environment.h"
#include "CameraContext.h"
#include <GL/glew.h>
#include <iostream>
#include "ResourceManager.h"

#include "PostProcessing.h"
#include "ShaderProgram.h"
#include "VertexArray.h"

namespace olivera
{
  std::shared_ptr<Core> Core::initialise(int _windowWidth, int _windowHeight)
  {
    std::shared_ptr<Core> core = std::make_shared<Core>();

    core->running = false;
    core->self = core;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      throw std::exception();
    }

    core->window = SDL_CreateWindow("Olivera Engine",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      _windowWidth, _windowHeight,
      SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_GRABBED);
	
	//Lock Mouse
 //   SDL_ShowCursor(SDL_DISABLE);
    
	core->environment->initialise();
    if (!SDL_GL_CreateContext(core->window))
    {
      throw std::exception();
    }

    if (glewInit() != GLEW_OK)
    {
      throw std::exception();
    }
    
    core->device = alcOpenDevice(NULL);

    if (!core->device)
    {
      throw std::exception();
    }

    core->context = alcCreateContext(core->device, NULL);

    if (!core->context)
    {
      alcCloseDevice(core->device);
      throw std::exception();
    }

    if (!alcMakeContextCurrent(core->context))
    {
      alcDestroyContext(core->context);
      alcCloseDevice(core->device);
      throw std::exception();
    }
    


    return core;
  }
  
  std::shared_ptr<Keyboard> Core::getKeyboard()
  {
    return keyboard;
  }

  std::shared_ptr<CameraContext> Core::getCameraList()
  {
    return cameraContext;
  }

  std::shared_ptr<ResourceManager> Core::getResources()
  {
	  return resources;
  }



  std::shared_ptr<Mouse> Core::getMouse()
  {
    return mouse;
  }

  std::shared_ptr<Environment> Core::getEnvironment()
  {
    return environment;
  }

  void Core::start()
  {
    running = true;
    SDL_SetRelativeMouseMode(SDL_TRUE);

    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    while (running)
    {
      SDL_Event event;

      while (SDL_PollEvent(&event))
      {
        switch (event.type)
        {
        case SDL_KEYDOWN:
          keyboard->isKeyPressed(event.key.keysym.scancode);
          break;
        case SDL_KEYUP:
          keyboard->isKeyReleased(event.key.keysym.scancode);
          break;
        case SDL_MOUSEMOTION:
          mouse->tick(event.motion.xrel, event.motion.yrel);
          break;
        }

        if (keyboard->getKeyPressed().size() > 0)
        {
          if (keyboard->getKeyPressed().at(0) == SDL_SCANCODE_ESCAPE)
          {
            running = false;
          }
        }
      }
      //Removes Cursor mouse position will be at the center of the window, use relative motion

      //Set relativeMotion


      for (std::vector<std::shared_ptr<Entity> >::iterator it = entities.begin();
        it != entities.end(); it++)
      {
        (*it)->tick();
      }

      //Clear keys after each frame
     //Set delta Time and set frame rate to 60fps





      environment->tick();
      keyboard->clearKey();


      //Set the main Viewport
      glViewport(0, 0, windowWidth, windowHeight);

      //Set smaller viewports to which to draw each camera's output
      for (int i = 0; i < cameraContext->getCameraList().size(); i++)
      {

        cameraContext->getCameraList().at(i)->activeFrameBuffer();

          for (std::vector<std::shared_ptr<Entity> >::iterator it = entities.begin();
            it != entities.end(); it++)
          {
            (*it)->display();
          }

        cameraContext->getCameraList().at(i)->clear();
       
      }

     
      for (int i = 0; i < cameraContext->getCameraList().size(); i++)
      {

          glViewport(cameraContext->getCameraList().at(i)->getViewport().x,
            cameraContext->getCameraList().at(i)->getViewport().y,
            cameraContext->getCameraList().at(i)->getViewport().z,
            cameraContext->getCameraList().at(i)->getViewport().w);
      
        cameraContext->getCameraList().at(i)->useFrameBuffer();
        
      }
      SDL_GL_SwapWindow(window);

    }
  }

  void Core::stop()
  {
    running = false;
  }

  int Core::getScreenWidth()
  {
    return windowWidth;
  }

  int Core::getScreenHeight()
  {
    return windowHeight;
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