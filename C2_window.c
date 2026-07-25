#include <stdio.h>

int longest_block(int a[], int n, long long L) {
    int best = 0;
    int left = 0;
    long long sum = 0;

    for (int right = 0; right < n; right++) {
        sum += a[right];

        while (sum > L && left <= right) {
            sum -= a[left];
            left++;
        }

        if ((right - left + 1) > best) {
            best = right - left + 1;
        }
    }

    return best;
}