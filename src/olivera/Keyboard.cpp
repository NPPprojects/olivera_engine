#include "Keyboard.h"
#include <iostream>

namespace olivera
{


  bool Keyboard::isKeyPressed(int _key)
  {
    pressedKeys.push_back(_key);
	return released= false;
  
  }
  bool Keyboard::isKeyReleased(int _key)
  {
    releasedKeys.push_back(_key); 
	return released=true;
  }
  void Keyboard::clearKey()
  {
    if (!pressedKeys.empty())
    {
      pressedKeys.clear();
    }
    if (!releasedKeys.empty())
    {
      releasedKeys.clear();
    }
  }

  void Keyboard::SetKeyboardState()
  {
    keyboard_state_array = SDL_GetKeyboardState(NULL);
  }



 
 


  std::vector<int> Keyboard::getKeyPressed()
  {
    return pressedKeys;
  }

  std::vector<int> Keyboard::getKeyReleased()
  {
	  return releasedKeys;
  }


  
}