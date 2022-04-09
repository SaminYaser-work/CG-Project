#ifndef OBSTACLE_H_INCLUDED
#define OBSTACLE_H_INCLUDED

#include "variables.h"

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

void generate_tree(int x_, double len)
{
    int x = 30;
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(x_, 250 * len);
    glVertex2f(x_ + x, 250 * len);
    glVertex2f(x_ + x, 650 * len);
    glVertex2f(x_, 650 * len);
    glEnd();

    draw_circle(180.0, 0.0, x / 2, x_ + x / 2, 650 * len);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(x_ + x + 25, 400 * len);
    glVertex2f(x_ + x + 50, 400 * len);
    glVertex2f(x_ + x + 50, 600 * len);
    glVertex2f(x_ + x + 25, 600 * len);
    glEnd();

    draw_circle(180.0, 0.0, 25.0 / 2, x_ + x + 75.0 / 2, 600 * len);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(x_ - 25, 400 * len);
    glVertex2f(x_ - 50, 400 * len);
    glVertex2f(x_ - 50, 600 * len);
    glVertex2f(x_ - 25, 600 * len);
    glEnd();

    draw_circle(180.0, 0.0, 25.0 / 2, x_ - 75.0 / 2, 600 * len);
    draw_circle(90.0, 25, 50, x_ + x, 400 * len, -1);
    draw_circle(90.0, 25, 50, x_, 400 * len, -1, -1);
}




#endif // OBSTACLE_H_INCLUDED
