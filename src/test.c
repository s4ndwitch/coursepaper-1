#include <stdlib.h>

#include "config.h"


int main() {
    int *result = readConfig("/home/sandwitch/Documents/gameoflife/data/config.conf");
    printf("%d %d %d %d\n", result[0], result[1], result[2], result[3]);
    return 0;
}