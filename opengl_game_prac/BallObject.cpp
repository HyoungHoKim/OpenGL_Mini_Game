//
//  BallObject.cpp
//  opengl_game_prac
//
//  Created by hyoukim on 2021/07/11.
//

#include "BallObject.hpp"

BallObject::BallObject()
: GameObject(), radius(12.5f), stuck(true), sticky(false), passThrough(false)
{ }

BallObject::BallObject(vec2 pos, float radius, vec2 velocity, Texture2D sprite)
: GameObject(pos, vec2(radius * 2.0f, radius * 2.0f), sprite, vec3(1.0f), velocity), radius(radius), stuck(true),
sticky(false), passThrough(false)
{ }

float BallObject::getRadius(void) const
{
    return (this->radius);
}

bool BallObject::getStuck(void) const
{
    return (this->stuck);
}

void BallObject::setStuck(bool _stuck)
{
    this->stuck = _stuck;
}

bool BallObject::getSticky(void) const
{
    return (this->sticky);
}

void BallObject::setSticky(bool _sticky)
{
    this->sticky = _sticky;
}

bool BallObject::getPassThrough(void) const
{
    return (this->passThrough);
}

void BallObject::setPassThrough(bool _passThrough)
{
    this->passThrough = _passThrough;
}

vec2 BallObject::Move(float dt, unsigned int window_width)
{
    // if not stuck to player board
    if (!this->stuck)
    {
        // move the ball
        this->position += this->velocity * dt;
        // then checkf if outside window bounds and if so, reverse velocity and restore at correct position
        if (this->position.x <= 0.0f)
        {
            this->velocity.x = -this->velocity.x;
            this->position.x = 0.0f;
        }
        else if (this->position.x + this->size.x >= window_width)
        {
            this->velocity.x = -this->velocity.x;
            this->position.x = window_width - this->size.x;
        }
        if (this->position.y <= 0.0f)
        {
            this->velocity.y = -this->velocity.y;
            this->position.y = 0.0f;
        }
    }
    return (this->position);
}

void BallObject::Reset(vec2 position, vec2 velocity)
{
    this->position = position;
    this->velocity = velocity;
    this->stuck = true;
    this->sticky = false;
    this->passThrough = false;
}
