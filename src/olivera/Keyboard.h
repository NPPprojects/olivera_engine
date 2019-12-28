#include <SDL2/SDL.h>
#include "Component.h"

#include <vector>
#include <memory>
namespace olivera 
{

  class Keyboard :public Component 
  {
  
  public:

    //void inputDetection(SDL_KeyboardEvent event);
    bool isKey(int key);
    void isKeyPressed(int key);
    void isKeyReleased(int key);
    void clearKey();
    void onTick();
    void onInitialise(SDL_Event &event);
    void inputHandler(SDL_Event &event);
    std::vector<int> getKeyPressed();
  private:
  
    std::vector<int> keys;
    std::vector<int> releasedKeys;
    std::vector<int> pressedKeys;

    std::weak_ptr<Keyboard> self;                   //Weak pointer to self refrence 

    SDL_Event event;
  
  };


}