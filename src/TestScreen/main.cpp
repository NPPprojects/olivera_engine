/// TO DO LIST ADD FUCKI Slayin UML Diagram fool


#include <olivera/olivera.h>

#include "FPSCamera.h"
#include "InputManager.h"
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


	engine->getResources()->create<olivera::Texture>(std::string("BetterBox"), std::string("resources/textures/BetterBox.png"));
	engine->getResources()->create<olivera::Texture>(std::string("AwesomeFace"), std::string("resources/textures/awesomeface.png"));
  engine->getResources()->create<olivera::VertexBuffer>(std::string("TextureCubeMesh"), std::string("resources/objects/TexturedCube.data"));
  engine->getResources()->create<olivera::VertexBuffer>(std::string("ColoredCubeMesh"), std::string("resources/objects/cube.data"));
  engine->getResources()->create<olivera::Model>(std::string("nanosuit"), std::string("resources/objects/nanosuit/nanosuit.obj"));
 

	std::vector<std::string> TextureContainer = {"BetterBox","AwesomeFace"};


  // "resources/objects/nanosuit/nanosuit.obj"

	std::shared_ptr<olivera::Entity> cameraEntity = engine->addEntity();
	std::shared_ptr<olivera::Transform> cameraTransform = cameraEntity->addComponent<olivera::Transform>();
	std::shared_ptr<FPSCamera> cameraComponent = cameraEntity->addComponent<FPSCamera>();
	std::shared_ptr<InputManager> cameraInput = cameraEntity->addComponent<InputManager>();


	//Cube
	std::shared_ptr<olivera::Entity> cube = engine->addEntity();
	std::shared_ptr<olivera::Transform> shapeTransform = cube->addComponent<olivera::Transform>();
	std::shared_ptr<olivera::ShaderProgram> cubeShader = cube->addComponent<olivera::ShaderProgram>("resources/shaders/TextureShader.vert", "resources/shaders/TextureShader.frag");
	std::shared_ptr<olivera::MeshRenderer> mr = cube->addComponent<olivera::MeshRenderer>(TextureContainer, "TextureCubeMesh");
	std::shared_ptr<olivera::Collision> collider = cube->addComponent<olivera::Collision>();
	collider->setSize(glm::vec3(1.0f, 1.0f, 1.0f));


	//Cube2
	std::shared_ptr<olivera::Entity> cube2 = engine->addEntity();
	std::shared_ptr<olivera::Transform> shapeTransform2 = cube2->addComponent<olivera::Transform>();
	std::shared_ptr<olivera::ShaderProgram> cubeShader2 = cube2->addComponent<olivera::ShaderProgram>("resources/shaders/cube.vert", "resources/shaders/cube.frag");
  std::shared_ptr<olivera::MeshRenderer> mr1 = cube2->addComponent<olivera::MeshRenderer>(TextureContainer, "ColoredCubeMesh");
	std::shared_ptr<olivera::Collision> collider2 = cube2->addComponent<olivera::Collision>();
	collider2->setSize(glm::vec3(1.0f, 1.0f, 1.0f));

	shapeTransform2->setPosition(glm::vec3(0.0f, 1.1f, 0.0f));

  //Nanosuit
  std::shared_ptr<olivera::Entity> nanosuit = engine->addEntity();
  std::shared_ptr<olivera::Transform> nanosuitTransform = nanosuit->addComponent<olivera::Transform>();
  std::shared_ptr<olivera::ShaderProgram> nanosuitShader = nanosuit->addComponent<olivera::ShaderProgram>("resources/shaders/nanosuit.vert", "resources/shaders/nanosuit.frag");
  std::shared_ptr<olivera::MeshRenderer> nanosuitMesh = nanosuit->addComponent<olivera::MeshRenderer>("nanosuit");
  nanosuitTransform->setPosition(glm::vec3(1.0f, 0.0f, 1.0f));
  nanosuitTransform->setScale(glm::vec3(0.2f, 0.2f, 0.2f));
  
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