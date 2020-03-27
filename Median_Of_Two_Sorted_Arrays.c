/*
Problem Statement
====================
There are two sorted arrays nums1 and nums2 of size m and n respectively. Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)). You may assume nums1 and nums2 cannot be both empty.

Theory and Explanation
=========================

Main Observation #1: Suppose we have a set S of numbers and a positive integer k. Then removing the k smallest elements and the k largest elements from S will not change the median, provided that k is small enough so that the median element(s) is not removed from S.

---------------------------------

Main Observation #2: Suppose nums1 and nums2 are two arrays of numbers. If the median of nums1 is greater than or equal to the median of nums2, then the following statements hold (or, if the median of nums2 is greater, then similar statements hold):

i) All elements in nums1 that are to the right of the median element(s) of nums1, will also fall to the right of the combined median elements.
ii) All elements in nums2 that are to the left of the median element(s) of nums2, will also fall to the left of the combined median elements.
iii) By observation #1, if we remove an equal number of elements from the right of the nums1 median element(s) and from the left of the nums2 median element(s), then the combined median will not change.

---------------------------------

Example

==========

This example is best followed along while reading the code.
Suppose the two arrays are as follows:

nums1 = {1, 4, 6, 8, 9, 9, 15, 16, 17, 20, 21, 34}
nums2 = {2, 5, 6, 10, 11} 

The medians of these two arrays are 12 and 6 respectively. Since nums2 has the smaller median, we can remove the 2 rightmost elements of nums1 and the 2 leftmost elements of nums2.

nums1 = {1, 4, 6, 8, 9, 9, 15, 16, 17, 20}
nums2 = {6, 10, 11} 

Applying the same logic as above, we can remove 1 and 11 from the arrays.

nums1 = {4, 6, 8, 9, 9, 15, 16, 17, 20}
nums2 = {6, 10} 

Now that nums2 has been cut down to two elements, we can cut nums1 down to 3 elements in one step by removing 3 elements from either side.

nums1 = {9, 9, 15}
nums2 = {6, 10} 

We can now use the linear-time solution to find the median of the remaining elements. */

double median(int* nums, int first, int last){
    /* Helper function that returns the median of the subarray of nums, starting at index 'first' and ending at index 'last'. */
    
    // Count the number of elements and obtain the middle element
    int len = last - first + 1;
    int mid = first + (len / 2);
    
    if (len % 2 == 0){
        // If the subarray has even length, return the average of the two middle elements.
        return (nums[mid - 1] + nums[mid]) / 2.0;
    }
    else {
        // Otherwise return the middle element as a double.
        return (double)nums[mid];
    }
}

double findMedianSortedArraysLinear(int* nums1, int first1, int last1, int* nums2, int first2, int last2){
    /* Helper function that implements a linear time solution to the problem. This will be called from the main function, once the two arrays have been reduced to a combined total of at most 6 elements. */
    // Initialize indices.
    int i1 = first1;
    int i2 = first2;
    int i = 0;
    
    // Obtain the total number of elements and create a new array to store the combined elements of nums1 and nums2.
    int totalCount = last1 - first1 + last2 - first2 + 2;
    int nums[totalCount];
    
    // Combine the elements.
    for (int i = 0; i < totalCount; i++){
        if(i2 > last2 || (i1 <= last1 && nums1[i1] <= nums2[i2])){
            nums[i] = nums1[i1];
            i1 += 1;
        }
        else {
            nums[i] = nums2[i2];
            i2 += 1;
        }
    }
    
    // Return the median.
    return median(nums, 0, totalCount - 1);
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    /* Finds the median of the two arrays in logarithmic time, by iteratively cutting the number of elements roughly in half at each step. */
    
    // If nums2 contains more elements than nums1, interchange the two arrays.
    if (nums1Size < nums2Size){
        return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);
    }
    
    // Going forward, assume nums1 has more elements than nums2.
    // If nums2 is empty, return the median of nums1.
    if (nums2Size == 0)
        return median(nums1, 0, nums1Size - 1);
    
    // Indices for nums1.
    int i1 = 0;
    int j1 = nums1Size - 1;
    
    // Indices for nums2
    int i2 = 0;
    int j2 = nums2Size - 1;
    
    // Declare variables to store the medians of nums1 and nums2, and the number of elements to cut at each step.
    double med1, med2;
    int cutCount;
    
    // Continue cutting until nums2 is reduced to at most 2 elements.
    while (j2 - i2 > 1){
        // Compute half the number of elements to any one side of the median of nums2.
        // Since nums2 has at most as many elements as nums1, this will be the number of elements to cut from either side of the combined median.
        // For example, if nums2 has 3 elements, then there is 1 element to either side of the median, and so cutCount will be set to 1. If nums2 has 6 elements, then cutCount will be set to 2.
        cutCount = (j2 - i2) / 2;
        
        // Compute the medians of nums1 and nums2.
        med1 = median(nums1, i1, j1);
        med2 = median(nums2, i2, j2);
        
        // If the median of nums1 is greater than or equal to the median of nums2, then remove elements from the left of nums2 and the right of nums1.
        if (med1 >= med2){
            i2 += cutCount;
            j1 -= cutCount;
        }
        // Otherwise remove elements from the left of nums1 and the right of nums2.
        else {
            i1 += cutCount;
            j2 -= cutCount;
        }
    }
    
    // At this point, nums2 has at most 2 elements.
    // If nums1 still contains more than 4 elements, it can now be cut down to at most 4 elements in just one step, by keeping only the middle 3 or 4 elements.
    cutCount = ((j1 - i1 + 1) / 2) - 2;
    
    if (cutCount > 0){
        i1 += cutCount;
        j1 -= cutCount;
    }
    
    // At this point, the combined number of elements in nums1 and nums2 is at most 6, so we can apply the linear time algorithm to finish the solution.
    return findMedianSortedArraysLinear(nums1, i1, j1, nums2, i2, j2);
}

