#!/usr/bin/env python3
"""
Optimized implementation of the QuickSort algorithm.

This implementation includes several optimizations:
- Median-of-three pivot selection to avoid worst-case behavior
- Insertion sort for small subarrays (more efficient than quicksort for small n)
- Tail recursion elimination to minimize stack space usage
- Hoare's partitioning scheme for fewer swaps
"""

def insertion_sort(arr, lo, hi):
    """
    Implementation of insertion sort for small subarrays.
    
    Args:
        arr: The array to sort
        lo: The starting index
        hi: The ending index (inclusive)
    """
    for i in range(lo + 1, hi + 1):
        key = arr[i]
        j = i - 1
        while j >= lo and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key

def median_of_three(arr, lo, hi):
    """
    Selects the median of the first, middle, and last elements as pivot.
    
    Args:
        arr: The array from which to select the pivot
        lo: The starting index
        hi: The ending index
    
    Returns:
        The index of the median value
    """
    mid = lo + (hi - lo) // 2
    
    # Sort the three values
    if arr[lo] > arr[mid]:
        arr[lo], arr[mid] = arr[mid], arr[lo]
    if arr[lo] > arr[hi]:
        arr[lo], arr[hi] = arr[hi], arr[lo]
    if arr[mid] > arr[hi]:
        arr[mid], arr[hi] = arr[hi], arr[mid]
    
    # Return the index of the median (middle)
    return mid

def hoare_partition(arr, lo, hi):
    """
    Hoare's partitioning scheme, more efficient than Lomuto's.
    
    Args:
        arr: The array to partition
        lo: The starting index
        hi: The ending index
    
    Returns:
        The new partition index
    """
    # Select pivot using median-of-three
    pivot_idx = median_of_three(arr, lo, hi)
    pivot = arr[pivot_idx]
    
    # Move pivot to the beginning
    arr[lo], arr[pivot_idx] = arr[pivot_idx], arr[lo]
    
    # Partition
    i = lo + 1
    j = hi
    
    while True:
        # Find elements that are in the wrong partition
        while i <= j and arr[i] < pivot:
            i += 1
        while i <= j and arr[j] > pivot:
            j -= 1
            
        if i >= j:
            break
            
        # Swap elements that are in wrong partitions
        arr[i], arr[j] = arr[j], arr[i]
        i += 1
        j -= 1
    
    # Move pivot to its final position
    arr[lo], arr[j] = arr[j], arr[lo]
    
    return j

def quicksort(arr, lo=0, hi=None):
    """
    Optimized quicksort implementation with:
    - Median-of-three pivot selection
    - Insertion sort for small subarrays
    - Tail recursion elimination
    
    Args:
        arr: The array to sort
        lo: The starting index
        hi: The ending index
    """
    if hi is None:
        hi = len(arr) - 1
    
    # Optimize stack space using a loop instead of two recursive calls
    while lo < hi:
        # Use insertion sort for small subarrays
        if hi - lo < 10:
            insertion_sort(arr, lo, hi)
            break
            
        # Partition the array
        p = hoare_partition(arr, lo, hi)
        
        # Recursively sort the smaller partition
        # Handle the larger partition with tail recursion elimination
        if p - lo < hi - p:
            quicksort(arr, lo, p - 1)
            lo = p + 1
        else:
            quicksort(arr, p + 1, hi)
            hi = p - 1

def sort(arr):
    """
    Public sorting function that applies quicksort to the input array.
    
    Args:
        arr: The array to sort
        
    Returns:
        The sorted array (sorted in-place)
    """
    if not arr:
        return arr
        
    quicksort(arr)
    return arr

# Test cases
if __name__ == "__main__":
    import random
    import time
    import copy
    
    def test_sort(arr_size, num_tests=5):
        print(f"Testing with array size: {arr_size}")
        total_time = 0
        
        for i in range(num_tests):
            # Generate random array
            arr = [random.randint(-1000, 1000) for _ in range(arr_size)]
            arr_copy = copy.deepcopy(arr)
            
            # Time our implementation
            start = time.time()
            sorted_arr = sort(arr)
            end = time.time()
            elapsed = end - start
            total_time += elapsed
            
            # Verify correctness
            assert sorted(arr_copy) == sorted_arr, "Sorting failed!"
            
            print(f"  Test {i+1}: {elapsed:.6f} seconds")
        
        print(f"Average time: {total_time/num_tests:.6f} seconds")
        print("All tests passed!")
        print("-" * 40)
    
    # Test with various array sizes
    test_sort(100)
    test_sort(1000)
    test_sort(10000)
    
    # Test edge cases
    print("Testing edge cases")
    
    # Empty array
    assert sort([]) == [], "Empty array test failed"
    
    # Single element
    assert sort([5]) == [5], "Single element test failed"
    
    # Already sorted
    assert sort([1, 2, 3, 4, 5]) == [1, 2, 3, 4, 5], "Already sorted test failed"
    
    # Reverse sorted
    assert sort([5, 4, 3, 2, 1]) == [1, 2, 3, 4, 5], "Reverse sorted test failed"
    
    # Duplicate elements
    assert sort([3, 1, 4, 1, 5, 9, 2, 6, 5]) == [1, 1, 2, 3, 4, 5, 5, 6, 9], "Duplicates test failed"
    
    print("All edge cases passed!")