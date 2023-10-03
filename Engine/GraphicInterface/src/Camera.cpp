#include "Camera.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

Camera::Camera()
{
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    _fov = glm::radians(45.0f);
    _aspectRatio = 1280.0f / 720.0f;
    _near = 0.1f;
    _far = 100.0f;
    //_projectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);
    _projectionMatrix = glm::perspective(_fov, _aspectRatio, _near, _far);
    
    _worldPosition = glm::vec3(0, 0, -10);
    _target = glm::vec3(0, 0, 0);
    _viewMatrix = glm::lookAt(
        _worldPosition,
        _target,
        glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
}

Camera::~Camera()
{
}

void Camera::SetPosition(glm::vec3 position)
{
    _worldPosition = position;
    _viewMatrix = glm::lookAt(
        position,
        _target,
        glm::vec3(0, 1, 0)
    );
}
