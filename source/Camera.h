#pragma once
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL3/SDL.h>

class Camera {
public:
    glm::vec3 position{ 0.f, 0.f, 5.f };
    float yaw{ 0.f };    // around world Y (radians)
    float pitch{ 0.f };  // around local X (radians)

    float moveSpeed{ 200.f };      // WASD units/sec
    float rotateSpeed{ 0.005f };  // rad/pixel
    float panSpeed{ 0.002f };     // scales with distance-to-origin
    float scrollSpeed{ 0.15f };   // fraction of distance-to-origin per tick

    glm::vec3 getForward() const;
    glm::vec3 getRight() const;
    glm::vec3 getUp() const;
    glm::mat4 getViewMatrix() const;

    // Feed each SDL event here
    void processEvent(const SDL_Event& event);
    // Call once per frame for WASD (requires right mouse held)
    void update(float deltaTime);
};
