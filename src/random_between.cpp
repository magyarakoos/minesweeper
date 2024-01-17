#include <stdlib.h>
#include "random_between.h"

int random_between(int min, int max) {
    return rand() % (max - min + 1) + min;
}
