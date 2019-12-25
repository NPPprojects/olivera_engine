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

    getCore()->stop();
  }

};
  int main()
  {
    std::shared_ptr<olivera::Core> engine = olivera::Core::initialise();
    std::shared_ptr<olivera::Entity> entity = engine->addEntity();
    std::shared_ptr<TestScreen> componentColor = entity->addComponent<TestScreen>("Green");

    engine->start();

    return 0;
  }
