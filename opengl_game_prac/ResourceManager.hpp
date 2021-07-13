//
//  ResourceManager.hpp
//  opengl_game_prac
//
//  Created by hyoukim on 2021/07/09.
//

#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include <map>
#include <string>

#include <glad/glad.h>

#include "Texture.hpp"
#include "Shader.hpp"

using namespace std;

class ResourceManager
{
public:
    // resource storage
    static map<string, Shader>      Shaders;
    static map<string, Texture2D>   Textures;
    // loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code.
    static Shader                   LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, string name);
    // retrieves a stored shader
    static Shader                   &GetShader(string name);
    // loads (and generates) a texture from file
    static Texture2D                LoadTexture(const char *file, bool alpha, string name);
    // retrieves a stored texture
    static Texture2D                &GetTexture(string name);
    // properly de-allocates all loaded resources
    static void                     Clear();
private:
    // private constructor, that is we do not want any actual resource manager objects.
    // Its members and functions should be publicly available(static)
    ResourceManager() { }
    // loads and generates a shader from file
    static Shader                   loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
    // loads a single texture from file
    static Texture2D                loadTextureFromFile(const char *file, bool alpha);
};

#endif /* ResourceManager_hpp */
