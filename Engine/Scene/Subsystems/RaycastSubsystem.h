#pragma once
#include "Scene/Subsystems/Subsystem.h"

class Object;

class RaycastSubsystem : public Subsystem {
public:
    RaycastSubsystem(Scene& scene);
    void tick() override;
    void onEvent(std::shared_ptr<Event> event) override;
private:
    std::optional<float> doesRayIntersectSphere(const glm::vec3& sphereCenter, float sphereRadius, const glm::vec3& rayOrigin, const glm::vec3& rayDirection) const;
    std::pair<glm::vec3, glm::vec3> getRay() const;
private:
    std::shared_ptr<Object> closestObject;
};
