
#include <olivera/olivera.h>

#include "FPSCamera.h"
#include "CameraInputManager.h"
#include "SoundInputManager.h"
#include "BoxInputManager.h"
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

	}
	void onDisplay()
	{

	}

};

int main()
{
	//Engine
  int windowWidth = 1800;
  int windowHeight = 800;
	std::shared_ptr<olivera::Core> engine = olivera::Core::initialise(windowWidth, windowHeight);


  std::shared_ptr<olivera::ShaderProgram> test = std::make_shared<olivera::ShaderProgram>("../resources/shaders/cubeShader.txt");

  engine->getResources()->create<olivera::ShaderProgram>(std::string("cubeShader"), std::string("../resources/shaders/cubeShader.txt"));
  engine->getResources()->create<olivera::ShaderProgram>(std::string("cubeShader1"), std::string("../resources/shaders/cubeShader.txt"));
  engine->getResources()->create<olivera::ShaderProgram>(std::string("texturedCubeShader"), std::string("../resources/shaders/textureCubeShader.txt"));
  engine->getResources()->create<olivera::ShaderProgram>(std::string("postProcessingAcidicShader"), std::string("../resources/shaders/postProcessingShader.txt"));
  engine->getResources()->create<olivera::ShaderProgram>(std::string("postProcessingBlurShader"), std::string("../resources/shaders/framebufferBlurScreen.txt"));
  engine->getResources()->create<olivera::ShaderProgram>(std::string("blinnPhongShader"), std::string("../resources/shaders/Blinn-PhongShader.txt"));



	engine->getResources()->create<olivera::Texture>(std::string("BetterBox"), std::string("../resources/textures/BetterBox.png"));
	engine->getResources()->create<olivera::Texture>(std::string("AwesomeFace"), std::string("../resources/textures/awesomeface.png"));
  
  engine->getResources()->create<olivera::VertexArray>(std::string("TextureCubeMesh"), std::string("../resources/objects/TexturedCube.data"));
  engine->getResources()->create<olivera::VertexArray>(std::string("ColoredCubeMesh"), std::string("../resources/objects/cube.data"));
  engine->getResources()->create<olivera::VertexArray>(std::string("PostProcessingSquare"), std::string("../resources/objects/postProcessingSquare.data"));




  engine->getResources()->create<olivera::Model>(std::string("nanosuit"), std::string("../resources/objects/nanosuit/nanosuit.obj"));
  
  engine->getResources()->create<olivera::Sound>(std::string("Horn"), std::string("../resources/sound/dixie_horn1.ogg"));

 
  
  //Set PostProcessing



	std::vector<std::string> TextureContainer = {"BetterBox", "AwesomeFace"};


  //Camera 1 
	std::shared_ptr<olivera::Entity> cameraEntity = engine->addEntity();
	std::shared_ptr<olivera::Transform> cameraTransform = cameraEntity->addComponent<olivera::Transform>();
	std::shared_ptr<FPSCamera> cameraComponent = cameraEntity->addComponent<FPSCamera>();
	std::shared_ptr<CameraInputManager> cameraInput = cameraEntity->addComponent<CameraInputManager>();
  cameraTransform->setPosition(glm::vec3(0, 0, 0));
  cameraComponent->getCurrentContext()->setViewport(glm::vec4(0, 0, 900, 800));
  cameraComponent->getCurrentContext()->setFrameBuffer(engine, "postProcessingBlurShader", "PostProcessingSquare");

 // Camera 2 
  std::shared_ptr<olivera::Entity> cameraEntity1 = engine->addEntity();
  std::shared_ptr<olivera::Transform> cameraTransform1 = cameraEntity1->addComponent<olivera::Transform>();
  std::shared_ptr<FPSCamera> cameraComponent1 = cameraEntity1->addComponent<FPSCamera>();
  std::shared_ptr<CameraInputManager> cameraInput1 = cameraEntity1->addComponent<CameraInputManager>();
  cameraTransform1->setPosition(glm::vec3(0, 0, 0));
  cameraComponent1->getCurrentContext()->setViewport(glm::vec4(900, 0, 900, 800));
  cameraComponent1->getCurrentContext()->setFrameBuffer(engine, "postProcessingAcidicShader", "PostProcessingSquare");


	//Moving cube
	std::shared_ptr<olivera::Entity> cube = engine->addEntity();
	std::shared_ptr<olivera::Transform> shapeTransform = cube->addComponent<olivera::Transform>();
	std::shared_ptr<olivera::MeshRenderer> mr = cube->addComponent<olivera::MeshRenderer>(TextureContainer, "TextureCubeMesh","texturedCubeShader");
	std::shared_ptr<olivera::Collision> collider = cube->addComponent<olivera::Collision>(true);
  std::shared_ptr<olivera::SoundSource> soundy = cube->addComponent<olivera::SoundSource>("Horn", cameraEntity);
  std::shared_ptr<SoundInputManager> soundyControl = cube->addComponent<SoundInputManager>();
  std::shared_ptr<BoxInputManager> controller = cube->addComponent<BoxInputManager>();
  collider->setScale(glm::vec3(0.5f, 0.5f, 0.5f));


	//LightCube2
	std::shared_ptr<olivera::Entity> cube2 = engine->addEntity();
	std::shared_ptr<olivera::Transform> shapeTransform2 = cube2->addComponent<olivera::Transform>();
  std::shared_ptr<olivera::MeshRenderer> mr1 = cube2->addComponent<olivera::MeshRenderer>(TextureContainer, "ColoredCubeMesh","cubeShader");
	std::shared_ptr<olivera::Collision> collider2 = cube2->addComponent<olivera::Collision>(true);

  shapeTransform2->setPosition(glm::vec3(0.0f, 1.1f, 0.0f));
  collider2->setScale(glm::vec3(1.0f, 1.5f, 1.5f));
  std::cout<<shapeTransform2->getScale().x;

  //LightCube3
  std::shared_ptr<olivera::Entity> cube3 = engine->addEntity();
  std::shared_ptr<olivera::Transform> shapeTransform3 = cube3->addComponent<olivera::Transform>();
  std::shared_ptr<olivera::MeshRenderer> mr2 = cube3->addComponent<olivera::MeshRenderer>(TextureContainer, "ColoredCubeMesh", "cubeShader1");
  std::shared_ptr<olivera::Collision> collider3 = cube3->addComponent<olivera::Collision>(true);
  shapeTransform3->setPosition(glm::vec3(1.0f, 1.1f, 0.0f));
  collider3->setScale(glm::vec3(0.5f, 0.5f, 0.5f));
  std::vector<std::shared_ptr<olivera::Entity>> lightSources;


  lightSources.push_back(cube2);
  lightSources.push_back(cube3);
  //Nanosuit
  std::shared_ptr<olivera::Entity> nanosuit = engine->addEntity();
  std::shared_ptr<olivera::Transform> nanosuitTransform = nanosuit->addComponent<olivera::Transform>();
  std::shared_ptr<olivera::Materials> nanosuitMaterials = nanosuit->addComponent<olivera::Materials>("blinnPhongShader");
  nanosuitMaterials->setDefaultMaterial(32.0f, 0, 1);
  std::shared_ptr<olivera::Light> nanosuitLights = nanosuit->addComponent<olivera::Light>("blinnPhongShader",lightSources);
  std::shared_ptr<olivera::MeshRenderer> nanosuitMesh = nanosuit->addComponent<olivera::MeshRenderer>("nanosuit","blinnPhongShader");


  nanosuitTransform->setPosition(glm::vec3(1.0f, -1.0f, 1.0f));
  nanosuitTransform->setScale(glm::vec3(0.2f, 0.2f, 0.2f));
  


	engine->start();

	return 0;
}