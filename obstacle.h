#ifndef OBSTACLE_H_INCLUDED
#define OBSTACLE_H_INCLUDED

#include "variables.h"
#include "texture.h"

void draw_circle(double theta, double inner_radius, double outer_radius, int x, int y, int sin_sign = 1, int cos_sign = 1)
{
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0);
    for(double r = outer_radius; r >= inner_radius; r -= 3.0)
    {
        for(double i = 0; i < theta ; i++)
        {
            double degInRad = i * DEG2RAD;
            glVertex2f( cos_sign * cos(degInRad) * r + x, sin_sign * sin(degInRad) * r + y  );
        }
    }
    glEnd();
}

//void generate_tree(int x_, double len)
//{
//    int x = 30;
//    glColor3f(1.0, 1.0, 1.0);
//    glBegin(GL_POLYGON);
//    glVertex2f(x_, 250 * len);
//    glVertex2f(x_ + x, 250 * len);
//    glVertex2f(x_ + x, 650 * len);
//    glVertex2f(x_, 650 * len);
//    glEnd();
//
//    draw_circle(180.0, 0.0, x / 2, x_ + x / 2, 650 * len);
//
//    glColor3f(1.0, 1.0, 1.0);
//    glBegin(GL_POLYGON);
//    glVertex2f(x_ + x + 25, 400 * len);
//    glVertex2f(x_ + x + 50, 400 * len);
//    glVertex2f(x_ + x + 50, 600 * len);
//    glVertex2f(x_ + x + 25, 600 * len);
//    glEnd();
//
//    draw_circle(180.0, 0.0, 25.0 / 2, x_ + x + 75.0 / 2, 600 * len);
//
//    glColor3f(1.0, 1.0, 1.0);
//    glBegin(GL_POLYGON);
//    glVertex2f(x_ - 25, 400 * len);
//    glVertex2f(x_ - 50, 400 * len);
//    glVertex2f(x_ - 50, 600 * len);
//    glVertex2f(x_ - 25, 600 * len);
//    glEnd();
//
//    draw_circle(180.0, 0.0, 25.0 / 2, x_ - 75.0 / 2, 600 * len);
//    draw_circle(90.0, 25, 50, x_ + x, 400 * len, -1);
//    draw_circle(90.0, 25, 50, x_, 400 * len, -1, -1);
//}

void generate_tree(int x_, double len)
{
    int x = 100;
    int y = 10;
    int z = 20;
    int m = 80;
    int v = 250;
    int dist[7] = {v, v+z, v+z+m, v+2*z+m, v+2*z+2*m, v+3*z+2*m, v+3*z+3*m};

    // Divider
    displayTexture(divTex,
                   x_ - y,      dist[0]     * len,
                   x_ + x + y,  dist[0]     * len,
                   x_ + x + y,  dist[0] + z * len,
                   x_ - y,      dist[0] + z * len);


    // End 1
    displayTexture(endTex,
                   x_,      dist[1]     * len,
                   x_ + x,  dist[1]     * len,
                   x_ + x,  dist[1] + m * len,
                   x_,      dist[1] + m * len);

    // Divider
    displayTexture(divTex,
                   x_ - y,      dist[2]     * len,
                   x_ + x + y,  dist[2]     * len,
                   x_ + x + y,  dist[2] + z * len,
                   x_ - y,      dist[2] + z * len);

    // Middle
    displayTexture(midTex,
                   x_,      dist[3]             * len,
                   x_ + x,  dist[3]             * len,
                   x_ + x,  dist[3] + m + 20    * len,
                   x_,      dist[3] + m + 20    * len);

    // Divider
    displayTexture(divTex,
                   x_ - y,      dist[4]     * len,
                   x_ + x + y,  dist[4]     * len,
                   x_ + x + y,  dist[4] + z * len,
                   x_ - y,      dist[4] + z * len);

    // End 2
    displayTexture(endTex,
                   x_,      dist[5]     * len,
                   x_ + x,  dist[5]     * len,
                   x_ + x,  dist[5] + m * len,
                   x_,      dist[5] + m * len);

    // Divider
    displayTexture(divTex,
                   x_ - y,      dist[6]     * len,
                   x_ + x + y,  dist[6]     * len,
                   x_ + x + y,  dist[6] + z * len,
                   x_ - y,      dist[6] + z * len);

}


#endif // OBSTACLE_H_INCLUDED
