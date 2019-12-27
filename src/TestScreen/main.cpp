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
    std::cout << "onTick" << std::endl;

 //   getCore()->stop();
  }
  void onDisplay()
  {
    //std::cout << "onTick" << std::endl;
  }

};
  int main()
  {
    std::shared_ptr<olivera::Core> engine = olivera::Core::initialise();
    std::shared_ptr<olivera::Entity> entity = engine->addEntity();

    std::shared_ptr<olivera::Sound> sound = std::make_shared<olivera::Sound>();
    sound->load("resources/sound/dixie_horn.ogg");
    sound->play();

    std::shared_ptr<TestScreen> componentColor = entity->addComponent<TestScreen>("Green");
    std::shared_ptr<olivera::MeshRenderer> mr = entity->addComponent<olivera::MeshRenderer>();

    engine->start();

    return 0;
  }
