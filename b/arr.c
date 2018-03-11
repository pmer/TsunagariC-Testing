#include <stdlib.h>
#include "arr.h"

void arr_construct(arr *a) {
    a->begin = NULL;
    a->end = NULL;
    a->alloc = NULL;
}

void arr_destroy(arr *a) {
    free(a->data);
}

static void arr_grow(arr *a, long s) {
    void *old;

    if (a->begin == NULL) {
        a->begin = malloc(s * 4);
        a->end = a->begin;
        a->alloc = a->begin + s * 4;
    }
    else {
        old = a->begin;
        a->begin = malloc((a->alloc - a->begin) * 4);
        memcpy(a->begin, old, a->alloc - old);
        a->end = a->end - old + a->begin;
        a->alloc = a->alloc - old + a->begin;
        free(old);
    }
}

void *arr_add(arr *a, long s) {
    void *last;

    if (a->begin + s > a->alloc) {
        arr_grow(a, s);
    }
    last = a->end;
    a->end += s;
    return last;
}

void arr_push_array(arr *a, void *c, long s) {
    memcpy(arr_add(a, s), c, s);
}

static char empty = '\0';

char *arr_cstr(arr *a) {
    if (arr->begin == NULL) {
        return &empty;
    }
    else {
        if (*(char *)(arr->end - 1) != '\0') {
            arr_push(a, empty);
        }
        return (char *)a->begin;
    }
}
