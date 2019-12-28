#include "Keyboard.h"
#include <iostream>
namespace olivera
{
  void Keyboard::inputDetection(SDL_KeyboardEvent event)
  {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_RETURN]) {
      printf("<RETURN> is pressed.\n");
    }
    //if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_UP]) {
    //  printf("Right and Up Keys Pressed.\n");
    //}
    if (state[SDL_SCANCODE_ESCAPE]) {
      printf("<RETURN> is pressed.\n");
    }
  }
  bool Keyboard::isKey(int key)
  {
    keys.push_back(key);
    return false;
  }
  void Keyboard::isKeyPressed(int &key)
  {
    pressedKeys.push_back(key);
    std::cout << key << std::endl;
   
  }
  void Keyboard::isKeyReleased(int key)
  {
   // pressedKeys.pop_back();
    releasedKeys.emplace_back(key);
    
  }
  void Keyboard::clearKey()
  {
    pressedKeys.clear();
    releasedKeys.clear();
  }

  void Keyboard::OnTick()
  {

  }

 

  
 
}