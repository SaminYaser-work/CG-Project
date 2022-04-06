#include <time.h>
#include <cmath>
#include <math.h>
#include <random>
#include <windows.h>
#include <GL/glut.h>
#include <iostream>

#define GL_CLAMP_TO_EDGE 0x812F
#include "bg.h";
#include "player.h";


const float sWidth = 1336;
const float sHeight = 768;

static int animationPeriod = 4;
static int isAnimate = 0;

// Player height
const int fact = 3;

// Used for jumping
static int flag = 0;

static int walk = 0;
static int x_ = 2500;
static int x2_ = 4500;
static double obstacleHeight = 1.0;


void animate(int value)
{
    if(isAnimate)
    {
        glutPostRedisplay();
        glutTimerFunc(animationPeriod, animate, 1);
    }
}


void keyInput(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 27:
    case 'q':
        exit(0);

    // Starts and Pauses the game
    case ' ':
        if(isAnimate) isAnimate = 0;
        else
        {
            isAnimate = 1;
            animate(1);
        }
        break;
    }
}

bool collision(double len)
{
    // Checking the distance
    if(abs(157 + x - (x_ + x + 50)) <= 100 + x || abs(157 + x - (x2_ + x + 50)) <= 100 + x)
    {
        // If height is low then its a hit
        if(5 * fact + w <= 650 * len)
            return true;

        return false;
    }
    return false;
}

void specialKeyInput(int key, int x, int y )
{
    if( key == GLUT_KEY_UP && flag==0 && w <= 250.0)
    {
        flag  = 1;
        sndPlaySound("C:\\Users\\samin\\Documents\\Projects\\Graphics\\2dDino\\sound\\jump.wav", SND_ASYNC);
    }
    glutPostRedisplay();
}

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


void reset()
{
    w = 250;
    flag = 0;
    walk = 0;
    x_ = 2500;
    x2_ = 4500;
    animationPeriod = 4;
    isAnimate = 0;
}


void render( void )
{
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawBG();

    drawStreet();

    if(x2_ > x_)
    {
        x2_ - x_ < 1000 ? x2_ += 500 : x2_ = x2_;
    }
    else
    {
        x_ - x2_ < 1000 ? x_ += 500 : x_ = x_;
    }

    generate_tree(x_, obstacleHeight);
    generate_tree(x2_, obstacleHeight);

    // Move the obstacle closer
    if(x_>= 0)
        x_ -= 5;
    else
    {
        x_ = 2000 + getRand<int>(0, 500);
//        obstacleHeight = getRand<int>(1 , 2);
    }
    x2_ >= 0 ? x2_ -= 5 : x2_ = 4500 + getRand<int>(1000, 1500);

    // The street outer line
    glLineWidth(5);
    glColor3ub(182, 29, 129);
    glBegin(GL_LINES);
        glVertex2f(0, 250);
        glVertex2f(2000, 250);
    glEnd();

    drawPlayer();

    if(collision(0.8))
    {
        reset();
    }

    // Feet animation
    if( w <=250)
    {
        if(walk==-20 )
            walk = 20;
        else
        {
            walk = -20;
        }
    }
    else
    {
        walk = 0;
    }

    // Jump
    if(flag==1)
    {
        // Going up
        if(w<=1000 )
        {
            w = w + 8;
        }
        else
        {
            flag = 0;
        }
    }
    // Coming back down
    else if(w >= 250 )
        w = w - 8;


    glutSwapBuffers();
}


void myInit(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 2000, 0.0, 2000);
//    getTexture();
}

int main( int argc, char** argv )
{
    srand(time(NULL));
    randomizeArray();
    incrementLine();
    decrementLine();

    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize( sWidth, sHeight );

    // Creates window at the center of the monitor
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-sWidth)/2,
                           (glutGet(GLUT_SCREEN_HEIGHT)-sHeight)/2);

    glutCreateWindow("CG Project Demo");

    myInit();
    glutDisplayFunc(render);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);



    glutMainLoop();
}
