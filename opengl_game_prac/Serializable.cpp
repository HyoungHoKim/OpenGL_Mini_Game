//
//  Serializable.cpp
//  opengl_game_prac
//
//  Created by hyoukim on 2021/07/13.
//

#include "Serializable.hpp"

Serializable::Serializable(vector<bool> &_destroyed)
: s_destroyed(_destroyed)
{ }

vector<bool> &Serializable::getDestroyed(void)
{
    return (this->s_destroyed);
}

void Serializable::setDestroyed(vector<bool> &_destroyed)
{
    this->s_destroyed = _destroyed;
}

void Serializable::clear_destroyed(void)
{
    this->s_destroyed.clear();
}
