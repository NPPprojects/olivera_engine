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

  
  void Keyboard::onTick()
  {
    inputHandler(event);

    if(pressedKeys.size()>0)
    {
      if (getKeyPressed().at(0) == SDL_SCANCODE_W)
      {
        std::cout << "Yas";
      }
    }
  }

 
 
  void Keyboard::onInitialise(SDL_Event &_event)
  {
    event = _event;
  }

  void Keyboard::inputHandler(SDL_Event &event)
  {
    switch (event.type)
    {
    case SDL_KEYDOWN:
      isKeyPressed(event.key.keysym.scancode);
      break;
    case SDL_KEYUP:
      isKeyReleased(event.key.keysym.scancode);
      break;
    }
  }

  std::vector<int> Keyboard::getKeyPressed()
  {
    return pressedKeys;
  }
 

  
 
}