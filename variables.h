#ifndef VARIABLES_H_INCLUDED
#define VARIABLES_H_INCLUDED

// Player character distance from the right side of the screen
const int x = 80;

// Player character distance from the bottom of the screen
static double w = 250;

int walk = 0;

bool isDead = false;

// change this to make the game difficult
int diff = 6; //Starting value. Looks good to maine.

int jumpVelocity = diff + 5;

// Player
const char* headTex;
const char* head2Tex;
const char* bodyTex;
const char* handTex;
const char* neckTex;

// Obstacle
const char* divTex;
const char* midTex;
const char* endTex;

#endif // VARIABLES_H_INCLUDED
