#ifndef UTILS_H_
#define UTILS_H_

#include <cstdlib>

namespace Utils
{
    inline float randomFloat(float min, float max);
};

inline float Utils::randomFloat(float min, float max)
{
    return min + ((float) rand() / (float) RAND_MAX) * (max - min);
}
#endif
