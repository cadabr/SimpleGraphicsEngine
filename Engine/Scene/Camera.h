#pragma once

class Frustum {
public:
    Frustum(float FOV, float aspectRatio, float nearPlane, float farPlane) : FOV(FOV), aspectRatio(aspectRatio), nearPlane(nearPlane), farPlane(farPlane) {}
    float getAspectRatio() const { return aspectRatio; }
    float getFOV() const { return FOV; }
    float getNearPlane() const { return nearPlane; }
    float getFarPlane() const { return farPlane; }
private:
    const float aspectRatio;
    const float FOV;
    const float nearPlane;
    const float farPlane;
};

class Camera {
public:
    Camera(const glm::mat4& worldMatrix, const Frustum& frustum)
    : view(worldMatrix)
    , projection(glm::perspective(glm::radians(frustum.getFOV()), frustum.getAspectRatio(), frustum.getNearPlane(), frustum.getFarPlane())) {
    }
    const glm::mat4& getViewMatrix() const { return view; }
    const glm::mat4& getProjectionMatrix() const { return projection; }
    glm::vec3 getPosition() const { return glm::inverse(view)[3]; }
private:
    glm::mat4 view;
    glm::mat4 projection;
};
