#ifndef PRINTTEXT_H_INCLUDED
#define PRINTTEXT_H_INCLUDED

// massage lol
void printText(std::string massage, float position_X=50.0, float position_Y=1800.0, float scale=1.0){

    glPushMatrix();
    glTranslatef(position_X, position_Y, 0.0f);
    glScalef(scale, scale, 0.0f);
    glLineWidth(5);

    unsigned char buf[256];
    std::copy(massage.begin(), massage.end(), buf);

    glutStrokeString(GLUT_STROKE_MONO_ROMAN, buf);

    glPopMatrix();
}


#endif // PRINTTEXT_H_INCLUDED
