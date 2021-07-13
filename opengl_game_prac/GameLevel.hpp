//
//  GameLevel.hpp
//  opengl_game_prac
//
//  Created by hyoukim on 2021/07/11.
//

#ifndef GameLevel_hpp
#define GameLevel_hpp

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "GameObject.hpp"
#include "SpriteRenderer.hpp"
#include "ResourceManager.hpp"

using namespace std;

class GameLevel
{
private:
    // level state
    vector<GameObject> bricks;
    
    void init(vector<vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
public:
    vector<GameObject> &getBricks(void);
    // loads level from file
    void Load(const char *file, unsigned int levelWidth, unsigned int levelHeight);
    // render level
    void Draw(SpriteRenderer &renderer);
    // check if the level is completed (all non-solid tiles are destroyed)
    bool isCompleted();
};

#endif /* GameLevel_hpp */
