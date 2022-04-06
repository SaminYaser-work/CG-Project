#ifndef LOADIMAGE_H_INCLUDED
#define LOADIMAGE_H_INCLUDED

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint loadImage()
{
    const char *filename = "image.bmp"; // path and filename
    int         req_channels = 3; // 3 color channels of BMP-file

    int width = 0, height = 0, channels = 0;
    stbi_uc *image = stbi_load( filename, &width, &height, &channels, 3 );

    GLuint texture_obj = 0;
    if ( image != nullptr )
    {
        glGenTextures(1, &texture_obj);
        glBindTexture(GL_TEXTURE_2D, texture_obj);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // default

        stbi_image_free( image );
    }

    return texture_obj;

}

GLuint LoadTexture(GLuint tex, const char * filename, int width, int height)
{
//bmp 24 bit
    unsigned char * data;
    unsigned char R,G,B;
    FILE * file;

//open .bmp
    file = fopen(filename, "rb");

    if(file == NULL)return 0;
//get memory for data
    data =(unsigned char *)malloc(width * height * 3);
//data skip offset
    fseek(file,128,0);
//read file to data
    fread(data, width * height * 3, 1, file);
//close file
    fclose(file);

//transpose R,G,B values
    int index;
    for(int i = 0; i < width * height ; ++i)
    {
        index = i*3;
        B = data[index];
        G = data[index+1];
        R = data[index+2];
        data[index] = R;
        data[index+1] = G;
        data[index+2] = B;
    }

//create a texture
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data);

//texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

//free memory
    free(data);
    return 0;
}



#endif // LOADIMAGE_H_INCLUDED
