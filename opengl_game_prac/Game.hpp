//
//  Game.hpp
//  opengl_game_prac
//
//  Created by hyoukim on 2021/07/09.
//

#ifndef Game_hpp
#define Game_hpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game
{
private:
    GameState       state;
    bool            keys[1024];
    unsigned int    width;
    unsigned int    height;
    
    Game();
public:
    Game(unsigned int _width, unsigned int _height);
    ~Game();
    
    // getter and setter
    GameState       getGameState(void) const;
    bool            getKeys(int key) const;
    unsigned int    getWidth(void) const;
    unsigned int    getHeight(void) const;
    void            setKeys(int key, bool isPress);
    
    // initialize game state (load all shaders/textures)
    void            Init();
    // game loop
    void            processInput(float dt);
    void            update(float dt);
    void            render(void);
};

#endif /* Game_hpp */
