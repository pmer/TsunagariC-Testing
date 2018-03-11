#include <stdlib.h>
#include <string.h>
#include "arr.h"

void arr_grow(arr *a, long s, int mul) {
    void *old;

    if (a->begin == NULL) {
        a->begin = malloc(s * mul);
        a->end = a->begin;
        a->alloc = a->begin + s * mul;
    }
    else {
        old = a->begin;
        a->begin = malloc((a->alloc - a->begin) * mul);
        memcpy(a->begin, old, a->alloc - old);
        a->end = a->end - old + a->begin;
        a->alloc = a->alloc - old + a->begin;
        free(old);
    }
}

void *arr_add(arr *a, long s) {
    void *last;

    if (a->begin + s > a->alloc) {
        arr_grow(a, s, 4);
    }
    last = a->end;
    a->end += s;
    return last;
}
