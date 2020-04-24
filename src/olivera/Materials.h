#include <memory>
#include <vector>
#include <string>
#include "Component.h"
namespace olivera
  /********************************************************************
      Need to rework entire class
  *********************************************************************/

{
  class ShaderProgram;
  /*****************************************
  @brief Set up material values for object

  ******************************************/
  class Materials :public Component
  {
  public:
    /***********************
    @brief 

    *
    @param
    ************************/
    void onInitialise(std::string _shader);

  private:

    std::weak_ptr<ShaderProgram> shader;///<weakPointer to lights
  };



}