// t6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include  <iomanip>
#include <fstream>
#include <math.h>
using namespace std;
const int L = 16;
const int N = 4;
const int K = 2;

ifstream infile;


int main()
{
	infile.open("input.txt");
	if (!infile)
	{
		cout << "File error";
		exit(1);
	}
	unsigned int x;
	int numSetDigits = N-1;
	int cache[N][K];
	int hit = 0;
	int miss = 0;
	while (infile >> hex >> x)
	{

		int tag = (x >> (4 + int(log2(double(N)))));
		int set = (x >> 4) & (N-1);
		if (cache[set][0] == tag)
		{
			hit++;
		}
		else if (cache[set][K-1] == tag)
		{
			hit++;
			cache[set][K-1] = cache[set][0]; //switch most recently accessed
			cache[set][0] = tag;
		}
		else
		{
			miss++;
			cache[set][K-1] = tag;
		}
		//cout << "Address: 0x" << setfill('0') << setw(4) << hex << x << " is in set: " << set << "\n";
		
	}

	infile.close();
	cout << "L = " << L << ". N = " << N << ". K = " << K << "\n";
	cout << "Hits: " << hit << "\nMisses: " << miss << "\n";
}

