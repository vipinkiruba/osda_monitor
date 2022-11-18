#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include< windows.h >
#pragma comment(lib, "user32.lib")
#include<iostream>
using namespace std;

#define BUF_SIZE 1
TCHAR szName[] = TEXT("Global\\MyFileMappingObject");
TCHAR szMsg[] = TEXT("0");

int _tmain()
{

    // doing all his work

    HANDLE hMapFile;
    LPCTSTR pBuf;

    hMapFile = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,   // read/write access
        FALSE,                 // do not inherit the name
        szName);               // name of mapping object

    if (hMapFile == NULL)
    {
        _tprintf(TEXT("Could not open file mapping object (%d).\n"),
            GetLastError());
        cin.get();
        return 1;
    }

    pBuf = (LPTSTR)MapViewOfFile(hMapFile, // handle to map object
        FILE_MAP_ALL_ACCESS,  // read/write permission
        0,
        0,
        BUF_SIZE);

    if (pBuf == NULL)
    {
        _tprintf(TEXT("Could not map view of file (%d).\n"),
            GetLastError());

        CloseHandle(hMapFile);
        cin.get();
        return 1;
    }

    wcout << (int)pBuf[0]<<endl;
    //loop untill value is 1

    // if value is 0 na break loop and
     
    // processing all data

    Sleep(15000);


    wcout << (int)pBuf[0] << endl;
    cout << "monitor stopping..." << endl;



    // update it as 1;
    cout << "monitor sending signal as 1..." << endl;
    szMsg[0] = '1';
    CopyMemory((PVOID)pBuf, szMsg, (_tcslen(szMsg) * sizeof(TCHAR)));


    cin.get();

    UnmapViewOfFile(pBuf);

    CloseHandle(hMapFile);



    return 0;
}
