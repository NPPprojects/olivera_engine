
#include <olivera/olivera.h>

#include "FPSCamera.h"
#include "CameraInputManager.h"
#include "SoundInputManager.h"
#include "BoxInputManager.h"
#include <iostream>
#include <string>
#include "GameObject.h"


int main()
{
	//Engine
  int windowWidth = 1800;
  int windowHeight = 800;


  stbi_set_flip_vertically_on_load(false);
	std::shared_ptr<olivera::Core> engine = olivera::Core::initialise(windowWidth, windowHeight);

  std::shared_ptr<olivera::ShaderProgram> test = std::make_shared<olivera::ShaderProgram>("../resources/shaders/cubeShader.txt");


  /**********************************************************SHADER RESOURCES*************************************************************************/

  engine->getResources()->create<olivera::ShaderProgram>(std::string("cubeShader"), std::string("../resources/shaders/cubeShader.txt"));
  engine->getResources()->create<olivera::ShaderProgram>(std::string("cubeShader1"), std::string("../resources/shaders/cubeShader.txt"));
  engine->getResources()->create<olivera::ShaderProgram>(std::string("texturedCubeShader"), std::string("../resources/shaders/textureCubeShader.txt"));
  engine->getResources()->create<olivera::ShaderProgram>(std::string("postProcessingAcidicShader"), std::string("../resources/shaders/postProcessingShader.txt"));
  engine->getResources()->create<olivera::ShaderProgram>(std::string("blinnPhongShader"), std::string("../resources/shaders/Blinn-PhongShader.txt"));
  engine->getResources()->create<olivera::ShaderProgram>(std::string("postProcessingBlurShader"), std::string("../resources/shaders/framebufferBlurScreen.txt"));

  ////ROOM DEMO/////

  //Object Shader
  engine->getResources()->create<olivera::ShaderProgram>(std::string("ShadowShader"), std::string("../resources/shaders/pointLShadows.txt"));

  //Depth Shader
  engine->getResources()->create<olivera::ShaderProgram>(std::string("depthShader"), std::string("../resources/shaders/DepthShader.txt"));


  /**********************************************************SHADER RESOURCES*************************************************************************/

  //Texture Resources

	engine->getResources()->create<olivera::Texture>(std::string("BetterBox"), std::string("../resources/textures/BetterBox.png"));
	engine->getResources()->create<olivera::Texture>(std::string("AwesomeFace"), std::string("../resources/textures/awesomeface.png"));
  std::vector<std::string> TextureContainer = { "BetterBox", "AwesomeFace" };
 
 
  //Mesh Resources 
  engine->getResources()->create<olivera::VertexArray>(std::string("ColoredCubeMesh"), std::string("../resources/objects/cube.data"));
  engine->getResources()->create<olivera::VertexArray>(std::string("TextureCubeMesh"), std::string("../resources/objects/TexturedCube.data"));




  /**********************************************************MODEL RESOURCES*************************************************************************/

  //crate
  engine->getResources()->create<olivera::Model>(std::string("room"), std::string("../resources/objects/Room/Rom.obj"));

  //Nanosuit
  engine->getResources()->create<olivera::Model>(std::string("nanosuit"), std::string("../resources/objects/nanosuit/nanosuit.obj"));
  
  //Table
  engine->getResources()->create<olivera::Model>(std::string("table"), std::string("../resources/objects/obj_mesa/obj_mesa.obj"));
  
  //Mug
  engine->getResources()->create<olivera::Model>(std::string("coffeeMug"), std::string("../resources/objects/coffeeMug/coffeMug1_free_obj.obj"));
  
  //Bed
  //engine->getResources()->create<olivera::Model>(std::string("bed"), std::string("../resources/objects/bed/krovat-2.obj"));

  //Wardrobe
  engine->getResources()->create<olivera::Model>(std::string("wardrobe"), std::string("../resources/objects/wardrobe/Wardrobe  4 door.obj"));
  
  //Samus
  engine->getResources()->create<olivera::Model>(std::string("Samus"), std::string("../resources/objects/Samus/DolSzerosuitR1.obj"));

  //Frida Picture
  engine->getResources()->create<olivera::Model>(std::string("fridaPicture"), std::string("../resources/objects/picture/frida.obj"));

  //Picture Frame
  engine->getResources()->create<olivera::Model>(std::string("pictureFrame"), std::string("../resources/objects/picture/frame.obj"));


  
  
  /**********************************************************MODEL RESOURCES*************************************************************************/
  
  
  /**********************************************************SOUND RESOURCES*************************************************************************/
 
  engine->getResources()->create<olivera::Sound>(std::string("Horn"), std::string("../resources/sound/dixie_horn1.ogg"));

  /**********************************************************SOUND RESOURCES*************************************************************************/

  //Post Processing Resources
  engine->getResources()->create<olivera::VertexArray>(std::string("PostProcessingSquare"), std::string("../resources/objects/postProcessingSquare.data"));


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
  std::shared_ptr<olivera::MeshRenderer> mr1 = cube2->addComponent<olivera::MeshRenderer>(TextureContainer, "ColoredCubeMesh","cubeShader1");
	std::shared_ptr<olivera::Collision> collider2 = cube2->addComponent<olivera::Collision>(true);

  shapeTransform2->setPosition(glm::vec3(5.0f, 1.1f, 0.0f));
  collider2->setScale(glm::vec3(1.0f, 1.5f, 1.5f));
  std::cout<<shapeTransform2->getScale().x;

  //LightCube3
  std::shared_ptr<olivera::Entity> cube3 = engine->addEntity();
  std::shared_ptr<olivera::Transform> shapeTransform3 = cube3->addComponent<olivera::Transform>();
  std::shared_ptr<olivera::MeshRenderer> mr2 = cube3->addComponent<olivera::MeshRenderer>(TextureContainer, "ColoredCubeMesh", "cubeShader");
  std::shared_ptr<olivera::Collision> collider3 = cube3->addComponent<olivera::Collision>(true);
  shapeTransform3->setPosition(glm::vec3(1.0f, 1.1f, 0.0f));
  collider3->setScale(glm::vec3(0.5f, 0.5f, 0.5f));
  std::vector<std::shared_ptr<olivera::Entity>> lightSources;
  std::vector<std::shared_ptr<olivera::Entity>> cameraEntities;

  lightSources.push_back(cube2);
  lightSources.push_back(cube3);

  cameraEntities.push_back(cameraEntity);
  cameraEntities.push_back(cameraEntity1);
  
  ////Nanosuit




  ////NanosuitObject1
  //std::unique_ptr<GameObject> nanosuitObject = std::make_unique<GameObject>(engine, "ShadowShader", "depthShader", "nanosuit");
  //nanosuitObject->addLight(lightSources, cameraEntities);

  //nanosuitObject->getTransform()->setPosition(glm::vec3(3.0f, 0.0f, 1.0f));
  //nanosuitObject->getTransform()->setScale(glm::vec3(0.2f, 0.2f, 0.2f));




  /**************************************************************ROOM DEMO***************************************************************************/
  



  //Table
  std::unique_ptr<GameObject> table = std::make_unique<GameObject>(engine, "ShadowShader","depthShader" ,"table");
  table->addLight(lightSources, cameraEntities);
 
  table->getTransform()->setPosition(glm::vec3(7.5f, 0.0f, 5.0f));
  table->getTransform()->setScale(glm::vec3(4.0f));
  
  
  //Coffee Mug
  std::unique_ptr<GameObject> coffeeMug = std::make_unique<GameObject>(engine, "ShadowShader", "depthShader","coffeeMug");
  coffeeMug->addLight(lightSources, cameraEntities);

  coffeeMug->getTransform()->setPosition(glm::vec3(7.5f, 4.0f, 5.0f));
  coffeeMug->getTransform()->setScale(glm::vec3(0.02f));



  //Samus
  std::unique_ptr<GameObject> samus = std::make_unique<GameObject>(engine, "ShadowShader", "depthShader", "Samus");
  samus->addLight(lightSources, cameraEntities);
  samus->getTransform()->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
  samus->getTransform()->setScale(glm::vec3(0.4f));


  
  //Wardrobe
  std::unique_ptr<GameObject> wardrobe = std::make_unique<GameObject>(engine, "ShadowShader", "depthShader", "wardrobe");
  wardrobe->addLight(lightSources, cameraEntities);
  wardrobe->getTransform()->setPosition(glm::vec3(-5.0f, 0.0f, -10.0f));
  wardrobe->getTransform()->setScale(glm::vec3(4.0f));

  //Frida
  std::unique_ptr<GameObject> fridaPicture = std::make_unique<GameObject>(engine, "ShadowShader", "depthShader", "fridaPicture");
  fridaPicture->addLight(lightSources, cameraEntities);
  fridaPicture->getTransform()->setPosition(glm::vec3(-3.0f, -4.0f, -12.2f));
  fridaPicture->getTransform()->setScale(glm::vec3(7.5f));

  //room
  std::unique_ptr<GameObject> room = std::make_unique<GameObject>(engine, "ShadowShader", "depthShader", "room");
  room->addLight(lightSources, cameraEntities);
  room->getTransform()->setPosition(glm::vec3(0.0f));
  room->getTransform()->setScale(glm::vec3(1.0f));


  //Frame
  std::unique_ptr<GameObject> pictureFrame = std::make_unique<GameObject>(engine, "ShadowShader", "depthShader", "pictureFrame");  
  pictureFrame->addLight(lightSources, cameraEntities);
  pictureFrame->getTransform()->setPosition(glm::vec3(-3.0f, -4.0f, -12.2f));
  pictureFrame->getTransform()->setScale(glm::vec3(7.5f));


  
  
  /**************************************************************ROOM DEMO***************************************************************************/
	engine->start();

	return 0;
}