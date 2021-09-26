#include <stdio.h>

static int static_val = 5;

void hello() {
    printf("hello: %d\n", static_val);
}