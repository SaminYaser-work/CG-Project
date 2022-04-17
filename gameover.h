#ifndef GAMEOVER_H_INCLUDED
#define GAMEOVER_H_INCLUDED

#include <string>
#include "texture.h"
#include "printText.h"

void gameOver(){
    displayTexture("C:\\Users\\samin\\Documents\\Projects\\Graphics\\CG-Project\\textures\\gmo2.jpg",
                   600, 1000, 1400, 1000, 1400, 1750, 600, 1750);

    // Add text to {to play agian}
    std::string contText="Press <space> to try again";
    printText(contText,720.0,1030.0, 0.3, 2);
}
#endif // GAMEOVER_H_INCLUDED
