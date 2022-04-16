#ifndef RANDOMVAL_H_INCLUDED
#define RANDOMVAL_H_INCLUDED

template<typename T>
T getRand(T minRange, T maxRange)
{
    return minRange + (fmod(rand(), (maxRange - minRange + 1)));
}

#endif // RANDOMVAL_H_INCLUDED
