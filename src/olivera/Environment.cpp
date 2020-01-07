#include "Component.h"
#include "Environment.h"
#include <SDL2/SDL.h>
namespace olivera
{
  float Environment::getDeltaTime()
  {
    return deltaTime;
  }

  void Environment::initialise() 
  {
    lastTime = SDL_GetTicks();
    idealTime = 1.0f / 60.0f;
  }
  void Environment::tick() 
  {
    float time = SDL_GetTicks();
    float diff = time - lastTime;
    deltaTime = diff / 1000; //convert Delta Time to seconds;
    lastTime = time;
    if (idealTime > deltaTime)
    {
      // Sleep off remaining time
      SDL_Delay((idealTime - deltaTime) * 1000.0f);
    }
  }
}