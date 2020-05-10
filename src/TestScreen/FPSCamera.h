#include "glm/glm.hpp"
#include <GL/glew.h>
#include <olivera/olivera.h>

//First Person Camera that will be used to test the engine 

  class FPSCamera : public olivera::Component
  {
	
  public:
    enum CameraMovement {
      FORWARD,
      BACKWARD,
      LEFT,
      RIGHT
    };
    void updateCameraVectors();

    FPSCamera();
    ~FPSCamera();

    void ProcessMouseScroll(float _yoffset);
    void ProcessMouseMovement(float _xoffset, float _yoffset, GLboolean _constrainPitch = true);
    void ProcessKeyboard(CameraMovement _direction, float _deltaTim);
    std::shared_ptr<olivera::CurrentCamera> getCurrentContext();
    glm::mat4 GetViewMatrix();
    float getZoom() const;
    glm::vec3 GetPosition();
    int getYaw();
    int getPitch();
    void onInitialise();

    void onTick();
  private:
    // Camera Attributes
    glm::vec3 Up;
    glm::vec3 Right;
    // Euler Angles
    float Yaw;
    float Pitch;
    // Camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    float YAW = -90.0f;
    float PITCH = 0.0f;
    float SPEED = 2.5f;
    float SENSITIVITY = 0.1f;
    float ZOOM = 45.0f;

    glm::mat4 projection;   
   
    std::shared_ptr<olivera::CurrentCamera> cameraContext;
	
	  std::weak_ptr<olivera::Core> core;
	  std::weak_ptr<olivera::Transform> transform;
	  std::weak_ptr<olivera::Entity> entitySelf;
  };

