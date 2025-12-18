\## 1611. Minimum One Bit Operations to Make Integers Zero



\*\*Difficulty:\*\* Hard  

\*\*Topics:\*\* Bit Manipulation  

\*\*Company Tags:\*\* LeetCode  



---



\### Problem Statement



You are given an integer `n`. You must transform it into `0` using the following operations any number of times:



1\. Change the rightmost (0th) bit in the binary representation of `n`.

2\. Change the `i`th bit in the binary representation of `n` \*\*only if\*\*:

&nbsp;  - The `(i-1)`th bit is set to `1`, and

&nbsp;  - All bits from `(i-2)` down to `0` are set to `0`.



Return the \*\*minimum number of operations\*\* required to transform `n` into `0`.



---



\### Example



\*\*Input\*\*

&nbsp; n=3

&nbsp;



\*\*Output\*\*

&nbsp; 2





\*\*Explanation\*\*



&nbsp;Binary representation of `3` is `11`:

&nbsp;

&nbsp; - 11 -> 01 (using operation 2)

&nbsp; - 01 -> 00 (using operation 1)





Total operations = `2`.



---



\### Key Insight



This problem follows a \*\*Gray Code\*\* pattern.



The minimum number of operations required to convert `n` to `0` is equal to the XOR of all prefixes of `n` while right-shifting it until it becomes zero.



---



\### Algorithm



1\. Initialize `result = 0`

2\. While `n > 0`:

&nbsp;  - `result ^= n`

&nbsp;  - Right shift `n` by 1

3\. Return `result`



---



\### C++ Solution



```cpp



&nbsp;	class Solution {

public:

    int minimumOneBitOperations(int n) {

        int res = 0;

        while (n > 0) {

            res ^= n;

            n >>= 1;

        }

        return res;

    }};



```



\## Complexity Analysis



* Time Complexity: O(log n)



* Space Complexity: O(1)



\## Notes



* This solution avoids recursion and uses pure bit manipulation.



* The XOR accumulation models the optimal sequence of bit flips.



