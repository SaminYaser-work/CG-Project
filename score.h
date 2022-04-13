#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

// time calculation
clock_t clockStart;

double excectime()
{
    clock_t clockEnd = clock();
    double time_taken = double(clockEnd - clockStart) / double(CLOCKS_PER_SEC);
    return time_taken;
}

std::string Current_Score(double exTime)
{

    std::string message_ = "Score: ";
    std::string scr = std::to_string(std::round(exTime));
    int rmv = 7;
    while(rmv--) scr.pop_back();
    message_ += scr;
    return message_;
}

#endif // SCORE_H_INCLUDED
