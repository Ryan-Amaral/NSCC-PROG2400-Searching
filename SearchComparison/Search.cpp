//  File: Search.cpp
//	Purpose: Contains searching algorithms for int array.
//  Project: SearchComparison
//  Author: Ryan Amaral
//  Created On: April 2, 2016

#include "Search.h"

/// Sequential search on an int array.
/// Returns index of num, -1 if not found.
int Search::sequentialSearch(const int* intArr, const unsigned int length, const int num)
{
	for (unsigned int i = 0; i < length; ++i)
	{
		// found numbmer
		if (intArr[i] == num)
		{
			return i;
		}
	}

	// num not found
	return -1;
}

/// Binary search on an int array.
/// Returns index of num, -1 if not found.
int Search::binarySearch(const int* intArr, const unsigned int length, const int num)
{
	unsigned int left = 0;
	int right = length - 1;
	int middle = (left + right) / 2;

	while (true)
	{
		// not found
		if (left > right)
		{
			return -1;
		}

		// number found
		if (intArr[middle] == num)
		{
			return middle;
		}
		// number too small
		else if (intArr[middle] < num)
		{
			left = middle + 1;
		}
		// number too big
		else if (intArr[middle] > num)
		{
			right = middle - 1;
		}

		middle = (left + right) / 2;
	}
}