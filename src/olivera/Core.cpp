#include "Core.h"
#include "Entity.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Environment.h"
#include "CurrentCamera.h"
#include <GL/glew.h>
#include <iostream>
#include "ResourceManager.h"

#include "PostProcessing.h"
#include "ShaderProgram.h"
#include "VertexBuffer.h"

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

  std::shared_ptr<CurrentCamera> Core::getCurrentCamera()
  {
    return cameraContext;
  }

  std::shared_ptr<ResourceManager> Core::getResources()
  {
	  return resources;
  }

  void Core::setPostProcessing(std::shared_ptr<Core> _core, std::string _shader, std::string _mesh, int _windowWidth, int _windowHeight)
  {
    postProcessing = std::make_shared<PostProcessing>(_core,_shader,_mesh,_windowWidth,_windowHeight);
  }

  std::shared_ptr<Mouse> Core::getMouse()
  {
    return mouse;
  }

  std::shared_ptr<Environment> Core::getEnvironment()
  {
    return environment;
  }

  void Core::start(int _viewportWidth, int _viewportHeight)
  {
    running = true;
    SDL_SetRelativeMouseMode(SDL_TRUE);
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
        case SDL_MOUSEMOTION:
          mouse->tick(event.motion.xrel, event.motion.yrel);
          mouse->setMouseState(true);
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
     
        ///PostProcessing

        if (postProcessing != nullptr) 
        {
          glBindFramebuffer(GL_FRAMEBUFFER, postProcessing->getFBO());
        }

      glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); // enable depth testing (is di sabled for rendering screen-space quad)


      for (std::vector<std::shared_ptr<Entity> >::iterator it = entities.begin();
        it != entities.end(); it++)
      {
        (*it)->display();
      }

      //Where Code for Post Processing Would go

      if (postProcessing != nullptr)
      {
        //now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
        //clear all relevant buffers
        glClearColor(0.184f, 0.196f, 0.235f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //use the color attachment texture as the texture of the quad plane

        postProcessing->use();

      }

      SDL_GL_SwapWindow(window);
      glViewport(0, 0, _viewportWidth, _viewportHeight);
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