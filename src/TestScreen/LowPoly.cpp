#include "LowPoly.h"
#include "FPSCamera.h"
#include "Flashlight.h"
#include "CameraInputManager.h"
#include "SoundInputManager.h"
#include "BoxInputManager.h"
#include <iostream>
#include <string>
#include "GameObject.h"

void LowPoly::sceneSetup()
{
  std::shared_ptr<olivera::Core> engine = olivera::Core::initialise(windowWidth, windowHeight);

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

  //Expermiental Shader
  engine->getResources()->create<olivera::ShaderProgram>(std::string("BetaShadowShader"), std::string("../resources/shaders/Blinn-PhongShadows.txt"));

  //Depth Shader
  engine->getResources()->create<olivera::ShaderProgram>(std::string("depthShader"), std::string("../resources/shaders/DepthShader.txt"));


  /**********************************************************SHADER RESOURCES*************************************************************************/

  //Texture Resources

  engine->getResources()->create<olivera::Texture>(std::string("BetterBox"), std::string("../resources/textures/BetterBox.png"));
  engine->getResources()->create<olivera::Texture>(std::string("AwesomeFace"), std::string("../resources/textures/awesomeface.png"));
  std::vector<std::string> TextureContainer = { "BetterBox", "AwesomeFace" };

  //SkyBox Resource
  engine->getResources()->create<olivera::Texture>(std::string("skyRight"), std::string("../resources/textures/skybox/right.jpg"));
  engine->getResources()->create<olivera::Texture>(std::string("skyLeft"), std::string("../resources/textures/skybox/left.jpg"));
  engine->getResources()->create<olivera::Texture>(std::string("skyTop"), std::string("../resources/textures/skybox/top.jpg"));
  engine->getResources()->create<olivera::Texture>(std::string("skyBottom"), std::string("../resources/textures/skybox/bottom.jpg"));
  engine->getResources()->create<olivera::Texture>(std::string("skyFront"), std::string("../resources/textures/skybox/front.jpg"));
  engine->getResources()->create<olivera::Texture>(std::string("skyBack"), std::string("../resources/textures/skybox/back.jpg "));
  std::vector<std::string> skyboxTextures = { "skyRight", "skyLeft","skyTop","skyBottom","skyFront","skyBack" };
  //Mesh Resources 
  engine->getResources()->create<olivera::VertexArray>(std::string("ColoredCubeMesh"), std::string("../resources/objects/cube.data"));
  engine->getResources()->create<olivera::VertexArray>(std::string("TextureCubeMesh"), std::string("../resources/objects/TexturedCube.data"));




  /**********************************************************MODEL RESOURCES*************************************************************************/

  engine->getResources()->create<olivera::Model>(std::string("Plane"), std::string("../resources/objects/unityAssets/Plane.obj"));
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
  std::shared_ptr<Flashlight> flashlight = cameraEntity->addComponent<Flashlight>();
  cameraTransform->setPosition(glm::vec3(0, 0, 0));
  cameraComponent->getCurrentContext()->setViewport(glm::vec4(0, 0, 900, 800));
  cameraComponent->getCurrentContext()->setFrameBuffer(engine, "postProcessingBlurShader", "PostProcessingSquare");

  // Camera 2 

  std::shared_ptr<olivera::Entity> cameraEntity1 = engine->addEntity();
  std::shared_ptr<olivera::Transform> cameraTransform1 = cameraEntity1->addComponent<olivera::Transform>();
  std::shared_ptr<FPSCamera> cameraComponent1 = cameraEntity1->addComponent<FPSCamera>();
  std::shared_ptr<CameraInputManager> cameraInput1 = cameraEntity1->addComponent<CameraInputManager>();
  std::shared_ptr<Flashlight> flashlight1 = cameraEntity1->addComponent<Flashlight>();
  cameraTransform1->setPosition(glm::vec3(0, 0, 0));
  cameraComponent1->getCurrentContext()->setViewport(glm::vec4(900, 0, 900, 800));
  cameraComponent1->getCurrentContext()->setFrameBuffer(engine, "postProcessingAcidicShader", "PostProcessingSquare");


  //Moving cube
  std::shared_ptr<olivera::Entity> cube = engine->addEntity();
  std::shared_ptr<olivera::Transform> shapeTransform = cube->addComponent<olivera::Transform>();
  std::shared_ptr<olivera::MeshRenderer> mr = cube->addComponent<olivera::MeshRenderer>(TextureContainer, "TextureCubeMesh", "texturedCubeShader");
  std::shared_ptr<olivera::Collision> collider = cube->addComponent<olivera::Collision>(true);
  std::shared_ptr<olivera::SoundSource> soundy = cube->addComponent<olivera::SoundSource>("Horn", cameraEntity);
  std::shared_ptr<SoundInputManager> soundyControl = cube->addComponent<SoundInputManager>();
  std::shared_ptr<BoxInputManager> controller = cube->addComponent<BoxInputManager>();
  collider->setScale(glm::vec3(0.5f, 0.5f, 0.5f));




  //LightCube2
  std::shared_ptr<olivera::Entity> cube2 = engine->addEntity();
  std::shared_ptr<olivera::Transform> shapeTransform2 = cube2->addComponent<olivera::Transform>();
  std::shared_ptr<olivera::MeshRenderer> mr1 = cube2->addComponent<olivera::MeshRenderer>(TextureContainer, "ColoredCubeMesh", "cubeShader1");
  std::shared_ptr<olivera::Collision> collider2 = cube2->addComponent<olivera::Collision>(true);

  shapeTransform2->setPosition(glm::vec3(5.0f, 1.1f, 0.0f));
  collider2->setScale(glm::vec3(0.5f, 0.5f, 0.5f));
  std::cout << shapeTransform2->getScale().x;

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





  /**************************************************************ISLAND DEMO***************************************************************************/


  //Frame
  std::unique_ptr<GameObject> Frame = std::make_unique<GameObject>(engine, "BetaShadowShader", "depthShader", "Plane");
  Frame->addLight(lightSources, cameraEntities);
  Frame->getTransform()->setPosition(glm::vec3(0.0f));
  Frame->getTransform()->setScale(glm::vec3(0.5f));


  //Skybox
  std::shared_ptr<olivera::Entity> skyboxEntity =engine->addEntity();
  std::shared_ptr<olivera::Skybox> skybox = skyboxEntity->addComponent<olivera::Skybox>(skyboxTextures);

  /**************************************************************ROOM DEMO***************************************************************************/
  engine->start();
}
