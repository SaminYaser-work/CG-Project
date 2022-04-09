#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <cstring>
#include <time.h>
#include <cmath>
#include <math.h>
#include <random>

#define GL_CLAMP_TO_EDGE 0x812F
#include "bg.h";
#include "player.h";
#include "obstacle.h";

const float sWidth = 1336;
const float sHeight = 768;

float animationPeriod = 9.0; // 10 means-> slower; closer to 0 means faster
static int isAnimate = 0;
bool rainday = true;
float rain = 0.0;
// time calculation
clock_t clockStart;
double excectime()
{
    clock_t clockEnd = clock();
    double time_taken = double(clockEnd - clockStart) / double(CLOCKS_PER_SEC);
    return time_taken;
}

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
    animationPeriod = 4;
    isAnimate = 0;
}

string Current_Score(double exTime){
    string message_ = "Score: ", scr = to_string(exTime);
    int rmv =3;
    while(rmv--) scr.pop_back();
    message_ += scr;
    return message_;
}

bool UpdateDiffculty(double exTime){
    int val = int(exTime);
    if(val%10 == 0)
        return true;
    return false;
}

void Rain(int value)
{
    if(rainday)
    {
        rain += 0.01f;

        glBegin(GL_POINTS);
        for(int i=1; i<=1000; i++)
        {
            int x=rand(),y=rand();
            x%=1300;
            y%=650;
            glBegin(GL_LINES);
            glColor3f(1.0, 1.0, 1.0);
            glVertex2d(x,y);
            glVertex2d(x+5,y+5);
            glEnd();
        }
        glutPostRedisplay();
        glutTimerFunc(5, Rain, 0);
        glFlush();
    }
}

void printText(string massage, float position_X=130.0, float position_Y=1900.0){
    int n = massage.size();

    glRasterPos2f(position_X,position_Y);
//    int len=strlen(txt);
    for(int i=0; i<massage.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,massage[i]);
    }
}

void render( void )
{
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawBG();

    drawStreet();

    //rainday =true;
    //Rain(rain);
    //*** Rain works fine, but the position in not okay...! Also creating a cause of blocking the difficulty ****//

            //Printing Text
    double exTime= excectime();
    printText(Current_Score(exTime));
    //For update difficulty
    /*
        if(UpdateDifficulty(exTime)){
            animationPeriod -=0.1;
            if(animationPeriod<=0.0){
                //We can add Game is completed Here....! :)
            }
        }
    Having Bug in difficulty Function. Had a crash on animation.
    */
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
    sndPlaySound("theme.wav", SND_ASYNC);
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



