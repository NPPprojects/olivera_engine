#include <SDL2/SDL.h>
#include "Component.h"
#include <vector>
#include <map>
namespace olivera 
{
  class Keyboard : public Component
  {

  public:
    void inputDetection(SDL_KeyboardEvent event);
    bool isKey(int key);
    void isKeyPressed(int &key);
    void isKeyReleased(int key);
    void clearKey();
    void OnTick();

  private:
  
    std::vector<int> keys;
    std::vector<int> pressedKeys;
    std::vector<int> releasedKeys;
    
    
  };


}