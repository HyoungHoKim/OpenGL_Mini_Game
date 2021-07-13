//
//  ResourceManager.cpp
//  opengl_game_prac
//
//  Created by hyoukim on 2021/07/09.
//

#include "ResourceManager.hpp"

#include <iostream>
#include <sstream>
#include <fstream>

#include "stb_image.h"

map<string, Texture2D>      ResourceManager::Textures;
map<string, Shader>         ResourceManager::Shaders;

Shader  ResourceManager::LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, string name)
{
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return (Shaders[name]);
}

Shader  &ResourceManager::GetShader(string name)
{
    return (Shaders[name]);
}

Texture2D   ResourceManager::LoadTexture(const char *file, bool alpha, string name)
{
    Textures[name] = loadTextureFromFile(file, alpha);
    return (Textures[name]);
}

Texture2D    &ResourceManager::GetTexture(string name)
{
    return (Textures[name]);
}

void    ResourceManager::Clear()
{
    // (properly) delete all shaders
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.getId());
    for (auto iter : Textures)
    {
        unsigned int id = iter.second.getId();
        glDeleteTextures(1, &id);
    }
}

Shader  ResourceManager::loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile)
{
    // 1. retrieve the vertex/fragment source code from filePath
    string vertexCode;
    string fragmentCode;
    string geometryCode;
    
    try
    {
        // open files
        ifstream vertexShaderFile(vShaderFile);
        ifstream fragmentShaderFile(fShaderFile);
        stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        //convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            ifstream geometryShaderFile(gShaderFile);
            stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (exception e)
    {
        cout << "ERROR::SHADER: Failed to read shader files" << endl;
    }
    
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    const char *gShaderCode = geometryCode.c_str();
    // 2. now create shader object from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return (shader);
}

Texture2D   ResourceManager::loadTextureFromFile(const char *file, bool alpha)
{
    Texture2D texture;
    if (alpha)
    {
        texture.setInternalFormat(GL_RGBA);
        texture.setImageFormat(GL_RGBA);
    }
    // load image
    int width, height, nrChannels;
    unsigned char *data = stbi_load(file, &width, &height, &nrChannels, 0);
    texture.Generate(width, height, data);
    // and finally free image data
    stbi_image_free(data);
    return (texture);
}




