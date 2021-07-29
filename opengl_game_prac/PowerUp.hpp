//
//  PowerUp.h
//  opengl_game_prac
//
//  Created by hyoukim on 2021/07/29.
//

#ifndef PowerUp_hpp
#define PowerUp_hpp

#include <string>

#include "GameObject.hpp"

using namespace std;

const vec2 SIZE(60.0f, 20.0f);
const vec2 VELOCITY(0.0f, 150.0f);

class PowerUp : public GameObject
{
public:
    string type;
    float duration;
    bool activated;
    
    PowerUp(string _type, vec3 _color, float _duration, vec2 _position, Texture2D _texture)
    : GameObject(_position, SIZE, _texture, _color, VELOCITY), type(_type), duration(_duration), activated(false)
    { }
};

#endif /* PowerUp_hpp */
