#include "algorithm.h"

int64_t Binomial(int64_t n, int64_t k)
{
    if (k > n)
        return 0;

    if (k > n - k)
        k = n - k;

    int64_t result = 1;
    for (int64_t i = 0; i < k; i++)
    {
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}

int64_t MultisetNumber(int64_t n, int64_t k)
{
    return Binomial(n + k - 1, n);
}
