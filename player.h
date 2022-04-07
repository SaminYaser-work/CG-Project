#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Player character distance from the right side of the screen
const int x = 80;

// Player character distance from the bottom of the screen
static double w = 250;

GLuint texture_obj = 0;

void drawWheel(float, float, float, float, int);

void drawPlayer()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Body
    glColor3ub(255,126,0);
    glBegin(GL_POLYGON);
        glVertex2i(x,       130 + w);
        glVertex2i(x + 157, 130 + w);
        glVertex2i(x + 157, 400 + w);
        glVertex2i(x,       400 + w);
    glEnd();

    // Wheel
    glColor3ub(36,38,39);
    glLineWidth(5);
    glBegin(GL_LINES);
        glVertex2i(x +  10,       w);
        glVertex2i(x + 147,       w);

        glVertex2i(x + 147,       w);
        glVertex2i(x +  30, 200 + w);

        glVertex2i(x +  30, 200 + w);
        glVertex2i(x +  10,       w);
    glEnd();

    glColor3ub(120,120,120);
    drawWheel(x+41, w + 47, 25, 25*aspectRatio, 360);
    drawWheel(x+41, w + 140, 15, 15*aspectRatio, 360);
    drawWheel(x+100, w + 35, 18, 18*aspectRatio, 360);

    glColor3ub(0, 0, 0);
    glLineWidth(3);
    glBegin(GL_LINES);
        glVertex2i(x + 41, w + 47);
        glVertex2i(x + 100, w + 35);
        glVertex2i(x + 41, w + 47);
        glVertex2i(x + 41, w + 140);
        glVertex2i(x + 41, w + 140);
        glVertex2i(x + 100, w + 35);
    glEnd();

    // Hand
    glColor3ub(255,92,6);
    glBegin(GL_QUADS);
        glVertex2i(x + 20,  300 + w);
        glVertex2i(x + 170, 300 + w);
        glVertex2i(x + 170, 340 + w);
        glVertex2i(x + 20,  340 + w);
    glEnd();

    // Finger
    glColor3ub(120,120,120);
    glLineWidth(5);
    glBegin(GL_LINES);
        glVertex2i(x + 170, 325 + w);
        glVertex2i(x + 190, 325 + w);
    glLineWidth(3);
        glVertex2i(x + 190, 330 + w);
        glVertex2i(x + 200, 300 + w);
    glEnd();

    // Neck
    glColor3ub(120,120,120);
    glBegin(GL_QUADS);
        glVertex2i(x +  60, 400 + w);
        glVertex2i(x +  80, 400 + w);
        glVertex2i(x + 100, 450 + w);
        glVertex2i(x +  80, 450 + w);

        glVertex2i(x + 100, 450 + w);
        glVertex2i(x +  80, 450 + w);
        glVertex2i(x +  60, 500 + w);
        glVertex2i(x +  80, 500 + w);
    glEnd();

    // Head
    glColor3ub(120,120,120);
    glBegin(GL_QUADS);
        glVertex2i(x +  50, 500 + w);
        glVertex2i(x + 100, 500 + w);
        glVertex2i(x + 100, 550 + w);
        glVertex2i(x +  50, 550 + w);

        glVertex2i(x + 100, 470 + w);
        glVertex2i(x + 150, 470 + w);
        glVertex2i(x + 150, 570 + w);
        glVertex2i(x + 100, 570 + w);
    glEnd();
}

void drawWheel(float cx, float cy, float rx, float ry, int num_segments)
{
    float theta = 2 * 3.1415926 / float(num_segments);
    float c = cosf(theta);
    float s = sinf(theta);
    float t;

    float x = 1;
    float y = 0;

    glBegin(GL_POLYGON);
    for(int ii = 0; ii < num_segments; ii++)
    {
        //apply radius and offset
        glVertex2f(x * rx + cx, y * ry + cy);//output vertex

        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}



//void getTexture()
//{
//    //int req_channels = 3;
//    int width = 0, height = 0, channels = 0;
//    stbi_set_flip_vertically_on_load(true);
//    stbi_uc *image = stbi_load( "C:\\Users\\samin\\Documents\\Projects\\Graphics\\2dDino\\img.png", &width, &height, &channels, STBI_rgb_alpha );
//
//    if ( image != nullptr )
//    {
//        glGenTextures(1, &texture_obj);
//        glBindTexture(GL_TEXTURE_2D, texture_obj);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
//        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
//
//        stbi_image_free( image );
//    }
//    else
//    {
//        const char* reason = "[unknown reason]";
//        if (stbi_failure_reason())
//        {
//            reason = stbi_failure_reason();
//        }
//        std::cout << reason << std::endl;
//        std::exit(-1);
//    }
//}
//
//void drawPlayer()
//{
//
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
//    glBindTexture(GL_TEXTURE_2D, texture_obj);
//    glEnable(GL_TEXTURE_2D);
//    glBegin(GL_QUADS);
//
//    glColor4f(1.0, 0.0, 0.0, 1.0);
//    glEnable(GL_ALPHA_TEST);
//    glAlphaFunc(GL_GREATER, 1.0);
////    glClearColor(0.0, 0.0, 0.0, 1.0);
//
//
//        glTexCoord2i(0, 0); glVertex2i(-50 + x, w);
//        glTexCoord2i(0, 1); glVertex2i(-50 + x, 500 + w);
//        glTexCoord2i(1, 1); glVertex2i(157 + x, 500 + w);
//        glTexCoord2i(1, 0); glVertex2i(157 + x, w);
//
//    glEnd();
//    glDisable(GL_BLEND);
//    glDisable(GL_ALPHA_TEST);
//    glDisable(GL_TEXTURE_2D);
//}
//
