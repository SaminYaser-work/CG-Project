#include "variables.h";

void drawWheel(float, float, float, float, int);

void drawPlayer()
{
    glClearColor(0.0, 0.0, 0.0, 0.5);

    if(isDead)
    {
        bodyTex = "C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\body4d.png";
        handTex = "C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\handd.png";
        headTex = "C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\head_ds.png";
    }
    else
    {
        bodyTex = "C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\body4s.png";
        handTex = "C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\hands.png";
        headTex = "C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\head_bs.png";
    }

    // Body
    displayTexture(bodyTex, x, 130 + w, x + 157, 130 + w, x + 157, 400 + w, x, 400 + w);

    // Wheel
    glColor3ub(36,38,39);
    glLineWidth(8);
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

    glColor3ub(0,0,0);
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
    displayTexture(handTex, x + 20, 300 + w, x + 170, 300 + w - walk, x + 170, 340 + w - walk, x + 20,  340 + w);

    // Finger
    glColor3ub(120,120,120);
    glLineWidth(5);
    glBegin(GL_LINES);
        glVertex2i(x + 170, 325 + w - walk);
        glVertex2i(x + 190, 325 + w - walk);
    glLineWidth(3);
        glVertex2i(x + 190, 330 + w - walk);
        glVertex2i(x + 200, 300 + w - walk);
    glEnd();

    // Neck
    displayTexture("C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\necks.png",
                   x +  60, 400 + w, x +  80, 400 + w, x + 100, 450 + w, x +  80, 450 + w);

    displayTexture("C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\necks.png",
                   x + 100, 450 + w, x +  80, 450 + w, x +  60, 500 + w, x +  80, 500 + w);

    // Head
    displayTexture("C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\head_ss.png",
                   x +  50 - walk * .01, 500 + w, x + 100, 500 + w - walk * .2,
                   x + 100 + walk * .2, 550 + w - walk * .2, x +  50 + walk * .2, 550 + w);

    displayTexture(headTex,
                    x + 100 - walk * .01, 470 + w, x + 150, 470 + w - walk * .2,
                    x + 150 + walk * .2, 570 + w - walk * .2, x + 100 + walk * .2, 570 + w);
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

