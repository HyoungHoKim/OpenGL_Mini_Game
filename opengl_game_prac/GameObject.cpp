//
//  GameObject.cpp
//  opengl_game_prac
//
//  Created by hyoukim on 2021/07/11.
//

#include "GameObject.hpp"

GameObject::GameObject()
: position(0.0f, 0.0f), size(1.0f, 1.0f), velocity(0.0f), color(1.0f), rotation(0.0f), sprite(), isSolid(false), destroyed(false)
{ }

GameObject::GameObject(vec2 pos, vec2 size, Texture2D sprite, vec3 color, vec2 velocity)
: position(pos), size(size), velocity(velocity), color(color), rotation(0.0f), sprite(sprite), isSolid(false), destroyed(false)
{ }

bool GameObject::getIsSolid(void) const
{
    return (this->isSolid);
}

bool GameObject::getDestroyed(void) const
{
    return (this->destroyed);
}

vec2 GameObject::getPosition(void) const
{
    return (this->position);
}

vec2 GameObject::getSize(void) const
{
    return (this->size);
}

vec2 GameObject::getVelocity(void) const
{
    return (this->velocity);
}

void GameObject::setPositionX(float _x)
{
    this->position.x = _x;
}

void GameObject::setPositionY(float _y)
{
    this->position.y = _y;
}

void GameObject::setVelocityX(float _x)
{
    this->velocity.x = _x;
}

void GameObject::setVelocityY(float _y)
{
    this->velocity.y = _y;
}

void GameObject::setVelocity(vec2 _velocity)
{
    this->velocity = _velocity;
}

void GameObject::setSize(vec2 _size)
{
    this->size = _size;
}

void GameObject::setIsSolid(bool _isSolid)
{
    this->isSolid = _isSolid;
}

void GameObject::setDestoryed(bool _destoryed)
{
    this->destroyed = _destoryed;
}

void GameObject::Draw(SpriteRenderer &renderer)
{
    renderer.DrawSprite(this->sprite, this->position, this->size, this->rotation, this->color);
}
