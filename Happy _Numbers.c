/* 
Problem Statement
====================
Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: Starting with any positive integer, replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.

Example: 

Input: 19
Output: true
Explanation: 
1*1 + 9*9 = 82
8*8 + 2*2 = 68
6*6 + 8*8 = 100
1*1 + 0*0 + 0*0 = 1

Theory and Explanation
=========================

For the purposes of this explanation, we will use the following definition:

Given a positive integer n, the process of squaring n's digits and summing the squares will be referred to as 'square-summing' the number n. The result of this process will be referred to as the 'square-sum' of n.

Suppose that n is a positive integer with N digits. Then the square-sum of n is at most (81 * N). This is easy to see, since n has N digits, and the square of any digit is at most 81.

If n has 4 digits, then its square-sum is at most 81 * 4 = 324, and therefore has at most 3 digits.
If n has 5 digits, then its square-sum is at most 81 * 5 = 405, and has at most 3 digits.

Suppose n has 1,000,000 digits, and let n1 be its square-sum. then n1 is at most 81,000,000, which has 8 digits.
Since n1 has at most 8 digits, its square-sum n2, is at most 8*81 = 648.
Since n2 has at most 3 digits, its square-sum is at most 324.

It is easy to see that given any integer n, if we repeat the process of replacing n with its square-sum, then n will eventually become less than or equal to 324, after which it will always stay within that range.

After realizing this, I wrote some code to produce sequences of square-sums for all numbers from 1 to 324, and made the following observation:

===========================================================================================================

Main Observation: When we start with any positive integer n, and repeatedly replace it with its square-sum, exactly one of the following scenarios occurs:

1) The sequence will eventually reach 1, and stay there.
2) The sequence will get stuck in a cycle that contains the number 4.

===========================================================================================================

Proof: For all integers between 1 and 324, the observation holds as can easily be verified with some simple code. Since all positive integers will eventually land in this range, the conclusion follows.

===========================================================================================================

*/

bool isHappy(int n){
    // variable to store the squar-sum computed at each step.
    int num = 0;
    
    while(true){
        // Compute the square-sum of n, and store the result in num.
        while(n > 0){
            num += (n % 10) * (n % 10);
            n /= 10;
        }
        
        // From the main observation above, we can continue computing the sequence of square-sums until
        // num == 1, in which case we return true, or
        // num == 4, in which case we return false.
        if(num == 1)
            return true;
        else if(num == 4)
            return false;
        
        // Set n to the value of num, and reset num to 0.
        n = num;
        num = 0;
    }
}

