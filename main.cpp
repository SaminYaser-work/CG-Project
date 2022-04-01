#include <time.h>
#include <cmath>
#include <math.h>
#include <random>
#include <windows.h>
#include <GL/glut.h>

const double DEG2RAD = 3.1415926535897932384/180;

// Screen width & height
const float sWidth = 1336;
const float sHeight = 768;

// Animation speed
static int animationPeriod = 4;

// Game start or pause
static int isAnimate = 0;

// Player height
const int fact = 3;

// Player character distance from the right side of the screen
const int x = 80;

// Player character distance from the bottom of the screen
static double w = 200;

// Used for jumping
static int flag = 0;

// Obstacle
static int x_ = 2500;
static int x2_ = 4500;
static double obstacleHeight = 1.0;


// Timer
void animate(int value)
{
    if(isAnimate)
    {
        glutPostRedisplay();
        glutTimerFunc(animationPeriod, animate, 1);
    }
}

template<typename T>
T getRand(T minRange, T maxRange)
{
    return minRange + ( fmod(rand(),  ( maxRange - minRange + 1 ) ));
}

void keyInput(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 27:
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
    if( key == GLUT_KEY_UP && flag==0 && w <= 200.0)
    {
        flag  = 1;
    }
    glutPostRedisplay();
}

void generate_tree(int x_, double len)
{
    int x = 30;
    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(x_ - 50, 400 * len);
    glVertex2f(x_ + x + 50, 400 * len);
    glVertex2f(x_ + x + 50, 600 * len);
    glVertex2f(x_ - 50, 600 * len);
    glEnd();
}

void drawPlayer()
{
    glBegin(GL_QUADS);
    glColor3ub(0, 0, 0);
    glVertex2i(10 + x, 100 + w);
    glVertex2i(157 + x, 100 + w);
    glVertex2i(157 + x, 500 + w);
    glVertex2i(10 + x, 500 + w);
    glEnd();
}

void reset()
{
    w = 200;
    flag = 0;

    x_ = 2500;
    x2_ = 4500;
    animationPeriod = 4;
    isAnimate = 0;
}
void render( void )
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Making distance between 2 obstacle if they become too close
    if(x2_ > x_)
    {
        x2_ - x_ < 1000 ? x2_ += 500 : x2_ = x2_;
    }
    else
    {
        x_ - x2_ < 1000 ? x_ += 500 : x_ = x_;
    }

    // Placing obstacle
    generate_tree(x_, obstacleHeight);
    generate_tree(x2_, obstacleHeight);


    // Move the obstacle closer
    if(x_>= 0)
        x_ -= 5;
    else
    {
        x_ = 2000 + getRand<int>(0, 500);
    }
    x2_ >= 0 ? x2_ -= 5 : x2_ = 4500 + getRand<int>(1000, 1500);


    // The street
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(0, 250);
    glVertex2f(2000, 250);
    glEnd();

    drawPlayer();

    // Collision check
    if(collision(0.8))
    {
        reset();
    }

    // Jump
    if(flag==1)
    {
        // Going up
        if(w<=1000 )
        {
            w += 8;
        }
        else
        {
            flag = 0;
        }
    }
    // Coming back down
    else if(w >= 200 ){
        w -= 8;
    }

    //Swapping buffer form GPU to CPU
    glutSwapBuffers();
}


void myInit(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 2000, 0.0, 2000);
}

int main( int argc, char** argv )
{

    srand(time(NULL));

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
