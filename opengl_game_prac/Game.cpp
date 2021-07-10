//
//  Game.cpp
//  opengl_game_prac
//
//  Created by hyoukim on 2021/07/09.
//

#include "Game.hpp"
#include "ResourceManager.hpp"
#include "SpriteRenderer.hpp"

// Game-related State data
SpriteRenderer *Renderer;

Game::Game(unsigned int _width, unsigned int _height)
: state(GAME_ACTIVE), keys(), width(_width), height(_height)
{
    
}

Game::~Game()
{
    delete Renderer;
}

GameState       Game::getGameState(void) const
{
    return (this->state);
}

// getter and setter
bool            Game::getKeys(int key) const
{
    return (this->keys[key]);
}

unsigned int    Game::getWidth(void) const
{
    return (this->width);
}

unsigned int    Game::getHeight(void) const
{
    return (this->height);
}

void            Game::setKeys(int key, bool isPress)
{
    this->keys[key] = isPress;
}

// initialize game state (load all shaders/textures)
void            Game::Init()
{
    ResourceManager::LoadShader("/Users/hyoukim/Desktop/opengl_game_prac/opengl_game_prac/VertexShader.vertexshader", "/Users/hyoukim/Desktop/opengl_game_prac/opengl_game_prac/FragmentShader.fragmentshader", nullptr, "sprite");
    mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width), static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    Shader shader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(shader);
    //load texture
    ResourceManager::LoadTexture("/Users/hyoukim/Desktop/opengl_game_prac/opengl_game_prac/Textures/awesomeface.png", true, "face");
}
// game loop
void            Game::processInput(float dt)
{
    
}

void            Game::update(float dt)
{
    
}

void            Game::render(void)
{
    Texture2D texture = ResourceManager::GetTexture("face");
    Renderer->DrawSprite(texture, glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
