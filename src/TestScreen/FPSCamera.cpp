#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "FPSCamera.h"


FPSCamera::FPSCamera()
  {
 
  }


FPSCamera::~FPSCamera()
  {
  }

  glm::mat4 FPSCamera::GetViewMatrix()
  {
    return glm::lookAt(transform.lock()->getPosition(), transform.lock()->getPosition() +  transform.lock()->getFront(), Up);
  }
  void FPSCamera::ProcessKeyboard(CameraMovement _direction, float _deltaTime)
  {
   
    velocity = MovementSpeed * _deltaTime;
    
    if (_direction == LEFTSHIFT)
    {
      MovementSpeed = SPEED*5;
    }
    if (_direction != LEFTSHIFT)
    {
      MovementSpeed = SPEED;
    }
    


    if (_direction == FORWARD)
    {
      transform.lock()->setPosition(transform.lock()->getPosition() + (transform.lock()->getFront() * velocity));
    }
    if (_direction == BACKWARD) 
    {
      transform.lock()->setPosition(transform.lock()->getPosition() - (transform.lock()->getFront() * velocity));
    }
    if (_direction == LEFT)
    {
      transform.lock()->setPosition(transform.lock()->getPosition() - (Right * velocity));
    }
    if (_direction == RIGHT) 
    {
      transform.lock()->setPosition(transform.lock()->getPosition() + (Right * velocity));
    }

    if (_direction == SPACEBAR)
    {
      flashlight = true;
    }
    if (_direction != SPACEBAR)
    {
      flashlight = false;
    }



  }

  std::shared_ptr<olivera::CurrentCamera> FPSCamera::getCurrentContext()
  {
    return cameraContext;
  }

  void FPSCamera::ProcessMouseMovement(float _xoffset, float _yoffset, GLboolean _constrainPitch)
  {
    _xoffset *= MouseSensitivity;
    _yoffset *= MouseSensitivity;

    Yaw += _xoffset;
    Pitch += _yoffset;


    // when pitch is out of bounds, screen doesn't get flipped
    if (_constrainPitch)
    {
      if (Pitch > 89.0f)
        Pitch = 89.0f;
      if (Pitch < -89.0f)
        Pitch = -89.0f;
    }

    // Update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
  }


  void FPSCamera::ProcessMouseScroll(float _yoffset)
  {
    if (Zoom >= 1.0f && Zoom <= 45.0f)
      Zoom -= _yoffset;
    if (Zoom <= 1.0f)
      Zoom = 1.0f;
    if (Zoom >= 45.0f)
      Zoom = 45.0f;
  }
  void FPSCamera::updateCameraVectors()
  {
    // Calculate the new Front vector
    glm::vec3 front;
    
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    transform.lock()->setFront(glm::normalize(front));

    Right = glm::normalize(glm::cross(transform.lock()->getFront(), transform.lock()->getWorldUp()));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, transform.lock()->getFront()));
  }

  float FPSCamera::getZoom() const
  {
    return Zoom;
  }

  glm::vec3 FPSCamera::GetPosition()
  {
	return  transform.lock()->getPosition();
  }

  int FPSCamera::getYaw()
  {
    return Yaw;
  }
  int FPSCamera::getPitch()
  {
    return Pitch;
  }

  void FPSCamera::onInitialise()
  {
  
  entitySelf = getEntity();
  cameraContext = std::make_shared<olivera::CurrentCamera>();
  entitySelf.lock()->getCore()->getCameraList()->addCamera(cameraContext);
	transform = entitySelf.lock()->getComponent<olivera::Transform>();
	transform.lock()->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
  Yaw = YAW;
  Pitch = PITCH;
  MovementSpeed = SPEED;
  MouseSensitivity = SENSITIVITY;
  Zoom = ZOOM;

  }

  void FPSCamera::onTick()
  {
    cameraContext->setProjection(glm::perspective(glm::radians(getZoom()), (float)getCore()->getScreenWidth() / getCore()->getScreenHeight(), 0.1f, 100.0f));
    cameraContext->setView(GetViewMatrix());
  }


  int FPSCamera::getFlashlight()
  {
    return flashlight;
  }