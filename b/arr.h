#ifndef ARR_H_
#define ARR_H_

#include <stdlib.h>

typedef struct {
    void *begin, *end, *alloc;
} arr;

void arr_grow(arr *a, long s, int mul);
void *arr_add(arr *a, long s);

#define arr_construct(a)  do { (a)->begin = (a)->end = (a)->alloc = NULL; } while (0)
#define arr_construct_n(t, a, n)  do { arr_construct((a)); arr_grow((a), sizeof(t), (n)); } while (0)
#define arr_construct_mem(a, vs, l)  do { arr_construct((a)); arr_push_mem((a), (vs), (l)); } while (0)
#define arr_construct_zstr(a, s)  do { arr_construct_mem((a), (s), strlen(s)); } while (0)
#define arr_destroy(a)  do { free((a)->begin); } while (0)
#define arr_push(t, a, v)  (*(t *)arr_add((a), sizeof(t)) = (v))
#define arr_push_mem(a, vs, l)  do { memcpy(arr_add((a), (l)), (vs), (l)); } while (0)
#define arr_push_array(a, vs)  do { arr_push_mem((a), (vs), sizeof((vs))); } while (0)
#define arr_push_zstr(a, s)  do { arr_push_mem((a), (s), strlen(s)); } while (0)
#define arr_idx(t, a, i)  (*(((t *)(a)->begin)+(i)))
#define arr_array(t, a)  ((t *)(a)->begin)
#define arr_zarray(t, a)  (((a)->begin == NULL) ? NULL : (*(t *)((a)->end - sizeof(t)) != 0) ? (arr_push(t, (a), 0), (t *)(a)->begin) : (t *)(a)->begin)

#define for_each_in_arr(i, a)  for ((i) = (a)->begin; (i) != (a)->end; (i)++)

#endif
