
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
  //Engine
  std::shared_ptr<olivera::Core> engine = olivera::Core::initialise();
  std::shared_ptr<olivera::Entity> square = engine->addEntity();

  
  

  //Camera
  
  std::shared_ptr<olivera::Entity> cameraEntity = engine->addEntity();
  std::shared_ptr<olivera::Camera> cameraComponent = cameraEntity->addComponent<olivera::Camera>();
  std::shared_ptr<olivera::InputManager> cameraInput = cameraEntity->addComponent<olivera::InputManager>();

  

  //Cube
  
  std::shared_ptr<olivera::Entity> cube = engine->addEntity();
  std::shared_ptr<olivera::ShaderProgram> cubeShader = cube->addComponent<olivera::ShaderProgram>("resources/shaders/cube.vert", "resources/shaders/cube.frag");
  std::shared_ptr<olivera::VertexBuffer> shape = cube->addComponent<olivera::VertexBuffer>("resources/objects/cube.data");
  std::shared_ptr<olivera::MeshRenderer> mr = cube->addComponent<olivera::MeshRenderer>(cameraEntity);
  
  //Square
 /*std::shared_ptr<olivera::Entity> square = engine->addEntity();
 std::shared_ptr<olivera::Texture> smiley = cube->addComponent<olivera::Texture>("resources/textures/awesomeface.png");
  std::shared_ptr<olivera::ShaderProgram> triangleShader = square->addComponent<olivera::ShaderProgram>("resources/shaders/simple.vert", "resources/shaders/simple.frag");
  std::shared_ptr<olivera::VertexBuffer> shape1 = square->addComponent<olivera::VertexBuffer>("resources/objects/triangle.data");
  std::shared_ptr<olivera::MeshRenderer> mr1 = square->addComponent<olivera::MeshRenderer>(cameraEntity);*/
  //std::shared_ptr<olivera::MeshRenderer> mr1 = square->addComponent<olivera::MeshRenderer>(cameraEntity);
  

  engine->start();

  return 0;
}