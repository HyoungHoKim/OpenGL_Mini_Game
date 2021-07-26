//
//  PostProcessor.cpp
//  opengl_game_prac
//
//  Created by hyoukim on 2021/07/26.
//

#include "PostProcessor.hpp"

#include <iostream>

PostProcessor::PostProcessor(Shader _shader, unsigned int _width, unsigned int _heigth)
: PostProcessingShader(_shader), Texture(), width(_width * 2), height(_heigth * 2), confuse(false), chaos(false), shake(false)
{
    // initialize renderbuffer/framebuffer object
    glGenFramebuffers(1, &this->MSFBO);
    glGenFramebuffers(1, &this->FBO);
    glGenRenderbuffers(1, &this->RBO);
    // initialize renderbuffer storage with a multisampled color buffer (don't need a depth/stencil buffer)
    glBindFramebuffer(GL_FRAMEBUFFER, this->MSFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, this->RBO);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGB, this->width, this->height); // allocate storage for render buffer object
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, this->RBO); // attach MS render buffer object to framebuffer
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::POSTPROCESSOR: Failed to initialize MSFBO" << std::endl;
    // also  initialize the FBO/texture to blit multisampled color-buffer to; used for shader operation (for postprocessing effects)
    glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);
    this->Texture.Generate(this->width, this->height, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->Texture.getId(), 0); // attach texture to framebuffer as its color attachment
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR:POSTPROCESSOR: Failed to initialize FBO" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // initialize render data and uniforms
    this->initRenderData();
    this->PostProcessingShader.SetInteger("scene", 0, true);
    float offset = 1.0f / 300.0f;
    float offsets[9][2] = {
        { -offset, offset  }, // top-left
        { 0.0f,    offset  }, // top-center
        { offset,  offset  }, // top-right
        { -offset, 0.0f    }, // center-left
        { 0.0f,    0.0f    }, // center-center
        { offset,  0.0f    }, // center-right
        { -offset, -offset }, // bottom-left
        { 0.0f,    -offset }, // bottom-center
        { offset,  -offset }  // bottom-right
    };
    glUniform2fv(glGetUniformLocation(this->PostProcessingShader.getId(), "offsets"), 9, (float*)offsets);
    int edge_kernel[9] = {
        -1, -1, -1,
        -1,  8, -1,
        -1, -1, -1
    };
    glUniform1iv(glGetUniformLocation(this->PostProcessingShader.getId(), "edge_kernel"), 9, edge_kernel);
    float blur_kernel[9] = {
        1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
        2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f,
        1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f
    };
    glUniform1fv(glGetUniformLocation(this->PostProcessingShader.getId(), "blur_kernel"), 9, blur_kernel);
}

void PostProcessor::BeginRender()
{
    glBindFramebuffer(GL_FRAMEBUFFER, this->MSFBO);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void PostProcessor::EndRender()
{
    // now resolve multisampled color-buffer into intermediate FBO to store to texture
    glBindFramebuffer(GL_READ_FRAMEBUFFER, this->MSFBO);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->FBO);
    glBlitFramebuffer(0, 0,  this->width, this->height, 0, 0, this->width, this->height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // binds both READ and WRITE framebuffer to default framebuffer
}

void PostProcessor::Render(float time)
{
    // set uniform/options
    this->PostProcessingShader.Use();
    this->PostProcessingShader.SetFloat("time", time);
    this->PostProcessingShader.SetFloat("confuse", this->confuse);
    this->PostProcessingShader.SetInteger("chaos", this->chaos);
    this->PostProcessingShader.SetInteger("shake", this->shake);
    // render texture quad
    glActiveTexture(GL_TEXTURE0);
    this->Texture.Bind();
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void PostProcessor::initRenderData()
{
    // configure VAO/VBO
    unsigned int VBO;
    float vertices[] = {
        // pos        // tex
        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,

        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f
    };
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);
    
    glBindBuffer(GL_ARRAY_BUFFER,  VBO);
    glBufferData(GL_ARRAY_BUFFER,  sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindVertexArray(this->VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
