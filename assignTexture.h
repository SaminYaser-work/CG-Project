#ifndef ASSIGNTEXTURE_H_INCLUDED
#define ASSIGNTEXTURE_H_INCLUDED

#include "variables.h";

void assignTexture()
{
    // Player
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

    neckTex = "C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\necks.png";
    head2Tex = "C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\head_ss.png";


    // Obstacle
    divTex = "C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\b_d.png";
    endTex = "C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\b_1.png";
    midTex = "C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\b_2.png";
}

#endif // ASSIGNTEXTURE_H_INCLUDED
