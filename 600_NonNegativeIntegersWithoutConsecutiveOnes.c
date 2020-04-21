/*
Problem Statement
==================================================
Given a non-negative integer n, find the number of non-negative integers less than or equal to n, whose binary representations 
do NOT contain consecutive ones.

Example 1:
==========
Input: 5
Output: 5
Explanation: 
Here are the non-negative integers <= 5 with their corresponding binary representations:
0 : 0
1 : 1
2 : 10
3 : 11
4 : 100
5 : 101
Among them, only integer 3 disobeys the rule (two consecutive ones) and the other 5 satisfy the rule. 

Theory and Explanation
==================================================

Given an integer n >= 0, we will use the term 'NCO Count' to refer to the number of non-negative integers less than or equal 
to n, whose binary representations do NOT contain consecutive 1s. We will also say that an integer satisfies the 'NCO Property' 
if it contains no consecutive 1s. The table below shows the NCO Counts of numbers 0 to 15.

n	| binary| NCO Count	| Satisfies NCO Property?
=========================================================
0	|    0	| 1		| yes
1	|    1	| 2		| yes
2	|   10	| 3		| yes
3	|   11	| 3		| no
4	|  100	| 4		| yes
5	|  101	| 5		| yes
6	|  110	| 5		| no
7	|  111	| 5		| no
8	| 1000	| 6		| yes
9	| 1001	| 7		| yes
10	| 1010	| 8		| yes
11	| 1011	| 8		| no
12	| 1100	| 8		| no
13	| 1101	| 8		| no
14	| 1110	| 8		| no
15	| 1111	| 8		| no

We will first consider the case when n has the form (2 ^ m) - 1 for some integer m >= 0. For n = 0, 1, 3, 7, and 15, the NCO 
Counts are 1, 2, 3, 5, and 8 respectively. This looks like the sequence of Fibonacci numbers (except that it starts with 1 and 2,
instead of 1 and 1, but this is irrelevant to the problem at hand).

Observation 1: If m is an integer >= 0, then the NCO Count of (2 ^ m) - 1 is Fib(m + 1), where we assume that Fib(0) = Fib(1) = 1 
are the initial values in the Fibonacci sequence. Since all powers of 2 contain exactly one 1, it follows that the NCO Count of 
(2 ^ m) is 1 + Fib(m + 1).

The observation can be proven by strong induction. We will not show a full proof here. An example will suffice. We will prove that 
the NCO Count of 15 is Fib(5), using the fact that the NCO Counts of 7 and 3 are Fib(4) = 5 and Fib(3) = 3, respectively. The 
numbers that are <= 15 can be divided in to three groups:

1) Those that are <= 7
2) Those that are > 7, and <= 11
3) Those that are > 11, and <= 15

Group 1 contains Fib(4) = 5 numbers that satisfy the NCO Property. The numbers in group 3 all begin with '11', and therefore do not 
satisfy the NCO Property. The numbers in group 2 all start with '10', therefore removing the leftmost 1 will not create or eliminate 
any pairs of consecutve 1s. Removing the leftmost 1 from the numbers 1000, 1001, 1010, and 1011, leaves us with the numbers 0, 1, 
10, and 11, which are precisely the numbers <= 3. Out of these, there are Fib(3) = 3 numbers that satisfy the NCO Property. 
Therefore the NCO Count of 15 is Fib(4) + Fib(3) = Fib(5).

Now we generalize to all other non-negative integers. Given any such integer n that is not an exact power of 2, there exists a number 
m such that 2 ^ (m - 1) < n < 2 ^ m. The midpoint of this range, as well as all subsequent numbers, all start with '11'. None of them 
satisfy the NCO property, and will therefore have the same NCO Count as (2 ^ m) - 1. By observation 1, this count is Fib(m + 1). The 
numbers preceding the midpoint all begin with '10'. If n is one of these numbers, then n satisfies the NCO Property if and only if 
(n - 2 ^ m) also satisfies the NCO Property. Therefore we can recursively find the NCO Count of (n - 2 ^ m). This will give us a 
count of numbers, without consecutive 1s, in the range from 2 ^ (m - 1) (non-inclusive) to n (inclusive). To find the NCO Count of N, 
we merely add the NCO Count of 2 ^ (m - 1), which is Fib(m).

*/



int fib(int n){
    if (n == 0 || n == 1) return 1;
    int f1 = 1;
    int f2 = 1;
    int tmp;
    for(int i = 0; i < n - 1; i++){
        tmp = f1;
        f1 = f2;
        f2 = f1 + tmp;
    }
    return f2;
}

int findIntegers(int num){
    if(num == 0) return 1;
    if(num == 1) return 2;
    int p2 = 1;
    int m = 0;

    // Compute m.
    while (p2 < num) {p2 *= 2; m++;}
    
    // If num is a power of 2, use Observation 1.
    if(p2 == num) return 1 + fib(m + 1);
    
    // If num starts with '10', use the other observations above to compute the NCO Count of num.
    if(num - (p2 / 2) < (p2 / 4)) return fib(m) + findIntegers(num - (p2 / 2));

    // If num starts with '11', return fib(m + 1).
    return fib(m + 1);
}
