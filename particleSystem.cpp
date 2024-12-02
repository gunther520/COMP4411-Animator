#pragma warning(disable : 4786)

#include "particleSystem.h"
#include "Particle.h"
#include <algorithm> // For std::remove_if
#include "vec.h"
#include <vector>
#include <map>
#include <FL/gl.h> // OpenGL headers
#include <random> // For random number generation

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <limits.h>

 /***************
  * Constructors
  ***************/
ParticleSystem::ParticleSystem()
    : bake_fps(30.0f), bake_start_time(-1), bake_end_time(-1), simulate(false), dirty(false)
{
    // Initialize the particle system
}

/*************
 * Destructor
 *************/
ParticleSystem::~ParticleSystem()
{
    // Clear all stored particles
    clearBaked();
}

/******************
 * Simulation fxns
 ******************/

 /** Start the simulation */
void ParticleSystem::startSimulation(float t)
{
    bake_end_time = -1; // Indicate that the simulation is ongoing
    simulate = true;
    dirty = true;
}

/** Stop the simulation */
void ParticleSystem::stopSimulation(float t)
{
    simulate = false;
    dirty = true;
}

/** Reset the simulation */
void ParticleSystem::resetSimulation(float t)
{
    // Clear particles and reset state variables
    clearBaked();
    simulate = false;
    dirty = true;
}

/** Compute forces and update particles **/
void ParticleSystem::computeForcesAndUpdateParticles(float t)
{
    if (!simulate) return;

    Vec3f gravity(0.0f, 0.0f, -9.8f); // Gravity force
    float deltaTime = 1.0f / bake_fps;
    Vec3f wind (4.0f, 0.0f, 0.0f); // Wind force
    // Update particles
    for (auto& particle : particles) {
        particle.update(deltaTime, gravity); // Apply gravity as the force
        particle.update(deltaTime, wind); // Apply wind as the force
    }

    particles.erase(
        std::remove_if(particles.begin(), particles.end(), [](const Particle& p) {
            return !p.isAlive();
            }),
        particles.end()
    );
}

/** Render particles */
void ParticleSystem::drawParticles(float t)
{
    if (!simulate) return;
    glPushMatrix();
    glColor3b(255, 0, 0);
    glPointSize(10.0);
    glBegin(GL_POINTS);
    for (const auto& particle : particles) {

        Vec3f pos = particle.getPosition();
        glVertex3f(pos[0], pos[1], pos[2]);
    }
    glEnd();
    glPopMatrix();
}

/** Adds the current configuration of particles to
  * your data structure for storing baked particles **/
void ParticleSystem::bakeParticles(float t)
{

    // Store the current particle states
    bakedParticles[t] = particles; // Copy the current particle list
    bake_start_time = (bake_start_time < 0) ? t : min(bake_start_time, t);
    bake_end_time = max(bake_end_time, t);
}

/** Clears out your data structure of baked particles */
void ParticleSystem::clearBaked()
{
    bakedParticles.clear();
}

/** Spawn a particle **/
void ParticleSystem::spawnParticle(const Vec3f& pos , const Vec3f& vel, float size, float lifespan)
{


    // ...

    /** Spawn multiple particles with random positions and velocities **/

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> posDist(-1.0f, 1.0f);
        std::uniform_real_distribution<float> velDist(-0.3f, 0.3f);

        for (int i = 0; i < 5; i++) {
            Vec3f randomPos(pos[0] + posDist(gen), pos[1] + posDist(gen), pos[2] + posDist(gen));
            Vec3f randomVel(vel[0] + velDist(gen), vel[1], vel[2] + velDist(gen));
            particles.push_back(Particle(randomPos, randomVel, size, lifespan));
        }
   
}






