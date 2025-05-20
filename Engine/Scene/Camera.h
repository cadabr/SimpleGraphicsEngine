#pragma once

class Camera {
public:
    glm::vec3 getDirection() const { return glm::normalize(-glm::vec3(matrix[2])); }
    glm::vec3 getPosition() const { return matrix[3]; }
    glm::mat4 matrix;
};
