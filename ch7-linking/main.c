#include <stdio.h>

static int static_val = 4;

void hello();

int main() {
    hello();
    printf("main: %d\n", static_val);

    return 0;
}