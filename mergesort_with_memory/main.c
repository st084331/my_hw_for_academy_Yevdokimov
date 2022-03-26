#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mergesort(void *base, size_t num, size_t size, int (*compar)(const void *, const void *)) {
    int i, p, p1, p2, d;
    int len1 = num / 2;
    int len2 = num - len1;
    unsigned char *arr = (unsigned char *) base;
    unsigned char *l;
    unsigned char *r;
    if (num <= 1) return 1;
    l = (unsigned char *) malloc(size * len1);
    r = (unsigned char *) malloc(size * len2);
    for (i = 0; i < len1 * size; i++) l[i] = arr[i];
    p = 0;
    for (; i < num * size; i++) r[p++] = arr[i];
    mergesort(l, len1, size, compar);
    mergesort(r, len2, size, compar);
    p = 0;
    p1 = 0;
    p2 = 0;
    while ((p1 < len1) | (p2 < len2)) {
        if (p1 == len1) d = 2;
        else if (p2 == len2) d = 1;
        else if (compar((void *) (l + p1 * size), (void *) (r + p2 * size)) < 0) d = 1;
        else d = 2;
        unsigned char *tt;
        if (d == 1) tt = l + p1 * size;
        else tt = r + p2 * size;
        for (int i = 0; i < size; i++) arr[p * size + i] = tt[i];
        p++;
        if (d == 1) p1++;
        else p2++;
    }
    free(l);
    free(r);
    return 1;
}

int cmp(const void *v1, const void *v2) {
    int n1 = *(int *) v1;
    int n2 = *(int *) v2;
    if (n1 > n2) return 1;
    if (n1 < n2) return -1;
    return 0;
}

int main() {
    int i, n;
    n = 8;
    int a[n];
    printf("Initial:\n");
    for (i = 0; i < n; i++) {
        a[i] = rand() % 10;

        printf("%d ", a[i]);
    }
    printf("\n");
    mergesort(&a, n, sizeof(int), cmp);
    printf("Sorted:\n");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}
