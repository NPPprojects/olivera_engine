#include <memory>
#include <vector>

namespace olivera
{
  class Entity;

  class Core
  {

  public:
    static std::shared_ptr<Core> initialise();    //Initialisation function that will add all entities to the tick rate and display them
    std::shared_ptr<Entity> addEntity();      //Adds an entity to the entity vector

    void start();             
    void stop();

  private:

    std::vector<std::shared_ptr<Entity>> entities;      //Vector of all entities
    std::weak_ptr<Core> self;                   //Weak pointer to self refrence 
    bool running;
  };
}
