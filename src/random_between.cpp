#include <random>
#include "random_between.h"

int random_between(int min, int max) {

    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> distribution(min, max);

    return distribution(engine);
}