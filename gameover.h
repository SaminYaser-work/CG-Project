#ifndef GAMEOVER_H_INCLUDED
#define GAMEOVER_H_INCLUDED

#include <string>
#include "texture.h"
#include "printText.h"

void gameOver(){
    displayTexture("E:\\CG-Project\\textures\\gmo2.jpg", 600, 1000, 1400, 1000, 1400, 1750, 600, 1750);  //'🆘Change the gmo2.jpg file direcotry...! 

    // Add text to {to play agian}
    std::string contText="Press <space> to play again";
    printText(contText,690.0,1030.0, 0.3, 2);
}
#endif // GAMEOVER_H_INCLUDED
