#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class NormalDistribution
{
public:
    static double poll() { return dist(gen); }
private:
    inline static std::random_device rd;
    inline static std::mt19937 gen{rd()};
    inline static std::normal_distribution<double> dist{0.0, 1.0};
};

#endif //RANDOM_H
