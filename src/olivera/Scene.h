#include <memory>


namespace olivera
{
  class Core;


  class Scene
  {

  public:
    void onInitialise(int _windowWidth, int _windowHeight);




    virtual void sceneSetup();

  protected:
    int windowWidth;
    int windowHeight;

    std::shared_ptr<olivera::Core> engine;
  };

}