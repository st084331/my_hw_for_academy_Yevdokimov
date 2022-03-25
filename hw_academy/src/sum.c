#include "../include/functions.h"

int sum(int n) {
    int res = 0;
    for (int j = 1; j != n; j++) {
        res += j;
    }
    return res;
}
