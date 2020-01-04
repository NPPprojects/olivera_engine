#include "Keyboard.h"
#include <iostream>

namespace olivera
{

  bool Keyboard::isKey(int key)
  {
    keys.push_back(key);
    return false;
  }
  void Keyboard::isKeyPressed(int key)
  {
    pressedKeys.push_back(key);
    std::cout << key << std::endl;
  
  }
  void Keyboard::isKeyReleased(int key)
  {
    releasedKeys.push_back(key); 
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
 

  
}