#include <sorts.h>

/* Bubble Sort ============================================================= */

sort bubble_sort(int * A, int n)
{
    int i, j, change, aux;
    sort s = { .cmp = 0, .mov = 0};

    for (i = 0; i < n - 1; i++) {
        change = 0;
        for (j = 1; j < n - i; j++)
            if (/* cmp */ s.cmp ++, A[j] < A[j - 1]) {
                aux = A[j];                 /* mov */
                A[j] = A[j - 1];            /* mov */
                A[j - 1] = aux;             /* mov */ s.mov += 3;
                change = 1;
            }
        if (change == 0)
            break;
    }
    return s;
}

/* Comb Sort =============================================================== */

sort comb_sort(int * A, int n)
{
    int sorted = 0, gap = n, i, sm, aux;    /* declare variables */
    sort s = { .cmp = 0, .mov = 0};         /* stats collector */

    while (!sorted) {
        gap = (int)floor(gap / 1.3);        /* shrink the gap by 1.3 */
        if (gap <= 1) {
            gap = 1;                        /* minimum gap is 1 */
            sorted = 1;
        }

        for (i = 0; i < n - gap; i++) {
            sm = gap + i;                   /* index of compared element */
            /* check if a swap is needed, if so, perform the swap */
            if (/* cmp */ s.cmp ++, A[i] > A[sm]) {
                aux = A[sm];                /* mov */
                A[sm] = A[i];               /* mov */
                A[i] = aux;                 /* mov */ s.mov += 3;
                sorted = 0;
            }
        }
    }

    return s; /* return number of comparisons and movements */
}

/* Heap Sort =============================================================== */

void heapify(int * A, int left, int right, sort *s)
{
    int i, j, aux;
    i = left;
    j = i * 2 + 1;
    aux = A[i];                                 /* mov */ s->mov ++;
    while (j <= right) {
        if ((j < right) && (/* cmp */ s->cmp ++, A[j] < A[j + 1]))
            j++;
        if (/* cmp */ s->cmp ++, aux >= A[j])
            break;
        A[i] = A[j];                            /* mov */ s->mov ++;
        i = j;
        j = i * 2 + 1;
    }
    A[i] = aux;                                 /* mov */ s->mov ++;
}

void build_heap(int * A, int n, sort *s)
{
    int left;
    left = (n / 2) - 1;
    while (left >= 0) {
        heapify(A, left, n - 1, s);
        left--;
    }
}

sort heap_sort(int * A, int n)
{
    int m, aux;
    sort s = { .cmp = 0, .mov = 0};

    build_heap(A, n, &s);
    m = n - 1;
    while (m > 0) {
        aux = A[m];                             /* mov */
        A[m] = A[0];                            /* mov */
        A[0] = aux;                             /* mov */ s.mov += 3;
        m = m - 1;
        heapify(A, 0, m, &s);
    }
    return s;
}

/* Insertion Sort ========================================================== */

sort insertion_sort(int * A, int n)
{
    int i, j, aux;
    sort s = { .cmp = 0, .mov = 0};

    for (i = 1; i < n; i++) {
        aux = A[i];                         /* mov */ s.mov ++;
        j = i - 1;
        while ((j >= 0) && (/* cmp */ s.cmp ++, aux < A[j])) {
            A[j + 1] = A[j];                /* mov */ s.mov ++;
            j--;
        }
        A[j + 1] = aux;                     /* mov */ s.mov ++;
    }
    return s;
}

/* Merge Sort ============================================================== */

void merge2(int * A, int * B, int p, int q, int r, sort *s)
{
    int i, j, k;
    if (/* cmp */ s->cmp ++, A[q] > A[q + 1]) {
        i = p;
        j = q + 1;
        k = p;
        while ((i <= q) && (j <= r))
            if (/* cmp */ s->cmp ++, A[i] <= A[j]) {
                B[k] = A[i];                /* mov */ s->mov ++;
                k = k + 1;
                i = i + 1;
            }
        else {
            B[k] = A[j];                    /* mov */ s->mov ++;
            k = k + 1;
            j = j + 1;
        }
        while (i <= q) {
            B[k] = A[i];                    /* mov */ s->mov ++;
            k = k + 1;
            i = i + 1;
        }
        while (j <= r) {
            B[k] = A[j];                    /* mov */ s->mov ++;
            k = k + 1;
            j = j + 1;
        }
    }
}

void merge(int * A, int p, int q, int r, sort *s) {
    int i, j, k;
    int * B;
    B = (int *) malloc((r - p + 1) * sizeof(int));

    for (i = p; i <= q; i++)
        B[i - p] = A[i];                    /* mov */ s->mov ++;
    for (j = q + 1; j <= r; j++)
        B[r + q + 1 - j - p] = A[j];        /* mov */ s->mov ++;
    i = p;
    j = r;
    for (k = p; k <= r; k++)
        if (/* comp */ s->cmp ++, B[i - p] <= B[j - p]) {
            A[k] = B[i - p];                /* mov */ s->mov ++;
            i = i + 1;
        }
    else {
        A[k] = B[j - p];                    /* mov */ s->mov ++;
        j = j - 1;
    }
    free(B);
}

sort merge_sort(int * A, int n) {
    int p, q, r;
    int jump = 1;
    sort s = { .cmp = 0, .mov = 0};

    while (jump < n) {
        p = 0;
        while (p + jump < n) {
            r = p + 2 * jump - 1;
            if (r >= n)
                r = n - 1;
            q = p + jump - 1;
            merge(A, p, q, r, &s);
            p = p + 2 * jump;
        }
        jump = 2 * jump;
    }
    return s;
}

/* Quick Sort ============================================================== */

void ternary_partition(int * A, int p, int r, int * q, int * t, sort *s)
{
    int i, j, k, x, aux;
    x = A[r];                               /* mov */ s->mov ++;
    i = p - 1;
    j = p;
    k = r;
    while (j <= k - 1) {
        if (/* cmp */ s->cmp ++, A[j] < x) {
            i = i + 1;
            aux = A[i];                     /* mov */
            A[i] = A[j];                    /* mov */
            A[j] = aux;                     /* mov */ s->mov += 3;
        } else if (/* cmp */ s->cmp ++, A[j] == x) {
            k = k - 1;
            aux = A[k];                     /* mov */
            A[k] = A[j];                    /* mov */
            A[j] = aux;                     /* mov */ s->mov += 3;
            j = j - 1;
        }
        j = j + 1;
    }
    (* q) = i + 1;
    for (j = k; j <= r; j++) {
        i = i + 1;
        aux = A[i];                         /* mov */
        A[i] = A[j];                        /* mov */
        A[j] = aux;                         /* mov */ s->mov += 3;
    }
    (* t) = i;
}

void _quick_sort(int * A, int p, int r, sort *s)
{
    int q, t;
    while (p < r) {
        ternary_partition(A, p, r, &q, &t, s);
        if (q - p < r - t) {
            _quick_sort(A, p, q - 1, s);
            p = t + 1;
        } else {
            _quick_sort(A, t + 1, r, s);
            r = q - 1;
        }
    }
}

sort quick_sort(int * A, int n)
{
    sort s = { .cmp = 0, .mov = 0};
    _quick_sort(A, 0, n - 1, &s);
    return s;
}

/* Selection Sort ========================================================== */

sort selection_sort(int * A, int n)
{
    int i, j, min, aux;
    sort s = { .cmp = 0, .mov = 0};

    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++)
            if (/* cmp */ s.cmp ++, A[j] < A[min])
                min = j;
        if (i != min) {
            aux = A[min];                   /* mov */
            A[min] = A[i];                  /* mov */
            A[i] = aux;                     /* mov */ s.mov += 3;
        }
    }
    return s;
}
