//
//  SpriteRenderer.hpp
//  opengl_game_prac
//
//  Created by hyoukim on 2021/07/10.
//

#ifndef SpriteRenderer_hpp
#define SpriteRenderer_hpp

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture.hpp"
#include "Shader.hpp"

using namespace glm;

class SpriteRenderer
{
private:
    // Render state
    Shader          shader;
    unsigned int    quadVAO;
    // Initializes and configures the quad's buffer and vertex attributes
    void initRenderData();
public:
    SpriteRenderer() {}
    SpriteRenderer(Shader &shader);
    ~SpriteRenderer();
    // Renders a defined quad textured with given sprite
    void DrawSprite(Texture2D &texture, vec2 position, vec2 size = vec2(10.0f, 10.0f), float rotate = 0.0f, vec3 color = vec3(1.0f));
};

#endif /* SpriteRenderer_hpp */
