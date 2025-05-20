#include "pch.h"
#include "Scene/Subsystems/RaycastSubsystem.h"
#include "Scene/Scene.h"

using glm::dot;
using glm::vec3;
using std::nullopt;
using std::numeric_limits;
using std::optional;
using std::shared_ptr;
using std::sqrt;

void RaycastSubsystem::tick(Scene* scene) {
    const vec3& rayOrigin = scene->getCamera().getPosition();
    const vec3& rayDirection = scene->getCamera().getDirection();
    float closestDistance = numeric_limits<float>::max();
    closestObject.reset();

    auto [beginSolid, endSolid] = scene->rangeForComponent<ComponentType::Collision>();
    for (auto it = beginSolid; it != endSolid; ++it) {
        const auto& sphereCenter = (*it)->getComponent<TransformComponent>()->matrix[3];
        float sphereRadius = (*it)->getComponent<CollisionComponent>()->shpereRadius;

        if (float distance = doesRayIntersectSphere(sphereCenter, sphereRadius, rayOrigin, rayDirection).value_or(numeric_limits<float>::max());
            distance < closestDistance) {
            closestDistance = distance;
            closestObject = *it;
        }
    }
}

optional<float> RaycastSubsystem::doesRayIntersectSphere(const vec3 &sphereCenter, float sphereRadius, const vec3 &rayOrigin, const vec3 &rayDirection) const
{
    vec3 oc = rayOrigin - sphereCenter;
    float a = dot(rayDirection, rayDirection);
    float b = 2.0f * dot(oc, rayDirection);
    float c = dot(oc, oc) - sphereRadius * sphereRadius;

    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return nullopt;
    }

    // Вычисляем ближайшую точку пересечения
    float distance = (-b - sqrt(discriminant)) / (2.0f * a);
    if (distance < 0) {
        // Если ближайшая точка позади луча, проверяем вторую точку
        distance = (-b + sqrt(discriminant)) / (2.0f * a);
        if (distance < 0) {
            return nullopt; // Обе точки пересечения позади луча
        }
    }
    return distance;
}
