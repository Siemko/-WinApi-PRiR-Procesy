#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

bool ifPrime(int num); //check if num is a prime number

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "** THIS IS MAIN PROCESS **";
	//Process & File Vars
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	SECURITY_ATTRIBUTES sap;
	ZeroMemory(&pi, sizeof(pi));
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&sap, sizeof(sap));
	si.cb = sizeof(si);
	sap.nLength = sizeof(sap);
	sap.bInheritHandle = TRUE;
	HANDLE hFile, hMutex;
	DWORD ile;

	stringstream cmdLine, primenums;
	string mutexName("mutex1");

	hFile = CreateFile("wyjscie.txt", FILE_ALL_ACCESS, 0, &sap, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	hMutex = CreateMutex(NULL, FALSE, mutexName.c_str());
	
	cmdLine << "Child.exe " << (DWORD)hFile << " " << mutexName;
	
	if (!CreateProcess(NULL, (char*)cmdLine.str().c_str(), NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		cout << "ERROR";
	}
	for (int i = 0; i < 500; ++i)
	{
		if (ifPrime(i))
		{
			cout << i << " ";
			primenums << i << " ";
			WaitForSingleObject(hMutex, INFINITE);
			WriteFile(hFile, primenums.str().c_str(), primenums.str().size(), &ile, NULL);
			ReleaseMutex(hMutex);
			primenums.str("");
		}
	}
	
	WaitForSingleObject(pi.hThread, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
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