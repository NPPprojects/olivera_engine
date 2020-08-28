#include <memory>


namespace olivera
{
  


  class Scene
  {

  public:
    void onInitialise(int _windowWidth, int _windowHeight);




    virtual void sceneSetup();

  protected:
    int windowWidth;
    int windowHeight;


  };

}