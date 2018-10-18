// t3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <ctime>
#include "t3.h"

//global variables for calculating reg windows usage
int wused, swp, cwp, numOverflows, numUnderflows = 0;
int maxDepth = -1;
const int NWINDOWS = 6;

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
	checkforOverflow();
	int returnVal;
	if (x == 0) {
		returnVal = y + 1;
	}
	else if (y == 0) {
		returnVal = ackermann(x - 1, 1);
	}
	else {
		returnVal = ackermann(x - 1, ackermann(x, y - 1));
	}
	checkforUnderflow();
	return returnVal;
}


int main()
{
	
	int ans = ackermannWindows(3, 6);
	std::cout << "NumOverflows = " << numOverflows << "\nNumUnderflows = "
		<< numUnderflows << "\nMaxDepth = " << maxDepth << "\n";
	/*time_t start = time(NULL);
    std::cout << "Start time = " << start << "\n";
	for (int i = 0; i <= 10000; i++)
	{
		int ans = ackermann(3, 6);
	}
	time_t end = time(NULL);
	std::cout << "End time = " << end << "\n";
	double duration = difftime(end, start);
	std::cout << "Duration = " << duration << "\n";
	std::cout << "Execution time 1 call = " << duration / 10000 << "\n";*/
}

