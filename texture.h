#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#define GL_CLAMP_TO_EDGE 0x812F
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// For loading textures
GLuint getTexture(const char* filePath)
{
    //int req_channels = 3;
    GLuint texture_obj = 0;
    int width = 0, height = 0, channels = 0;
    stbi_set_flip_vertically_on_load(true);
    stbi_uc *image = stbi_load( filePath, &width, &height, &channels, STBI_rgb );

    if ( image != nullptr )
    {
        glGenTextures(1, &texture_obj);
        glBindTexture(GL_TEXTURE_2D, texture_obj);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

        stbi_image_free( image );
    }
    else
    {
        const char* reason = "[unknown reason]";
        if (stbi_failure_reason())
        {
            reason = stbi_failure_reason();
        }
        std::cout << reason << std::endl;
        std::cout << filePath << std::endl;
        std::exit(-1);
    }

    return texture_obj;
}

void displayTexture(const char* filePath ,int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{

//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLuint texture_obj = getTexture(filePath);
    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texture_obj);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor4f(1.0, 0.0, 0.0, 1.0);

        glTexCoord2i(0, 0); glVertex2i(x1, y1);
        glTexCoord2i(1, 0); glVertex2i(x2, y2);
        glTexCoord2i(1, 1); glVertex2i(x3, y3);
        glTexCoord2i(0, 1); glVertex2i(x4, y4);

    glEnd();
//    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glDeleteTextures(1, &texture_obj);
}


#endif // TEXTURE_H_INCLUDED
