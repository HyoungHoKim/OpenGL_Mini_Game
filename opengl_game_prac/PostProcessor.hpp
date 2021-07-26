//
//  PostProcessor.hpp
//  opengl_game_prac
//
//  Created by hyoukim on 2021/07/26.
//

#ifndef PostProcessor_hpp
#define PostProcessor_hpp

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Texture.hpp"
#include "SpriteRenderer.hpp"
#include "Shader.hpp"

// PostProcessor hosts all PostProcessing effects for the Breakout Game.
// It renders the game on a textured quad after which one can enable specific
// effects  by enabling either the Confuse, Chaos or Shake boolean.
// It is required to call BeginRender()  before rendering the game
// and EndRender() after rendering the game for the class to work.
class PostProcessor
{
private:
    // render state
    unsigned int MSFBO, FBO; // MSFBO = Multisampled FBO, FBO is regular, used for MS color-buffer to texture
    unsigned int RBO; // RBO is used for multisampled color buffer
    unsigned int VAO; //  initailize quad for rendering postprocessing texture
    void initRenderData();
public:
    // state
    Shader PostProcessingShader;
    Texture2D Texture;
    unsigned int width, height;
    // options
    bool confuse, chaos, shake;
    // constructor
    PostProcessor(Shader _shader, unsigned int _witdh, unsigned int _height);
    // prepare the postprocessor's framebuffer operations before rendering the game
    void BeginRender();
    // should be called after rendering the game, so it stores all the rendered data into a texture object
    void EndRender();
    // renders the PostProcessing texture quad (as a screen-encompassing large sprite)
    void Render(float time);
};


#endif /* PostProcessor_hpp */
