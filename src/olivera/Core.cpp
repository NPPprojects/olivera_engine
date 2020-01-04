#include "Core.h"
#include "Entity.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Environment.h"
#include "CurrentCamera.h"
#include <GL/glew.h>
#include <iostream>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

namespace olivera
{
  std::shared_ptr<Core> Core::initialise()
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
      WINDOW_WIDTH, WINDOW_HEIGHT,
      SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

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

  std::shared_ptr<CurrentCamera> Core::getCurrentCamera()
  {
    return cameraContext;
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
    
    while (running)
    {
      SDL_Event event;
      while (SDL_PollEvent(&event))
      {
        keyboard->SetKeyboardState();
        switch (event.type)
        {
        case SDL_KEYDOWN:
          keyboard->isKeyPressed(event.key.keysym.scancode);
          break;
        case SDL_KEYUP:
          keyboard->isKeyReleased(event.key.keysym.scancode);
          break;
        }

        if (event.type == SDL_QUIT)
        {
          running = false;
        }

        if (keyboard->getKeyPressed().size() > 0)
        {
          if (keyboard->getKeyPressed().at(0) == SDL_SCANCODE_ESCAPE)
          {
            running = false;
          }
        }
        
      }
        for (std::vector<std::shared_ptr<Entity> >::iterator it = entities.begin();
          it != entities.end(); it++)
        {
          (*it)->tick();
        }
      
      //Clear keys after each frame
     //Set delta Time and set frame rate to 60fps
        mouse->tick();
        environment->tick();
        keyboard->clearKey();
     
      glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      for (std::vector<std::shared_ptr<Entity> >::iterator it = entities.begin();
        it != entities.end(); it++)
      {
        (*it)->display();
      }

      SDL_GL_SwapWindow(window);
      glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    }
  }
  void Core::stop()
  {
    running = false;
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