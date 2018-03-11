#ifndef ARR_H_
#define ARR_H_

typedef struct {
    void *begin, *end, *alloc;
} arr;

void arr_construct(arr *a);
void arr_destroy(arr *a);
void *arr_add(arr *a, long s);
void arr_push_array(arr *a, void *c, long s);
char *arr_cstr(arr *a);

#define arr_push(a, v)  do { *arr_add((a), (sizeof(v))) = v; } while (0)
#define arr_push_carray(a, c)  do { arr_push_array((a), (c), sizeof((c))); } while (0)
#define arr_idx(t, a, i)  (*(((t*)a->begin)+i))

#define for_each_arr(i, a)  for ((i) = (a)->begin; (i) != (a)->end; (i)++)

#endif
