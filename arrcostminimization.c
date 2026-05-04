#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void *a, const void *b)
{
    long long arg1 = *(const long long *)a;
    long long arg2 = *(const long long *)b;
    if (arg1 < arg2)
        return -1;
    if (arg1 > arg2)
        return 1;
    return 0;
}

int main()
{
    int N;
    if (scanf("%d", &N) != 1)
        return 0;

    long long *A = (long long *)malloc(N * sizeof(long long));
    for (int i = 0; i < N; i++)
    {
        scanf("%lld", &A[i]);
    }

    long long K;
    scanf("%lld", &K);

    // 1. Check if transformation is possible
    // All elements must have the same remainder when divided by K
    long long target_rem = A[0] % K;
    // Handle negative remainders if any (though constraints say A[i] >= 1)
    if (target_rem < 0)
        target_rem += K;

    for (int i = 1; i < N; i++)
    {
        long long current_rem = A[i] % K;
        if (current_rem < 0)
            current_rem += K;

        if (current_rem != target_rem)
        {
            printf("-1\n");
            free(A);
            return 0;
        }
    }

    // 2. Sort the array to find the median
    qsort(A, N, sizeof(long long), compare);

    // The median minimizes the sum of absolute differences
    long long median = A[N / 2];
    long long total_operations = 0;

    // 3. Calculate total operations to reach the median
    for (int i = 0; i < N; i++)
    {
        long long diff = llabs(A[i] - median);
        total_operations += (diff / K);
    }

    printf("%lld\n", total_operations);

    free(A);
    return 0;
}