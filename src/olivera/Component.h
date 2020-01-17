#ifndef OLIVERA_COMPONENT_H
#define OLIVERA_COMPONENT_H

#include <memory>

namespace olivera
{
  class  Entity;
  class  Core;

  /**
  *Base class to add components to entities
  */
  class Component
  {
    friend class Entity;

  public:
    /**
    *\virtual deconstructor for derived classes
    */
    virtual ~Component();

    /**
    *\Getter for entity
    */
    std::shared_ptr<Entity> getEntity();
    /**
    *\Getter for core
    */
    std::shared_ptr<Core> getCore();


  private:
	
    std::weak_ptr<Entity> entity; ///refrence to entity component belongs to
    bool began;///< boolean to begin

    /**
    *\Virtual function for components initilastion(constructor for components)
    */
   virtual void onInitialise();
   /**
   *\Virtual function for on Start Function
   */
   virtual void onStart();

   /**
  *\Virtual function that gets called every tick call
  */
   virtual void onTick();

   /**
  *\Virtual function that gets called every display call
  */
   virtual void onDisplay();

  };
}

#endif