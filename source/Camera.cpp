#include "Camera.h"
#include <algorithm>
#include <cmath>

static constexpr float kPitchLimit = 1.553343f; // ~89 degrees

glm::vec3 Camera::getForward() const {
    return {
        std::sin(yaw) * std::cos(pitch),
        -std::sin(pitch),
        -std::cos(yaw) * std::cos(pitch)
    };
}

glm::vec3 Camera::getRight() const {
    return glm::normalize(glm::cross(getForward(), glm::vec3(0.f, 1.f, 0.f)));
}

glm::vec3 Camera::getUp() const {
    return glm::cross(getRight(), getForward());
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + getForward(), getUp());
}

void Camera::processEvent(const SDL_Event& event) {
    if (event.type == SDL_EVENT_MOUSE_MOTION) {
        // Right drag: rotate (look around)
        if (event.motion.state & SDL_BUTTON_RMASK) {
            yaw   += (float)event.motion.xrel * rotateSpeed;
            pitch += (float)event.motion.yrel * rotateSpeed;
            pitch  = std::clamp(pitch, -kPitchLimit, kPitchLimit);
        }
        // Middle drag: pan perpendicular to view
        if (event.motion.state & SDL_BUTTON_MMASK) {
            float dist  = std::max(glm::length(position), 1.0f);
            float scale = dist * panSpeed;
            position -= getRight() * (float)event.motion.xrel * scale;
            position += getUp()    * (float)event.motion.yrel * scale;
        }
    }
    // Scroll: move along forward axis, speed scales with distance
    if (event.type == SDL_EVENT_MOUSE_WHEEL) {
        float dist = std::max(glm::length(position), 0.5f);
        position += getForward() * (float)event.wheel.y * dist * scrollSpeed;
    }
}

void Camera::update(float deltaTime) {
    if (!(SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_RMASK)) return;

    const bool* keys = SDL_GetKeyboardState(nullptr);
    float speed = moveSpeed * deltaTime;
    if (keys[SDL_SCANCODE_W])      position += getForward() * speed;
    if (keys[SDL_SCANCODE_S])      position -= getForward() * speed;
    if (keys[SDL_SCANCODE_A])      position -= getRight()   * speed;
    if (keys[SDL_SCANCODE_D])      position += getRight()   * speed;
    if (keys[SDL_SCANCODE_SPACE])  position += getUp()      * speed;
    if (keys[SDL_SCANCODE_LSHIFT]) position -= getUp()      * speed;
}
