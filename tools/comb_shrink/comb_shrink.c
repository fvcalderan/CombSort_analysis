#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

typedef struct {
    uint64_t cmp;
    uint64_t mov;
} sort;

void print_array(int *A, int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

sort comb_sort(int * A, int n, float shrink)
{
    int sorted = 0, gap = n, i, sm, aux;
    sort s = { .cmp = 0, .mov = 0 };

    while (!sorted) {
        gap = (int)floor(gap / shrink);
        if (gap <= 1) {
            gap = 1;
            sorted = 1;
        }

        for (i = 0; i < n - gap; i++) {
            sm = gap + i;
            if (/* cmp */ s.cmp ++, A[i] > A[sm]) {
                aux = A[sm];                /* mov */
                A[sm] = A[i];               /* mov */
                A[i] = aux;                 /* mov */ s.mov += 3;
                sorted = 0;
            }
        }
    }

    return s;
}

int main(int argc, char **argv)
{
    /* declare variables */
    int *A;
    FILE *f;
    sort stats;

    /* check amount of arguments */
    if (argc != 5) {
        printf("Usage: %s file_name shrink size print\n", argv[0]);
        return 0;
    }

    /* name arguments */
    char *file_path = argv[1];
    float comb_shrink = atof(argv[2]);
    int array_size = atoi(argv[3]);
    int print_sorted = atoi(argv[4]);

    /* allocate array */
    A = (int *) malloc(array_size * sizeof(int));

    /* load array from file */
    f = fopen(file_path, "rb");
    fread(A, sizeof(int), array_size, f);

    /* sort array */
    stats = comb_sort(A, array_size, comb_shrink);

    /* print sorted array */
    if (print_sorted)
        print_array(A, array_size);

    /* print shrink, number of comparisons and number of movements */
    printf("%f,%ld,%ld\n", comb_shrink, stats.cmp, stats.mov);

    /* free memory, close file descriptors and return success */
    free(A);
    fclose(f);
    return 0;
}
