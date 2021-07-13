//
//  BallObject.hpp
//  opengl_game_prac
//
//  Created by hyoukim on 2021/07/11.
//

#ifndef BallObject_hpp
#define BallObject_hpp

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "GameObject.hpp"
#include "Texture.hpp"

using namespace glm;

// BallObject holds the state of the Ball object inheriting
// relevant state data from GameObject. Contain some extra
// functionality specific to Breakout's ball object that
// were too specific for within GameObject alone.
class BallObject : public GameObject
{
private:
    //ball state
    float radius;
    bool stuck;
public:
    BallObject();
    BallObject(vec2 pos, float radius, vec2 velocity, Texture2D sprite);
    
    float getRadius(void) const;
    bool getStuck(void) const;
    void setStuck(bool _stuck);
    
    // moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position
    vec2 Move(float dt, unsigned int window_width);
    // resets the ball to original state with given position and velocity
    void Reset(vec2 position, vec2 velocity);
};

#endif /* BallObject_hpp */
