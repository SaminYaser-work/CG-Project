#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <cstring>
#include <time.h>
#include <cmath>
#include <math.h>
#include <random>
#include <GL/freeglut.h>

#define GL_CLAMP_TO_EDGE 0x812F
#include "printText.h";
#include "bg.h";
#include "player.h";
#include "obstacle.h";
#include "score.h";
#include "difficulty.h";

using namespace std;

const float sWidth = 1336;
const float sHeight = 768;

const float animationPeriod = 4.0; // 10 means-> slower; closer to 0 means faster (DO NOT CHANGE AT RUNTIME)
static int isAnimate = 0;

// Player height
const int fact = 3;

// Used for jumping
static int flag = 0;

static int walk = 0;
static int x_ = 2500;
static int x2_ = 4500;
static double obstacleHeight = 1.0;

int score = 0;
int period = 0;


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
        if(isAnimate)
        {
            isAnimate = 0;
            sndPlaySound("pause.wav", SND_ASYNC);
        }
        else
        {
            isAnimate = 1;
            animate(1);
            sndPlaySound("start.wav", SND_ASYNC);
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
        sndPlaySound("jump.wav", SND_ASYNC);
    }
    glutPostRedisplay();
}

void reset()
{
    w = 250;
    flag = 0;
    walk = 0;
    x_ = 2500;
    x2_ = 4500;
    isAnimate = 0;
    score = 0;
    period = 0;
}


void render( void )
{
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawBG();

    drawStreet();

    // Looks like shit
    //Rain(true);

    //Printing Score
    printText(Current_Score(score));
    period++;
    if (period > 500/animationPeriod)
    {
        score++;
        period = 0;
    }

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
    int diff = 5; // change this to make the game difficult
    x_ >= 0 ? x_ -= diff : x_ = 2000 + getRand<int>(0, 500);
    x2_ >= 0 ? x2_ -= diff : x2_ = 4500 + getRand<int>(1000, 1500);

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
        sndPlaySound("game_over.wav", SND_ASYNC);
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

//    NO MUSIC BECAUSE HARAM
//    sndPlaySound("theme.wav", SND_ASYNC);
//    getTexture();
}

int main( int argc, char** argv )
{
    clockStart = clock();
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



