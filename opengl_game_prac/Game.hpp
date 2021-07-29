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

// Save : boost::serialization
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include "GameLevel.hpp"
#include "GameObject.hpp"
#include "PowerUp.hpp"
#include "Serializable.hpp"

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

// Represents the four possible (collision) direction
enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};
// Define a Collision typedef that represents collision data
typedef tuple<bool, Direction, vec2> Collision;

// Initial size of the player paddle
const vec2 PLAYER_SIZE(100.0f, 20.0f);
// Initial velocity of the player paddle
const float PLAYER_VELOCITY(500.0f);
// Initial velocity of the Ball
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// Radius of the ball object
const float BALL_RADIUS = 12.5f;

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability
class Game
{
private:
    // game state
    GameState           state;
    bool                keys[1024];
    unsigned int        width;
    unsigned int        height;
    vector<GameLevel>   levels;
    vector<PowerUp>     powerUps;
    unsigned int        level;
    
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
    void            DoCollisions(void);
    // reset
    void            ResetLevel();
    void            ResetPlayer();
    // powerups
    void            SpawnPowerUp(GameObject &block);
    void            UpdatePowerUp(float dt);
};

void saveFileOut(Serializable &saveData);
void saveFileIn(Serializable &saveData);

#endif /* Game_hpp */
