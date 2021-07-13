//
//  GameLevel.cpp
//  opengl_game_prac
//
//  Created by hyoukim on 2021/07/11.
//

#include "GameLevel.hpp"

#include <fstream>
#include <sstream>

void GameLevel::Load(const char *file, unsigned int levelWidth, unsigned int levelHeight)
{
    // clear old data
    this->bricks.clear();
    // load from file
    unsigned int tileCode;
    GameLevel level;
    string line;
    ifstream fstream(file);
    vector<vector<unsigned int>> tileData;
    
    if(fstream)
    {
        while (getline(fstream, line))
        {
            istringstream sstream(line);
            vector<unsigned int> row;
            while (sstream >> tileCode)
                row.push_back(tileCode);
            tileData.push_back(row);
        }
        if (tileData.size() > 0)
            this->init(tileData, levelWidth, levelHeight);
    }
}

void GameLevel::Draw(SpriteRenderer &renderer)
{
    for (GameObject &tile : this->bricks)
        if (!tile.getDestroyed())
            tile.Draw(renderer);
}

bool GameLevel::isCompleted()
{
    for (GameObject &tile : this->bricks)
        if (!tile.getIsSolid() && !tile.getDestroyed())
            return (false);
    return (true);
}

void GameLevel::init(vector<vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
    // calculate dimensions
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size(); // note we can index vector at [0] since this function is only called if height > 0
    float unit_width = levelWidth / static_cast<float>(width);
    float unit_height = levelHeight / height;
    // initialize level tiles based on tileData
    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            // check block type from level data (2D level array)
            if (tileData[y][x] == 1) // solid
            {
                vec2 pos(unit_width * x, unit_height * y);
                vec2 size(unit_width, unit_height);
                GameObject obj(pos, size, ResourceManager::GetTexture("block_solid"), vec3(0.8f, 0.8f, 0.7f));
                obj.setIsSolid(true);
                this->bricks.push_back(obj);
            }
            else if (tileData[y][x] > 1) // non-solid; now determine its color based on level data
            {
                vec3 color = vec3(1.0f); // original: white
                if (tileData[y][x] == 2)
                    color = vec3(0.2f, 0.6f, 1.0f);
                else if (tileData[y][x] == 3)
                    color = vec3(0.0f, 0.7f, 0.0f);
                else if (tileData[y][x] == 4)
                    color = vec3(0.8f, 0.8f, 0.4f);
                else if (tileData[y][x] == 5)
                    color = vec3(1.0f, 0.5f, 0.0f);
                
                vec2 pos(unit_width * x, unit_height * y);
                vec2 size(unit_width, unit_height);
                this->bricks.push_back(GameObject(pos, size, ResourceManager::GetTexture("block"), color));
            }
        }
    }
}

vector<GameObject> &GameLevel::getBricks(void)
{
    return (this->bricks);
}
