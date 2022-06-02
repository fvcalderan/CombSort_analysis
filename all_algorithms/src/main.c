#include <stdio.h>
#include <sorts.h>

#define NUMSORTS 7 /* number of implemented sorting algorithms */

void print_array(int *A, int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int main(int argc, char **argv)
{
    /* declare variables */
    int *A;
    FILE *f;
    sort stats;

    /* check amount of arguments */
    if (argc != 5) {
        printf("Usage: %s file_name method size print\n", argv[0]);
        return 0;
    }

    /* name arguments */
    char *file_path = argv[1];
    int sorting_method = atoi(argv[2]);
    int array_size = atoi(argv[3]);
    int print_sorted = atoi(argv[4]);

    /* allocate array */
    A = (int *) malloc(array_size * sizeof(int));

    /* all sorting algorithms */
    sort (*sort_algorithms[NUMSORTS])(int*, int) = {
        insertion_sort,
        selection_sort,
        bubble_sort,
        heap_sort,
        merge_sort,
        quick_sort,
        comb_sort
    };

    /* load array from file */
    f = fopen(file_path, "rb");
    fread(A, sizeof(int), array_size, f);

    /* sort array */
    stats = sort_algorithms[sorting_method](A, array_size);

    /* print sorted array */
    if (print_sorted)
        print_array(A, array_size);

    /* print number of comparisons and number of movements */
    printf("%ld,%ld\n", stats.cmp, stats.mov);

    /* free memory, close file descriptors and return success */
    free(A);
    fclose(f);
    return 0;
}
