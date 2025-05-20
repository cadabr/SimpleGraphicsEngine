#pragma once
#include "Scene/Subsystems/Subsystem.h"

class Object;

class RaycastSubsystem : public Subsystem {
public:
    void tick(Scene* scene) override;
    std::shared_ptr<Object> getClosestObject() const;
private:
    std::optional<float> doesRayIntersectSphere(const glm::vec3& sphereCenter, float sphereRadius, const glm::vec3& rayOrigin, const glm::vec3& rayDirection) const;
private:
    std::shared_ptr<Object> closestObject;
};
