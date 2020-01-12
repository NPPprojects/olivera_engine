#include <olivera/olivera.h>

class GameObject
{
public:
	void addShader();
	void addTransform();
	void addModel();
	void addMeshRenderer();

private:
	std::shared_ptr<olivera::Entity> entity;
	std::shared_ptr<olivera::Transform> transform;
	std::shared_ptr<olivera::ShaderProgram> shader;
	std::shared_ptr<olivera::VertexBuffer> shape;
	std::shared_ptr<olivera::MeshRenderer> meshRenderer;
};