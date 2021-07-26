//
//  ParticleGenerator.hpp
//  opengl_game_prac
//
//  Created by hyoukim on 2021/07/24.
//

#ifndef ParticleGenerator_hpp
#define ParticleGenerator_hpp

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Texture.hpp"
#include "GameObject.hpp"

// Represents a single particle and its state
struct Particle
{
    vec2 position;
    vec2 velocity;
    vec4 color;
    float life;
    
    Particle() : position(0.0f), velocity(0.0f), color(1.0f), life(0.0f) { }
};

// ParticleGenerator acts as a container for rendering a large number of
// particles by repeatedly spawning and updating particles and killing
// them after a given amount of time.
class ParticleGenerator
{
private:
    // state
    vector<Particle> particles;
    unsigned int amount;
    
    // render state
    Shader shader;
    Texture2D texture;
    unsigned int VAO;
    // initializes buffer and vertex attributes
    void init();
    // returns the first Particle index that's currently unused e.g. life
    // <= 0.0f or 0 if no particle is currently inactive
    unsigned int firstUnusedParticle();
    void respawnParticle(Particle &particle, GameObject &object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));

public:
    ParticleGenerator(Shader shader, Texture2D texture, unsigned int amount);
    // update all particles
    void Update(float dt, GameObject &object, unsigned int newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
    // render all particles
    void Draw();
};

#endif /* ParticleGenerator_hpp */
