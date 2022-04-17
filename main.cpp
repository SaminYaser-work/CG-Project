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

#include "printText.h"
#include "texture.h"
#include "bg.h"
#include "player.h"
#include "obstacle.h"
#include "score.h"
#include "difficulty.h"
#include "assignTexture.h"
#include "randomVal.h"
#include "gameover.h"

using namespace std;

const float sWidth = 1336;
const float sHeight = 768;

const float animationPeriod = 4.0; // 10 means-> slower; closer to 0 means faster (DO NOT CHANGE AT RUNTIME)
static int isAnimate = 0;

// Player height
const int fact = 3;

// Used for jumping
static int flag = 0;

static int x_ = 2500;
static int x2_ = 4500;
static double obstacleHeight = 1.0;

int score = 0;
int period = 0;

bool isFirst = true;

bool dieNextFrame = false;
bool pauseNextFrame = false;

bool isTut = false;
bool showTut = false;
int delay = 4000;


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
            pauseNextFrame = true;
        }
        else
        {
            isAnimate = 1;
            animate(1);
            sndPlaySound("start.wav", SND_ASYNC);
            if(isFirst)
                showTut = true;
            isFirst = false;
            isDead = false;
            pauseNextFrame = false;
            assignTexture();
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
        showTut = false;
    }
    glutPostRedisplay();
}

void reset()
{
    diffc = dDiff;
    w = 250;
    flag = 0;
    walk = 0;
    x_ = 2500;
    x2_ = 4500;
    isAnimate = 0;
    score = 0;
    period = 0;
    dieNextFrame = false;
}


void render( void )
{
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawBG();

    drawStreet();


    //Printing Score & Level
    if(!isFirst)
    {
        printText("Score: " + to_string(score));
        printText("Level: " + to_string(diffc - dDiff), 1450, 1800, 1.0, 5);
    }
    period++;
    if (period > 500/animationPeriod && !showTut)
    {
        score++;
        period = 0;

        // Difficulty increase
        if(score%7==0 && diffc < 12)
        {
            diffc+=1;
            // sndPlaySound("level_up.wav", SND_ASYNC);
        }
    }


    // Makes gap between obstacles
    if(x2_ > x_)
    {
        x2_ - x_ < 1000 ? x2_ += 600 : x2_ = x2_;
    }
    else
    {
        x_ - x2_ < 1000 ? x_ += 600 : x_ = x_;
    }

    if(showTut)
    {
        glColor3ub(122,152,238);
        printText("Press Up Arrow to Jump!", 530, 1500, 0.5, 3);
        printText("Press <space> to pause the game", 420, 1200, 0.5, 3);
    }
    else
    {
        if(delay >= 0 && isAnimate)
        {
            printText("Avoid The Obstacles!", 350, 1500, 1, 5);
            delay -= 10;
        }

        // Rendering obstacles
        placeObstacle(x_, obstacleHeight, randTex1);
        placeObstacle(x2_, obstacleHeight, randTex2);

        // Move the obstacle closer
        // diff is defined in "variables.h". So change it there. DO NOT CHANGE ANYTHING HERE

        if(x_ >= 0)
        {
            x_ -= diffc;
        }
        else
        {
            x_ = 2000 + getRand<int>(0, 500);
            randTex1 = getRand<int>(0, 1);
        }

        if(x2_ >= 0)
        {
            x2_ -= diffc;
        }
        else
        {
            x2_ = 4500 + getRand<int>(1000, 1500);
            randTex2 = getRand<int>(0, 1);
        }
    }


    // The street outer line
    glLineWidth(5);
    glColor3ub(182, 29, 129);
    glBegin(GL_LINES);
    glVertex2f(0, 250);
    glVertex2f(2000, 250);
    glEnd();

    drawPlayer();

    if(collision(0.8) || dieNextFrame)
    {
        if(!dieNextFrame)
        {
            dieNextFrame = true;
            isDead = true;
            assignTexture();
        }
        else
        {
            reset();
            sndPlaySound("game_over.wav", SND_ASYNC);
            gameOver();
        }
    }

    // Jumping animation
    if( flag == 1 )
    {
        walk += 1;
    }
    else
    {
        if(walk > 0)
            walk -= 2;
    }

    // Jump
    if(flag==1)
    {
        // Going up
        if(w<=1000 )
        {
            w = w + jumpVelocity;
        }
        else
        {
            flag = 0;
        }
    }
    // Coming back down
    else if(w >= 250 )
        w = w - jumpVelocity;


    if(isFirst)
    {
        // Relative path doesn't work
        // Change this to absolute path of your computer
        // Don't forget to escape '\' !!
        displayTexture(logoTex, 600, 900, 1400, 900, 1400, 1650, 600, 1650);
//        glColor3ub(244, 150, 210);
//        printText("Press <space> to start...", 600, 1050, 0.5, 3);
    }

    if(pauseNextFrame)
    {
        sndPlaySound("pause.wav", SND_ASYNC);
        printText("Game Paused...", 550, 900, 1.0, 5);
        isAnimate = 0;
    }


//    glFlush();
    glutSwapBuffers();
}



void myInit(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 2000, 0.0, 2000);
    assignTexture();


//    NO MUSIC BECAUSE HARAM
//    sndPlaySound("theme.wav", SND_ASYNC);
}

int main( int argc, char** argv )
{
    // clockStart = clock();
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

    glutCreateWindow("OpenGL Adventures");

    myInit();
    glutDisplayFunc(render);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);

    glutMainLoop();
}
