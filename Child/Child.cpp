#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;

bool ifPrime(int num); //check if num is a prime number

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hFile, hMutex;
	DWORD ileb;
	int i, m, M;
	stringstream primeNums;
	cout << "SIEMA!" << endl;

	hFile = (HANDLE)argv[1];
	hMutex = OpenMutex(MUTEX_ALL_ACCESS,FALSE, argv[2]);
	for (int i = 501; i < 1000; ++i)
	{
		if (ifPrime(i))
		{
			cout << i << " ";
			primeNums << i << " ";
			WaitForSingleObject(hMutex, INFINITE);
			WriteFile(hFile, primeNums.str().c_str(), primeNums.str().size(), &ileb, NULL);
			ReleaseMutex(hMutex);
			primeNums.str("");
		}
	}
	CloseHandle(hMutex);
	_getch();
	return 0;
}

bool ifPrime(int num)
{
	int d;
	bool prime;
	prime = true;
	d = 2;
	while (d*d <= num && prime)
	{
		if (num%d == 0)
			prime = false;
		d++;
	}
	return prime;
}