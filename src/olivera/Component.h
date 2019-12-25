#ifndef OLIVERA_COMPONENT_H
#define OLIVERA_COMPONENT_H

#include <memory>

namespace olivera
{

  class  Entity;
  class  Core;

  class Component
  {
    friend class Entity;

  public:
    virtual ~Component();
    std::shared_ptr<Entity> getEntity();
    std::shared_ptr<Core> getCore();


  private:
    std::weak_ptr<Entity> entity;
    bool began;

    void onInitialise();
    void onStart();
    void onTick();
    void onDisplay();

  };
}

#endif