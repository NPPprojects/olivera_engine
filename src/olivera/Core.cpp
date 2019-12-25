#include "Core.h"
#include "Entity.h"

#include <GL/glew.h>

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

    core->window = SDL_CreateWindow("My Engine",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      WINDOW_WIDTH, WINDOW_HEIGHT,
      SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

    if (!SDL_GL_CreateContext(core->window))
    {
      throw std::exception();
    }

    if (glewInit() != GLEW_OK)
    {
      throw std::exception();
    }

    //core->device = alcOpenDevice(NULL);

    //if (!rtn->device)
    //{
    //  throw std::exception();
    //}

    //core->context = alcCreateContext(rtn->device, NULL);

    //if (!rtn->context)
    //{
    //  alcCloseDevice(rtn->device);
    //  throw std::exception();
    //}

    //if (!alcMakeContextCurrent(rtn->context))
    //{
    //  alcDestroyContext(rtn->context);
    //  alcCloseDevice(rtn->device);
    //  throw std::exception();
    //}

    return core;
  }

  void Core::start()
  {
    running = true;

    while (running)
    {
      SDL_Event event = { 0 };

      while (SDL_PollEvent(&event))
      {
        if (event.type == SDL_QUIT)
        {
          running = false;
        }
      }

      for (std::vector<std::shared_ptr<Entity> >::iterator it = entities.begin();
        it != entities.end(); it++)
      {
        (*it)->tick();
      }

      glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      for (std::vector<std::shared_ptr<Entity> >::iterator it = entities.begin();
        it != entities.end(); it++)
      {
        (*it)->display();
      }

      SDL_GL_SwapWindow(window);
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