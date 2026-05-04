#include <stdio.h>
#include <string.h>

/**
 * Problem: Cyclic Substring Maximum Sum
 * Finds the max sum of unique characters in a cyclic string.
 */

int main()
{
    char s[100005];
    if (scanf("%s", s) != 1)
        return 0;

    int n = strlen(s);

    // To handle the cyclic wrap-around, we treat the string as 2n length.
    // However, since we can't have more than 26 unique characters,
    // we only need to check windows up to length 26 starting from any index 0 to n-1.

    long long maxSum = 0;

    for (int i = 0; i < n; i++)
    {
        int visited[26] = {0}; // Track characters in the current window
        long long currentSum = 0;

        for (int j = 0; j < 26; j++)
        {
            // Use modulo to wrap around the original string index
            int currentIndex = (i + j) % n;
            int charVal = s[currentIndex] - 'a' + 1;
            int charIdx = s[currentIndex] - 'a';

            // If we hit a duplicate or have seen all n characters, stop the window
            if (visited[charIdx] || j >= n)
            {
                break;
            }

            visited[charIdx] = 1;
            currentSum += charVal;

            if (currentSum > maxSum)
            {
                maxSum = currentSum;
            }
        }

        // Optimization: If we found the max possible sum (a-z = 351), we can stop.
        if (maxSum == 351)
            break;
    }

    printf("%lld\n", maxSum);

    return 0;
}