#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

typedef struct {
    uint64_t cmp;
    uint64_t mov;
} sort;

sort bubble_sort(int * A, int n);
sort comb_sort(int * A, int n);
sort heap_sort(int * A, int n);
sort insertion_sort(int * A, int n);
sort merge_sort(int * A, int n);
sort quick_sort(int * A, int n);
sort selection_sort(int * A, int n);
