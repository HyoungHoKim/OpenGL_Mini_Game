//
//  Texture.hpp
//  opengl_game_prac
//
//  Created by hyoukim on 2021/07/09.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <glad/glad.h>

class Texture2D
{
private:
    // holds the ID of the texture object, used for all texture operations to reference to this particlar texture
    unsigned int id;
    // texture image dimensions
    unsigned int width;
    unsigned int height;
    // texture Format
    unsigned int internal_format; // format of texture object
    unsigned int image_format; // format of loaded image
    // texture configuration
    unsigned int wrap_s; // wrapping mode on S axis
    unsigned int wrap_t; // wrapping mode on T axis
    unsigned int filter_min; // filtering mode if texture pixels < screen pixels
    unsigned int filter_max; // filtering mode if texture pixels > screen pixels
    
public:
    Texture2D();
    
    //getter and setter
    unsigned int getId(void) const;
    void setInternalFormat(unsigned int format);
    void setImageFormat(unsigned int format);
    
    // generates texture from image data
    void         Generate(unsigned int width, unsigned int height, unsigned char *data);
    // binds the texture as the current active GL_TEXTURE_2D texture object
    void         Bind() const;
};

#endif /* Texture_hpp */
