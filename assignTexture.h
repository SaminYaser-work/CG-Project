#ifndef ASSIGNTEXTURE_H_INCLUDED
#define ASSIGNTEXTURE_H_INCLUDED

#include "variables.h"

void assignTexture()
{
    // Player
    if(isDead)
    {
        bodyTex = "C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\body5d.png";
        handTex = "C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\handwd.png";
        headTex = "C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\head_ds.png";
    }
    else
    {
        bodyTex = "C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\body5.png";
        handTex = "C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\handw.png";
        headTex = "C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\head_bs.png";
    }

    neckTex = "C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\necks.png";
    head2Tex = "C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\head_ss.png";


    // Obstacle
    divTex = "C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\b_d.png";
    endTex = "C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\b_1.png";
    midTex = "C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\b_2.png";
    mid2Tex = "C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\b_2v.png";

    // Logo
    logoTex = "C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\bin\\Debug\\logo.png";
}

#endif // ASSIGNTEXTURE_H_INCLUDED
