//  File: Source.cpp
//	Purpose: Main driver file.
//  Project: SearchComparison
//  Author: Ryan Amaral
//  Created On: April 2, 2016

#include "Search.h"
#include <iostream>
#include <conio.h>
#include <ctime>

using namespace std;

int main()
{
	const unsigned int LENGTH = 10000;
	// create the ints
	static int* intArr = new int[LENGTH];
	for (unsigned int i = 0; i < LENGTH; ++i)
	{
		intArr[i] = i + 1;
	}

	cout << "Comparison of Sequential and binary search on " << LENGTH << " numbers." << endl <<
		"Press any key to continue." << endl;
	_getch();

	// variables for timing
	double start;
	double durationSeq;
	double durationBin;
	double totalDurationSeq = 0;
	double totalDurationBin = 0;

	start = clock();
	for (int i = 0; i < LENGTH; ++i)
	{
		/*// time sequential search
		start = clock();
		Search::sequentialSearch(intArr, LENGTH, i + 1);
		durationSeq = (clock() - start) / CLOCKS_PER_SEC; // finish timer
		totalDurationSeq += durationSeq;

		// time binary search
		start = clock();
		Search::binarySearch(intArr, LENGTH, i + 1);
		durationBin = (clock() - start) / CLOCKS_PER_SEC; // finish timer
		totalDurationBin += durationBin;

		cout << "Seq: " << durationSeq << "s     " <<
			"Bin: " << durationBin << "s" << endl;*/

		Search::sequentialSearch(intArr, LENGTH, i + 1);
	}
	totalDurationSeq = (clock() - start) / CLOCKS_PER_SEC; // finish timer

	start = clock();
	for (int i = 0; i < LENGTH; ++i)
	{
		Search::binarySearch(intArr, LENGTH, i + 1);
	}
	totalDurationBin = (clock() - start) / CLOCKS_PER_SEC; // finish timer

	// print totals and averages
	cout << endl << "Total Times:" << endl <<
		"Sequential: " << totalDurationSeq << "s     " <<
		"Binary: " << totalDurationBin << "s" << endl << endl <<
		"Average Times:" << endl <<
		"Sequential: " << totalDurationSeq / (double)LENGTH << "s     " <<
		"Binary: " << totalDurationBin / (double)LENGTH << "s";

	_getch();

	delete[] intArr;
}