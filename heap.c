/*
 * heapsort.c
 *
 *  Created on: Jul 1, 2013
 *      Author:
 */
#include <stdio.h>
#include <stdlib.h>
#include "employee.h"
#include "heap.h"

/**
 * Sorts a list of n employees in descending order
 *
 * @param	*A	Pointer to the list of employees
 * @param	n	Size of the heap
 */
void heapSort(Employee *A, int n)
{
	// Build a heap out of A
	buildHeap(A, n);

	// Move from the end of the array to the beginning
	while (n > 0) {
		// Swap the last element with the first
		swap(A + n - 1, A);
		// Decrease the length, since the element at the end is now in the right place
		n--;
		// Heapify the array again, to make sure it's still a heap
		for (int i = 0; i < n; i++) {
			heapify(A, i, n);
		}
	}
}

/**
 * Given an array A[], we want to get A[] into min-heap property
 * We only need to run heapify() on internal nodes (there are floor(n/2) of them)
 * and we need to run it bottom up (top-down cannot build a heap)
 *
 * @param	*A	Pointer to the list of employees
 * @param	n	Size of the heap
 */
void buildHeap(Employee *A, int n)
{
	// To build a heap, we need to heapify all the non-leaf nodes, so from n / 2 to 0
	for (int i = n / 2; i-- > 0;) {
		heapify(A, i, n);
	}
}

/**
 * We want to start with A[i] and percolate it downward
 * if it is greater than either left or right child.
 *
 * @param	*A	Pointer to the list of employees
 * @param	i	Index of current element to heapify
 * @param	n	Size of the heap
 */
void heapify(Employee *A, int i, int n)
{
	int left_child = 2 * (i + 1) - 1;
	int right_child = 2 * (i + 1);

	// Find the smaller of the two children
	int smaller;
	// Since the left child is always at a lower index, if it is out of bounds, they both are
	if (left_child >= n) return;
	// If the right child is out of bounds, the left one is obviously smaller
	if (right_child >= n) {
		smaller = left_child;
	} else if (A[left_child].salary < A[right_child].salary) {
		smaller = left_child;
	} else {
		smaller = right_child;
	}

  // If the smaller child is smaller than the parent, swap them
	if (A[smaller].salary < A[i].salary) {
		swap(A + smaller, A + i);
		// Recurse to see if the parent, moved down, is still larger than it's children
		heapify(A, smaller, n);
	}
}

/**
 * Swaps the locations of two Employees
 * @param *e1 An Employee
 * @param *e2 Another Employee to swap with
 */
void swap(Employee *e1, Employee *e2)
{
	Employee tmp = *e1;
	*e1 = *e2;
	*e2 = tmp;
}

/**
 * Outputs an array of Employees
 * @param	*A	Pointer to the list of employees
 * @param	n	Size of the list
 */
void printList(Employee *A, int n)
{
	for (int i = 0; i < n; i++) {
		printf("[id=%s sal=%d]", A[i].name, A[i].salary);
		if (i < n - 1) printf(", "); // We don't want a comma at the very end
	}
	printf("\n");
}
