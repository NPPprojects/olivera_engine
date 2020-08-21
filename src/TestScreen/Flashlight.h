#include <olivera/olivera.h>




class Flashlight : public olivera::Component
{

public:
  void onInitialise();

  void onTick();

  void AddToList(std::shared_ptr<olivera::Entity> _entitiy);
private:

  std::vector<std::shared_ptr<olivera::Entity>> gameObjects;

};