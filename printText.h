#ifndef PRINTTEXT_H_INCLUDED
#define PRINTTEXT_H_INCLUDED

void printText(std::string massage, float position_X=130.0, float position_Y=1900.0){
    int n = massage.size();

    glRasterPos2f(position_X,position_Y);
//    int len=strlen(txt);
    for(int i=0; i<massage.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,massage[i]);
    }
}


#endif // PRINTTEXT_H_INCLUDED
