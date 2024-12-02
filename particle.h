#ifndef PARTICLE_H
#define PARTICLE_H

#include "vec.h"
#include <FL/gl.h> // OpenGL headers

class Particle {
public:
    // Constructor
    Particle(const Vec3f& pos, const Vec3f& vel, float size, float lifespan = 10.0f);

    // Update particle state
    void update(float deltaTime, const Vec3f& force = Vec3f(0.0f, 0.0f, 0.0f));

    // Check if the particle is alive
    bool isAlive() const;



    // Accessors
    const Vec3f& getPosition() const;
    const Vec3f& getVelocity() const;
    float getSize() const;

private:
    Vec3f position;
    Vec3f velocity;
    float size;
    float lifespan; // Remaining life of the particle
};

#endif // PARTICLE_H
