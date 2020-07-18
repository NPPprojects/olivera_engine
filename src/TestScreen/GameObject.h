#include <olivera/olivera.h>

class GameObject
{
public:

  GameObject(std::shared_ptr<olivera::Core> &_scene, std::string _shader, std::string _model);

  void addLight(std::vector<std::shared_ptr<olivera::Entity>> &_lightSources);
  
  void addMaterial();

  std::shared_ptr<olivera::Transform> getTransform();

private:
	std::shared_ptr<olivera::Entity> self;
	std::shared_ptr<olivera::Transform> transform;
  std::string shaderName;
	std::shared_ptr<olivera::MeshRenderer> meshRenderer;
  std::shared_ptr<olivera::Materials> material;
  std::shared_ptr<olivera::Light> lightSources;
  std::shared_ptr<olivera::ShaderProgram> shaderProgram;

  std::shared_ptr<olivera::ResourceManager> objectResouces = std::make_shared<olivera::ResourceManager>();

};