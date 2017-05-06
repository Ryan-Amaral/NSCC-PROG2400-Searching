//  File: Search.h
//	Purpose: Header file for Search.cpp
//  Project: SearchComparison
//  Author: Ryan Amaral
//  Created On: April 2, 2016

#ifndef _SEARCH_H
#define _SEARCH_H

class Search
{
private:
public:
	static int sequentialSearch(const int* intArr, const unsigned int length, const int num);
	static int binarySearch(const int* intArr, const unsigned int length, const int num);
};

#endif