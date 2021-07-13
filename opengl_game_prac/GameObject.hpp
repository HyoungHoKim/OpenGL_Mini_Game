//
//  GameObject.hpp
//  opengl_game_prac
//
//  Created by hyoukim on 2021/07/11.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Texture.hpp"
#include "SpriteRenderer.hpp"

using namespace glm;

class GameObject
{
protected:
    // object state
    vec2 position;
    vec2 size;
    vec2 velocity;
    vec3 color;
    float rotation;
    bool isSolid;
    bool destroyed;
    // render state
    Texture2D sprite;
public:
    GameObject();
    GameObject(vec2 pos, vec2 size, Texture2D sprite, vec3 color = vec3(1.0f), vec2 velocity = vec2(0.0f, 0.0f));
    
    bool getIsSolid(void) const;
    bool getDestroyed(void) const;
    vec2 getPosition(void) const;
    vec2 getSize(void) const;
    vec2 getVelocity(void) const;
    void setIsSolid(bool _isSolid);
    void setDestoryed(bool _destoryed);
    void setPositionX(float _x);
    void setPositionY(float _y);
    void setVelocityX(float _x);
    void setVelocityY(float _y);
    void setVelocity(vec2 _velocity);
    void setSize(vec2 _size);

    // draw sprite
    virtual void Draw(SpriteRenderer &renderer);
};

#endif /* GameObject_hpp */
