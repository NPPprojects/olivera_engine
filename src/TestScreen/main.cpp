#include <olivera/olivera.h>

#include <iostream>
#include <string>

class TestScreen : public olivera::Component
{
public:

  void onInitialise(std::string color)
  {
    std::cout << "onInitialise " << color << std::endl;
  }

  void onStart()
  {
    std::cout << "onStart" << std::endl;
  }

  void onTick()
  {
 //   std::cout << "onTick" << std::endl;

 // getCore()->stop();
  }
  void onDisplay()
  {
    //std::cout << "onTick" << std::endl;
  }

};

  int main()
  {
    SDL_Event event = { 0 };
    std::shared_ptr<olivera::Core> engine = olivera::Core::initialise();
    std::shared_ptr<olivera::Entity> entity = engine->addEntity();

    std::shared_ptr<TestScreen> componentColor = entity->addComponent<TestScreen>("Green");
    std::shared_ptr<olivera::Texture> smiley = entity->addComponent<olivera::Texture>("resources/textures/awesomeface.png");
    std::shared_ptr<olivera::MeshRenderer> mr = entity->addComponent<olivera::MeshRenderer>();
    std::shared_ptr<olivera::Keyboard> keyboard = entity->addComponent<olivera::Keyboard>(event);



    engine->start(event);

    return 0;
  }
