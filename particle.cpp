#include "Particle.h"
#include <FL/gl.h> // OpenGL headers

Particle::Particle(const Vec3f& pos, const Vec3f& vel, float size, float lifespan)
    : position(pos), velocity(vel), size(size), lifespan(lifespan) {}

void Particle::update(float deltaTime, const Vec3f& force) {
    // Apply force to velocity (F = ma; assuming mass = 1 for simplicity)
    velocity += force * deltaTime;

    // Update particle's position using velocity
    position += velocity * deltaTime;

    // Reduce lifespan
    lifespan -= deltaTime;
}

bool Particle::isAlive() const {
    return lifespan > 0.0f;
}


// Accessors
const Vec3f& Particle::getPosition() const {
    return position;
}

const Vec3f& Particle::getVelocity() const {
    return velocity;
}

float Particle::getSize() const {
    return size;
}
