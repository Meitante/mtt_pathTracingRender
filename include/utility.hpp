#ifndef PATHTRACING_UTILITY_H
#define PATHTRACING_UTILITY_H

#include <iostream>
#include <cmath>
#include <random>


constexpr float PI = 3.1415926;
constexpr float RussianRoulette = 0.8;
constexpr bool sw1 = false;

/*
    models path
*/
namespace commonData
{
constexpr char rootPath[] =  "../";
constexpr char bunnyPath[] = "../models/bunny/bunny.obj";
}



/*
    x0 should be less than or equal to x1
*/
inline bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1)
{
    float discr = b * b - 4 * a * c;
    if (discr < 0) return false;
    else if (discr == 0) x0 = x1 = - 0.5 * b / a;
    else {
        float q = (b > 0) ?
                  -0.5 * (b + std::sqrt(discr)) :
                  -0.5 * (b - std::sqrt(discr));
        x0 = q / a;
        x1 = c / q;
    }
    if (x0 > x1) std::swap(x0, x1);
    return true;
}

inline float getRandomFloat()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<float> dist(0.f, 1.f); // distribution in range [0, 1]

    return dist(rng);
}

inline void UpdateProgress(int done, int all)
{
    int barWidth = 70;
    float progress = ((float)done)/all;
    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %";
    std::cout << "  [" << done << "/" << all << "]\r";
    std::cout.flush();
};

inline float getRadianFromDegree(float Degree)
{
    return Degree * PI / 180;
}


#endif