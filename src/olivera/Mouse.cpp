#include "Mouse.h"
#include <SDL2/SDL.h>
namespace olivera 
{
  int Mouse::getXCoordinate()
  {
    return x;
  }
  int Mouse::getYCoordinate()
  {
    return y;
  }
  void Mouse::tick() 
  {
    SDL_PumpEvents();
    SDL_GetMouseState(&x, &y);
  }

}