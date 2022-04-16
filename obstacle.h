#ifndef OBSTACLE_H_INCLUDED
#define OBSTACLE_H_INCLUDED

#include "variables.h"
#include "texture.h"

void placeObstacle(int x_, double len, int randVal)
{
    int x = 120;
    int y = 10;
    int z = 20;
    int m = 100;
    int v = 250;
    int dist[7] = {v, v+z, v+z+m, v+2*z+m, v+2*z+2*m, v+3*z+2*m, v+3*z+3*m};

    const char* randTex1;
    const char* randTex2;
    const char* randTex3;

    if(randVal)
    {
        randTex1 = divTex;
        randTex2 = midTex;
        randTex3 = endTex;
    }
    else
    {
        randTex1 = div2Tex;
        randTex2 = mid2Tex;
        randTex3 = end2Tex;
    }

    // Divider
    displayTexture(randTex1,
                   x_ - y,      dist[0]     * len,
                   x_ + x + y,  dist[0]     * len,
                   x_ + x + y,  dist[0] + z * len,
                   x_ - y,      dist[0] + z * len);


    // End 1
    displayTexture(randTex3,
                   x_,      dist[1]     * len,
                   x_ + x,  dist[1]     * len,
                   x_ + x,  dist[1] + m * len,
                   x_,      dist[1] + m * len);

    // Divider
    displayTexture(randTex1,
                   x_ - y,      dist[2]     * len,
                   x_ + x + y,  dist[2]     * len,
                   x_ + x + y,  dist[2] + z * len,
                   x_ - y,      dist[2] + z * len);


    // Middle
    displayTexture(randTex2,
                   x_,      dist[3]        * len,
                   x_ + x,  dist[3]        * len,
                   x_ + x,  dist[3] + m    * len,
                   x_,      dist[3] + m    * len);

    // Divider
    displayTexture(randTex1,
                   x_ - y,      dist[4]     * len,
                   x_ + x + y,  dist[4]     * len,
                   x_ + x + y,  dist[4] + z * len,
                   x_ - y,      dist[4] + z * len);

    // End 2
    displayTexture(randTex3,
                   x_,      dist[5]     * len,
                   x_ + x,  dist[5]     * len,
                   x_ + x,  dist[5] + m * len,
                   x_,      dist[5] + m * len);

    // Divider
    displayTexture(randTex1,
                   x_ - y,      dist[6]     * len,
                   x_ + x + y,  dist[6]     * len,
                   x_ + x + y,  dist[6] + z * len,
                   x_ - y,      dist[6] + z * len);

}

//void moveObstacle(int f, int dist)
//{
//    x_ >= 0 ? x_ -= diffc : x_ = 2000 + getRand<int>(0, 500);
//    x2_ >= 0 ? x2_ -= diffc : x2_ = 4500 + getRand<int>(1000, 1500);
//
//    if(f >= 0)
//    {
//
//    }
//}

#endif // OBSTACLE_H_INCLUDED
