//
//  Game.cpp
//  opengl_game_prac
//
//  Created by hyoukim on 2021/07/09.
//

#include "Game.hpp"
#include "ResourceManager.hpp"
#include "SpriteRenderer.hpp"
#include "BallObject.hpp"
#include "ParticleGenerator.hpp"
#include "PostProcessor.hpp"

// Game-related State data
SpriteRenderer      *Renderer;
GameObject          *Player;
BallObject          *Ball;
ParticleGenerator   *Particles;
PostProcessor       *Effects;

float ShakeTime = 0.0f;

// Game-save data
// Serializable   *saveData;

Game::Game(unsigned int _width, unsigned int _height)
: state(GAME_ACTIVE), keys(), width(_width), height(_height)
{
    
}

Game::~Game()
{
    delete Renderer;
    delete Player;
    delete Ball;
    delete Particles;
    delete Effects;
    // delete saveData;
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
    ResourceManager::LoadShader("Shaders/VertexShader.vertexshader", "Shaders/FragmentShader.fragmentshader", nullptr, "sprite");
    ResourceManager::LoadShader("Shaders/ParticleVertexShader.vertexshader", "Shaders/ParticleFragmentShader.fragmentshader", nullptr, "particle");
    ResourceManager::LoadShader("Shaders/PP_VertexShader.vertexshader", "Shaders/PP_FragmentShader.fragmentshader", nullptr, "postprocessing");
    // configure shaders
    mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width), static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    ResourceManager::GetShader("particle").Use().SetInteger("sprite", 0);
    ResourceManager::GetShader("particle").SetMatrix4("projection", projection);
    //load texture
    ResourceManager::LoadTexture("Textures/background.jpeg", false, "background");
    ResourceManager::LoadTexture("Textures/awesomeface.png", true, "face");
    ResourceManager::LoadTexture("Textures/block.png", false, "block");
    ResourceManager::LoadTexture("Textures/block_solid.png", false, "block_solid");
    ResourceManager::LoadTexture("Textures/paddle.png", true, "paddle");
    ResourceManager::LoadTexture("Textures/particle.png", true, "particle");
    ResourceManager::LoadTexture("Textures/powerup_speed.png", true, "powerup_speed");
    ResourceManager::LoadTexture("Textures/powerup_sticky.png", true, "powerup_sticky");
    ResourceManager::LoadTexture("Textures/powerup_increase.png", true, "powerup_increase");
    ResourceManager::LoadTexture("Textures/powerup_confuse.png", true, "powerup_confuse");
    ResourceManager::LoadTexture("Textures/powerup_chaos.png", true, "powerup_chaos");
    ResourceManager::LoadTexture("Textures/powerup_passthrough.png", true, "powerup_passthrough");
    // set render-specific controls
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    Particles = new ParticleGenerator(ResourceManager::GetShader("particle"), ResourceManager::GetTexture("particle"), 500);
    Effects = new PostProcessor(ResourceManager::GetShader("postprocessing"), this->width, this->height);
    // load levels
    GameLevel one; one.Load("Levels/one.lvl", this->width, this->height / 2);
    GameLevel two; two.Load("Levels/two.lvl", this->width, this->height / 2);
    GameLevel three; three.Load("Levels/three.lvl", this->width, this->height / 2);
    GameLevel four; four.Load("Levels/four.lvl", this->width, this->height / 2);
    this->levels.push_back(one);
    this->levels.push_back(two);
    this->levels.push_back(three);
    this->levels.push_back(four);
    this->level = 0;
    // configure game object
    vec2 playerPos = vec2(this->width / 2.0f - PLAYER_SIZE.x / 2.0f, this->height - PLAYER_SIZE.y);
    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
    vec2 ballPos = playerPos + vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);
    Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("face"));
    /*vector<bool> bricks_destroyed;
    for (GameObject &t_brick : this->levels[this->level].getBricks())
        bricks_destroyed.push_back(t_brick.getDestroyed());
    saveData = new Serializable(bricks_destroyed);*/
}
// game loop
void            Game::processInput(float dt)
{
    if (this->state == GAME_ACTIVE)
    {
        float velocity = PLAYER_VELOCITY * dt;
        float playerPosX = Player->getPosition().x;
        if (this->keys[GLFW_KEY_A])
        {
            if (playerPosX >= 0.0f)
            {
                Player->setPositionX(playerPosX - velocity);
                if (Ball->getStuck())
                {
                    float ballPosX = Ball->getPosition().x;
                    Ball->setPositionX(ballPosX - velocity);
                }
            }
        }
        if (this->keys[GLFW_KEY_D])
        {
            if (playerPosX <= this->width - Player->getSize().x)
            {
                Player->setPositionX(playerPosX + velocity);
                if (Ball->getStuck())
                {
                    float ballPosX = Ball->getPosition().x;
                    Ball->setPositionX(ballPosX + velocity);
                }
            }
        }
        /*if (this->keys[GLFW_KEY_P])
        {
            vector<bool> bricks_destroyed;
            for (GameObject t_brick : this->levels[this->level].getBricks())
                bricks_destroyed.push_back(t_brick.getDestroyed());
            saveData->setDestroyed(bricks_destroyed);
            saveFileOut(*saveData);
        }
        if (this->keys[GLFW_KEY_O])
        {
            saveFileIn(*saveData);
            vector<bool> &bricks_destroyed = saveData->getDestroyed();
            int i = 0;
            for (GameObject &g_brick : this->levels[this->level].getBricks())
                g_brick.setDestoryed(bricks_destroyed[i++]);
        }*/
        if (this->keys[GLFW_KEY_SPACE])
            Ball->setStuck(false);
    }
}

void            Game::update(float dt)
{
    // update objects
    Ball->Move(dt, this->width);
    // check for collisions
    this->DoCollisions();
    // update particles
    Particles->Update(dt, *Ball, 2, glm::vec2(Ball->getRadius() / 2.0f));
    // update PowerUps
    this->UpdatePowerUp(dt);
    // reduce shake time
    if (ShakeTime > 0.0f)
    {
        ShakeTime -= dt;
        if (ShakeTime <= 0.0f)
            Effects->shake = false;
    }
    // check loss condition
    if (Ball->getPosition().y >= this->height) // did ball reach bottom edge
    {
        this->ResetLevel();
        this->ResetPlayer();
    }
}

void            Game::render(void)
{
    if (this->state == GAME_ACTIVE)
    {
        // begin rendering to postprocessing framebuffer
        Effects->BeginRender();
            // draw background
            Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->width, this->height), 0.0f);
            // draw level
            this->levels[this->level].Draw(*Renderer);
            // draw player
            Player->Draw(*Renderer);
            // draw PowerUps
            for (PowerUp &powerUp : this->powerUps)
                if (!powerUp.getDestroyed())
                    powerUp.Draw(*Renderer);
            // draw ball
            Ball->Draw(*Renderer);
            // draw particles
            Particles->Draw();
        // end rendering to postprocessing framebuffer
        Effects->EndRender();
        // render postProcessing quad
        Effects->Render(glfwGetTime());
        
    }
}

void Game::ResetLevel()
{
    if (this->level == 0)
        this->levels[0].Load("levels/one.lvl", this->width, this->height / 2);
    else if (this->level == 1)
        this->levels[1].Load("levels/two.lvl", this->width, this->height / 2);
    else if (this->level == 2)
        this->levels[2].Load("levels/three.lvl", this->width, this->height / 2);
    else if (this->level == 3)
        this->levels[3].Load("levels/four.lvl", this->width, this->height / 2);
}

void Game::ResetPlayer()
{
    // reset player/ball stats
    Player->setSize(PLAYER_SIZE);
    Player->setPositionX(this->width / 2.0f - PLAYER_SIZE.x / 2.0f);
    Player->setPositionY(this->height - PLAYER_SIZE.y);
    Ball->Reset(Player->getPosition() + vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -(BALL_RADIUS * 2.0f)), INITIAL_BALL_VELOCITY);
    Effects->chaos = Effects->confuse = false;
    Ball->setSticky(false);
    Ball->setPassThrough(false);
    Player->setColor(vec3(1.0f));
    Ball->setColor(vec3(1.0f));
}

// powerups
bool IsOtherPowerUpActive(vector<PowerUp> &powerups, string type);

void Game::UpdatePowerUp(float dt)
{
    for (PowerUp &powerUp : this->powerUps)
    {
        powerUp.setPositionX(powerUp.getPosition().x + powerUp.getVelocity().x * dt);
        powerUp.setPositionY(powerUp.getPosition().y + powerUp.getVelocity().y * dt);
        if (powerUp.activated)
        {
            powerUp.duration -= dt;
            
            if (powerUp.duration <= 0.0f)
            {
                // remove powerup from list (will later be removed)
                powerUp.activated = false;
                // deactivate effects
                if (powerUp.type == "sticky")
                {
                    if (!IsOtherPowerUpActive(this->powerUps, "sticky"))
                    {
                        // only reset if no other PowerUp of type sticky is active
                        Ball->setSticky(false);
                        Player->setColor(vec3(1.0f));
                    }
                    else if (powerUp.type == "pass-through")
                    {
                        if (!IsOtherPowerUpActive(this->powerUps, "pass-through"))
                        {
                            // only reset if no other PowerUp of type pass-through is active
                            Ball->setPassThrough(false);
                            Ball->setColor(vec3(1.0f));
                        }
                    }
                    else if (powerUp.type == "confuse")
                    {
                        if (!IsOtherPowerUpActive(this->powerUps, "confuse"))
                        {
                            // only reset if no other PowerUp of type confuse is active
                            Effects->confuse = false;
                        }
                    }
                    else if (powerUp.type == "chaos")
                    {
                        if (!IsOtherPowerUpActive(this->powerUps, "chaos"))
                        {
                            // only reset if no other PowerUp of type chaos is active
                            Effects->chaos = false;
                        }
                    }
                }
            }
        }
    }
    
    // Remove all PowerUps from vector that are destoryed AND !activated (thus either off the map or finished)
    // Note we use a lamda expression to remove each PowerUp which is destoryed and not activated
    this->powerUps.erase(remove_if(this->powerUps.begin(), this->powerUps.end(),
                                   [](const PowerUp & powerUp) {return powerUp.getDestroyed() && !powerUp.activated; }
                                   ), this->powerUps.end());
}

bool ShouldSpawn(unsigned int chance)
{
    unsigned int random = rand() % chance;
    return (random == 0);
}

void Game::SpawnPowerUp(GameObject &block)
{
    if (ShouldSpawn(2)) // 1 in 75 chance
        this->powerUps.push_back(PowerUp("speed", vec3(0.5f, 0.5f, 1.0f), 0.0f, block.getPosition(), ResourceManager::GetTexture("powerup_speed")));
    if (ShouldSpawn(2))
        this->powerUps.push_back(PowerUp("sticky", vec3(1.0f, 0.5f, 1.0f), 20.0f, block.getPosition(), ResourceManager::GetTexture("powerup_sticky")));
    if (ShouldSpawn(2))
        this->powerUps.push_back(PowerUp("pass-through", vec3(0.5f, 1.0f, 0.5f), 10.0f, block.getPosition(), ResourceManager::GetTexture("powerup_passthrough")));
    if (ShouldSpawn(2))
        this->powerUps.push_back(PowerUp("pad-size-increase", vec3(1.0f, 0.6f, 0.4f), 0.0f, block.getPosition(),ResourceManager::GetTexture("powerup_increase")));
    if (ShouldSpawn(2))
        this->powerUps.push_back(PowerUp("confuse", vec3(1.0f, 0.3f, 0.3f), 15.0f, block.getPosition(), ResourceManager::GetTexture("powerup_confuse")));
    if (ShouldSpawn(2))
        this->powerUps.push_back(PowerUp("chaos", vec3(0.9f, 0.25f, 0.25f), 15.0f, block.getPosition(), ResourceManager::GetTexture("powerup_chaos")));
}

void ActivePowerUp(PowerUp &powerUp)
{
    if (powerUp.type == "speed")
        Ball->setVelocity(Ball->getVelocity() * 1.2f);
    else if (powerUp.type == "sticky")
    {
        Ball->setSticky(true);
        Player->setColor(vec3(1.0f, 0.5f, 1.0f));
    }
    else if (powerUp.type == "pass-through")
    {
        Ball->setPassThrough(true);
        Ball->setColor(vec3(1.0f, 0.5f, 0.5f));
    }
    else if (powerUp.type == "pad-size-increase")
        Player->setSize(vec2(Player->getSize().x + 50, Player->getSize().y));
    else if (powerUp.type == "confuse")
    {
        if (!Effects->chaos)
            Effects->confuse = true; // only activate if chaos wasn't already active
    }
    else if (powerUp.type == "chaos")
    {
        if (!Effects->confuse)
            Effects->chaos = true;
    }
}

bool IsOtherPowerUpActive(vector<PowerUp> &powerups, string type)
{
    // Check if another PowerUp of the same type is still active
    // in which case we don't disable its effect (yet)
    for (const PowerUp &powerUP : powerups)
    {
        if (powerUP.activated)
            if (powerUP.type == type)
                return (true);
    }
    return (false);
}

// Load & Save
void saveFileOut(Serializable &saveData)
{
    ofstream file("Save/save.dat");
    if (file.is_open())
    {
        cout << "Save!!!" << endl;
        // Text 형식으로 직렬화
        // boost::archive::text_oarchive oa(file);
        // binary 형식으로 직렬화
        boost::archive::binary_oarchive oa(file);
        oa << (const Serializable &) saveData;
        file.close();
    }
}

void saveFileIn(Serializable &saveData)
{
    ifstream file("Save/save.dat");
    if (file.is_open())
    {
        cout << "Load!!!" << endl;
        // Text 형식으로 직렬화
        // boost::archive::text_iarchive ia(file);
        // binary 형식으로 직렬화
        boost::archive::binary_iarchive ia(file);
        ia >> saveData;
        file.close();
    }
}

// collision detection
bool CheckCollision(GameObject &one, GameObject &two); // AABB - AABB collision
Collision CheckCollision(BallObject &one, GameObject &two);
Direction VectorDirection(glm::vec2 target);

void Game::DoCollisions()
{
    for (GameObject &box : this->levels[this->level].getBricks())
    {
        if (!box.getDestroyed())
        {
            Collision collision = CheckCollision(*Ball, box);
            if (get<0>(collision))
            {
                // destroy block if not solid
                if (!box.getIsSolid())
                {
                    box.setDestoryed(true);
                    this->SpawnPowerUp(box);
                }
                // if block is solid, enable shake effect
                ShakeTime = 0.05f;
                Effects->shake = true;
                // collision resoultion
                Direction dir = get<1>(collision);
                vec2 diff_vector = get<2>(collision);
                if (dir == LEFT || dir == RIGHT) // horizontal collision
                {
                    // reverse horizontal velocity
                    Ball->setVelocityX(-(Ball->getVelocity().x));
                    // relocate
                    float penetration = Ball->getRadius() - abs(diff_vector.x);
                    if (dir == LEFT)
                        Ball->setPositionX(Ball->getPosition().x + penetration); // move ball to right
                    else
                        Ball->setPositionX(Ball->getPosition().x - penetration); // move ball to left
                }
                else // vertical collision
                {
                    // reverse vertical velocity
                    Ball->setVelocityY(-(Ball->getVelocity().y));
                    // relocate
                    float penetration = Ball->getRadius() - abs(diff_vector.y);
                    if (dir == UP)
                        Ball->setPositionY(Ball->getPosition().y - penetration); // move ball bback up
                    else
                        Ball->setPositionY(Ball->getPosition().y + penetration); // move ball down
                }
            }
        }
    }
    
    // also check collision on PowerUps and if so, activate them
    for (PowerUp &powerup : this->powerUps)
    {
        if (!powerup.getDestroyed())
        {
            // first check if powerup passed bottom edge, if so: keep as inactive and destory
            if (powerup.getPosition().y >= this->height)
                powerup.setDestoryed(true);
            
            if (CheckCollision(*Player, powerup))
            {
                // collided with player, now activate powerup
                ActivePowerUp(powerup);
                powerup.setDestoryed(true);
                powerup.activated = true;
            }
        }
    }
    // check collision for player pad (unless stuck)
    Collision result = CheckCollision(*Ball, *Player);
    if (!Ball->getStuck() && get<0>(result))
    {
        // check where it hit the board, and change velocity based on where it hit the board
        float centerBoard = Player->getPosition().x + Player->getSize().x / 2.0f;
        float distance = (Ball->getPosition().x + Ball->getRadius()) - centerBoard;
        float percentage = distance / (Player->getSize().x / 2.0f);
        // then move accordingly
        float strength = 2.0f;
        vec2 oldVelocity = Ball->getVelocity();
        Ball->setVelocityX(INITIAL_BALL_VELOCITY.x * percentage * strength);
        // Ball->Velocity.y = -Ball->Velocity.y
        // keep speed consistent over both axes (multiply by length of old velocity, so total strength is not changed)
        Ball->setVelocity(normalize(Ball->getVelocity()) * length(oldVelocity));
        // fix sticky paddle
        Ball->setVelocityY(-1.0f * abs(Ball->getVelocity().y));
        
        // if Sticky powerup is activated, also stick ball to paddle once new velocity vectors were calculate
        Ball->setStuck(Ball->getSticky());
    }
}

bool CheckCollision(GameObject &one, GameObject &two) // AABB - AABB collision
{
    // collision x-axis?
    bool collisionX = one.getPosition().x + one.getSize().x >= two.getPosition().x
    && two.getPosition().x + two.getSize().x >= one.getPosition().x;
    // collision y-axis?
    bool collisionY = one.getPosition().y + one.getSize().y >= two.getPosition().y
    && two.getPosition().y + two.getSize().y >= one.getPosition().y;
    // collision only if on both axes
    return (collisionX && collisionY);
}

Collision CheckCollision(BallObject &one, GameObject &two) // AABB - Circle collision
{
    // get center point circle first
    vec2 center(one.getPosition() + one.getRadius());
    // calculate AABB info (center, half-extents)
    vec2 aabb_half_extents(two.getSize().x / 2.0f, two.getSize().y / 2.0f);
    vec2 aabb_center(two.getPosition().x + aabb_half_extents.x, two.getPosition().y + aabb_half_extents.y);
    // get difference vector between both centers
    vec2 difference = center - aabb_center;
    vec2 clamped = clamp(difference, -aabb_half_extents, aabb_half_extents);
    // add clamped value to AABB_center and we get the value of box closest to circle
    vec2 closest = aabb_center + clamped;
    // retrieve vector between center circle and closet point AABB and check if length <= radius
    difference = closest - center;
    
    // not <= since in that case a collision also occurs when
    // object one exactly touches object two,
    // which they are at the end of each collision resolution stage.
    if (length(difference) < one.getRadius())
        return make_tuple(true, VectorDirection(difference), difference);
    else
        return make_tuple(false, UP, vec2(0.0f));
}

// calculates which direction a vector is facing
Direction VectorDirection(glm::vec2 target)
{
    vec2 compass[] = {
        vec2(0.0f, 1.0f), // up
        vec2(1.0f, 0.0f), // right
        vec2(0.0f, -1.0f), // down
        vec2(-1.0f, 0.0f)
    };
    float max = 0.0f;
    unsigned int best_match = -1;
    for (unsigned int i = 0; i < 4; i++)
    {
        float dot_product = dot(normalize(target), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}
