//
//  Shader.hpp
//  opengl_game_prac
//
//  Created by hyoukim on 2021/07/09.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <string>
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

class Shader
{
private:
    // state
    unsigned int    id;
private:
    void            CheckCompileErrors(unsigned int object, string type);
public:
    Shader() { }
    // sets the current shader as active
    Shader          &Use();
    
    // getter
    unsigned int    getId(void) const;
    // compiles the shader from given source code
    void            Compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource = nullptr);
    // utility functions
    void            SetFloat(const char *name, float value, bool useShader = false);
    void            SetInteger(const char *name, int value, bool useShader = false);
    void            SetVector2f(const char *name, float x, float y, bool useShader = false);
    void            SetVector2f(const char *name, const vec2 &value, bool useShader = false);
    void            SetVector3f(const char *name, float x, float y, float z, bool useShader = false);
    void            SetVector3f(const char *name, const vec3 &value, bool useShader = false);
    void            SetVector4f (const char *name, float x, float y, float z, float w, bool useShader = false);
    void            SetVector4f (const char *name, const vec4 &value, bool useShader = false);
    void            SetMatrix4  (const char *name, const mat4 &matrix, bool useShader = false);
};

#endif /* Shader_hpp */
