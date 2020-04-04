#include "Mouse.h"
#include <SDL2/SDL.h>
#include <iostream>
namespace olivera 
{

  bool Mouse::getMouseState()
  {
    return isMouseMoving;
  }

  void Mouse::setMouseState(bool _mouseMotion)
  {
    isMouseMoving = _mouseMotion;
  }
  int Mouse::getXCoordinate()
  {
    return xCoord;
  }
  int Mouse::getYCoordinate()
  {
    return yCoord;
  }
  float Mouse::getXMotion()
  {
    return xMotion;
  }
  float Mouse::getYMotion()
  {
    return yMotion;
  }
  void Mouse::setXMotion(int _xRelMotion)
  {
    xMotion = _xRelMotion;
  }
  void Mouse::setYMotion(int _yRelMotion)
  {
    yMotion = _yRelMotion;
  }
  void Mouse::tick(int _xRelMotion, int _yRelMotion )
  {
    SDL_GetMouseState(&xCoord, &yCoord);
    setXMotion(_xRelMotion);
    setYMotion(_yRelMotion);
   
    
  }

}