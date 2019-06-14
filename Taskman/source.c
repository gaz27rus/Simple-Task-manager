#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

VOID PrintProcessList(HANDLE CONST hStdOut)
{
	PROCESSENTRY32 peProcessEntry;
	THREADENTRY32 peThreadEntry;
	HANDLE procSnapshot;
	HANDLE thrSnapshot;
	TCHAR szBuff[1024];
	DWORD dwTemp;

	procSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	thrSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);

	peProcessEntry.dwSize = sizeof(PROCESSENTRY32);
	peThreadEntry.dwSize = sizeof(THREADENTRY32);
	Process32First(procSnapshot, &peProcessEntry);
	
	do
	{
		_tprintf(TEXT("\n\n====================================================="));
		_tprintf(TEXT("\nPROCESS NAME:  %s"), peProcessEntry.szExeFile);
		_tprintf(TEXT("\n-------------------------------------------------------"));
		_tprintf(TEXT("\n  Process ID        = 0x%08X"), peProcessEntry.th32ProcessID);
		_tprintf(TEXT("\n  Thread count      = %d"), peProcessEntry.cntThreads);
		_tprintf(TEXT("\n  Parent process ID = 0x%08X"), peProcessEntry.th32ParentProcessID);
		_tprintf(TEXT("\n  Priority base     = %d"), peProcessEntry.pcPriClassBase);
	} while (Process32Next(procSnapshot, &peProcessEntry));

	Thread32First(thrSnapshot, &peThreadEntry);
	do
	{
		_tprintf(TEXT("\n\n====================================================="));
		_tprintf(TEXT("\n  Thread ID        = 0x%08X"), peThreadEntry.th32ThreadID);
		_tprintf(TEXT("\n  Owner Process      = %d"), peThreadEntry.th32OwnerProcessID);
	} while (Thread32Next(thrSnapshot, &peThreadEntry));

	CloseHandle(procSnapshot);
}

INT main() {
	HANDLE CONST hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	PrintProcessList(hStdOut);
	system("pause");
	ExitProcess(0);
	
}