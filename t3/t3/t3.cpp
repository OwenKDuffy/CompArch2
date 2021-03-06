// t3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <ctime>
#include "t3.h"

//global variables for calculating reg windows usage
int wused, swp, cwp = 0;
int maxDepth = -1;
int numCalls, numOverflows, numUnderflows, currentDepth = 0;
const int NWINDOWS = 16;

int checkforOverflow()
{
	if (wused == NWINDOWS)
	{
		//do releveant overflow stuff
		numOverflows++;
		swp++;
		swp %= NWINDOWS;
	}
	else
	{
		wused++;
	}
	cwp++;
	cwp %= NWINDOWS;
	return 0;
}

int checkforUnderflow()
{
	if (wused == 2) {
		swp--;
		swp %= NWINDOWS;
		//do relevant underflow things;
		numUnderflows++;
	}
	else {
		wused--;
	}
	cwp--;
	cwp %= NWINDOWS;
	return 0;
}
int ackermann(int x, int y)
{
	if (x == 0) {
		return y + 1;
	}
	else if (y == 0) {
		return ackermann(x - 1, 1);
	}
	else {
		return ackermann(x - 1, ackermann(x, y - 1));
	}
}

int ackermannWindows(int x, int y)
{
	numCalls++;
	currentDepth++;
	if (currentDepth > maxDepth)
	{
		maxDepth = currentDepth;
	}
	checkforOverflow();
	int returnVal;
	if (x == 0) {
		returnVal = y + 1;
	}
	else if (y == 0) {
		returnVal = ackermannWindows(x - 1, 1);
	}
	else {
		returnVal = ackermannWindows(x - 1, ackermannWindows(x, y - 1));
	}
	checkforUnderflow();
	currentDepth--;
	return returnVal;
}


int main()
{
	
	/*int ans = ackermannWindows(3, 6);
	std::cout << "NumCalls = " << numCalls << "\nNumOverflows = " << numOverflows << "\nNumUnderflows = "
		<< numUnderflows << "\nMaxDepth = " << maxDepth << "\nNumber of RegWindows = " << NWINDOWS << "\n";*/
	time_t start = time(NULL);
    std::cout << "start time = " << start << "\n";
	for (int i = 0; i <= 10000; i++)
	{
		int x = 3;
		int y = 6;
		int ans = ackermann(x, y);
	}
	time_t end = time(NULL);
	std::cout << "end time = " << end << "\n";
	double duration = difftime(end, start);
	std::cout << "duration = " << duration << "\n";
	std::cout << "execution time 1 call = " << duration / 10000 << "\n";
}

