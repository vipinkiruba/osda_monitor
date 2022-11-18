#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include<iostream>
#include< windows.h >
using namespace std;


#define BUF_SIZE 1
TCHAR szName[] = TEXT("Global\\MyFileMappingObject");
TCHAR szMsg[] = TEXT("1");

int _tmain()
{

    cout << "osda started..."<<endl;

    HANDLE hMapFile;
    LPCTSTR pBuf;

    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // use paging file
        NULL,                    // default security
        PAGE_READWRITE,          // read/write access
        0,                       // maximum object size (high-order DWORD)
        BUF_SIZE,                // maximum object size (low-order DWORD)
        szName);                 // name of mapping object

    if (hMapFile == NULL)
    {
        _tprintf(TEXT("Could not create file mapping object (%d).\n"),
            GetLastError());
        return 1;
    }
    pBuf = (LPTSTR)MapViewOfFile(hMapFile,   // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        BUF_SIZE);

    if (pBuf == NULL)
    {
        _tprintf(TEXT("Could not map view of file (%d).\n"),
            GetLastError());

        CloseHandle(hMapFile);

        return 1;
    }

    // start agara apo value 1 nu set paniruvan
    CopyMemory((PVOID)pBuf, szMsg, (_tcslen(szMsg) * sizeof(TCHAR)));
    cout << "osda sets its value as 1..." << endl;


    // osda processing data
    Sleep(10000);
    cout << "osda completed its process..." << endl;


    // end agara apo value 0 nu set paniruvan
    szMsg[0] = '0';
    CopyMemory((PVOID)pBuf, szMsg, (_tcslen(szMsg) * sizeof(TCHAR)));
    cout << "osda sets its value as 0..." << endl;


    //loop untill share data is 1 {
     
    // checking shared data(if true continue)
    //                     (else break)
    
    // }
    while (1) {
        Sleep(3000);
        cout << "checking pbuf == 1 ..." << endl;
        cout << "pbuf status : "<<pBuf[0] << endl;
        if (((int)pBuf[0]) - 48 == 1) {
            cout << "break" << endl;
            break;
        }
    }
    




    UnmapViewOfFile(pBuf);
    

    CloseHandle(hMapFile);

    cout << "restarting..." << endl;
    _getch();

    return 0;
}
