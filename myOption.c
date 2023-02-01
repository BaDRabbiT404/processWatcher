#include "header.h"

void processWatcher() {
	PROCESSENTRY32 pe;
	HANDLE hSnap = NULL;


	while (TRUE)
	{
		hSnapshot = CreateToolhelp32Snapshot(
			TH32CS_SNAPPROCESS, 0);
		if (INVALID_HANDLE_VALUE == hSnapshot) {
			CloseHandle(hSnapshot);
			MessageBox(NULL, L"INVALID_HANDLE_VALUE", L"Info", MB_ICONEXCLAMATION);
			ExitProcess(0);
		}

		peProcessEntry.dwSize = sizeof(PROCESSENTRY32);
		Process32First(hSnapshot, &peProcessEntry);
		do {
			if ((!wcscmp(pe.szExeFile, L"taskmgr.exe")) || (!wcscmp(pe.szExeFile, L"processhacker.exe")))
			{
				CloseHandle(hSnapshot);
				//MessageBox(NULL, L"DETECTED Task manager!!! Close process!!", L"Info", MB_ICONEXCLAMATION);
				ExitProcess(0);
			}

		} while (Process32Next(hSnapshot, &peProcessEntry));

		CloseHandle(hSnapshot);
	}
}
