#include "pch.h"
#include "Scene/Events/All.h"
#include "Scene/Subsystems/EventProcessingSubsystem.h"
#include "Scene/Subsystems/RaycastSubsystem.h"
#include "Scene/Scene.h"

using glm::dot;
using glm::inverse;
using glm::normalize;
using glm::vec3;
using glm::vec4;
using std::make_shared;
using std::nullopt;
using std::numeric_limits;
using std::optional;
using std::pair;
using std::shared_ptr;
using std::sqrt;

RaycastSubsystem::RaycastSubsystem(Scene& scene)
:Subsystem(scene) {
    scene.getSubsystem<EventProcessingSubsystem>()->subscribe(this);
}

void RaycastSubsystem::tick() {
    const auto& [rayOrigin, rayDirection] = getRay();
    float closestDistance = numeric_limits<float>::max();
    closestObject.reset();

    auto [beginSolid, endSolid] = scene.rangeForComponent<ComponentType::Collision>();
    for (auto it = beginSolid; it != endSolid; ++it) {
        const vec3& sphereCenter = (*it)->getComponent<TransformComponent>()->matrix[3];
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

pair<vec3, vec3> RaycastSubsystem::getRay() const {
    const MousePosition& mousePosition = scene.getMouse().position;
    vec4 rayClip = vec4(mousePosition.getNdcWidth(), mousePosition.getNdcHeight(), -1.0f, 1.0f);
    vec4 rayEye = inverse(scene.getCamera()->getProjectionMatrix()) * rayClip;
    rayEye = vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);

    vec3 rayDirection = normalize(vec3(inverse(scene.getCamera()->getViewMatrix()) * rayEye));
    const vec3& raySource = scene.getCamera()->getPosition();
    return pair<vec3, vec3>(raySource, rayDirection);
}

void RaycastSubsystem::onEvent(shared_ptr<Event> event) {
    if(auto btnPressed = dynamic_cast<MouseButtonPressed*>(event.get()); btnPressed && closestObject) {
        auto rayHitObject = make_shared<RayHitObject>(closestObject);
        scene.getSubsystem<EventProcessingSubsystem>()->pushEvent(rayHitObject);
    }
}
