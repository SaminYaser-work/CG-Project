#ifndef DIFFICULTY_H_INCLUDED
#define DIFFICULTY_H_INCLUDED

bool UpdateDiffculty(double exTime){
    int val = int(exTime);
    if(val%10 == 0)
        return true;
    return false;
}


#endif // DIFFICULTY_H_INCLUDED
