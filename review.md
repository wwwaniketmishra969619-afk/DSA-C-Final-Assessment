## C2 Optimisation Report
- **Current Time Complexity:** $O(n^2)$ due to nested linear loops scanning every subarray start position. At $n = 1,000,000$, $10^{12}$ operations occur, triggering a TLE (Time Limit Exceeded).
- **Corrected Time Complexity:** $O(n)$ sliding window approach.
- **Corrected Space Complexity:** $O(1)$ auxiliary space.
- **Condition on Input:** All elements in the array $a$ must be non-negative ($a[i] \ge 0$), making the prefix sums monotonic and allowing the sliding window's left boundary to only move forward.