#ifndef SOUNDANALIZE_H
#define SOUNDANALIZE_H

#include "waveparser.h"
#include <vector>

class SoundAnalize
{
public:
    SoundAnalize();

    typedef __int16_t value_t;
    typedef __int32_t int_t;

    struct Point : public std::pair<int_t, value_t> {
        inline int_t   &x() { return first ; }
        inline value_t &y() { return second; }
    };

    typedef std::vector<Point> MinPoints;

public:
    MinPoints getMinPoints();

private:

};

#endif // SOUNDANALIZE_H
