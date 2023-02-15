#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <string>

uint64_t ShAllow = 0xDCAB8;

DWORD GetProcessId(const char* cProcessName)
{
	DWORD dwProcessId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnap && hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry))
		{
			do
			{
				if (!_stricmp(procEntry.szExeFile, cProcessName))
				{
					dwProcessId = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));
		}
		CloseHandle(hSnap);
	}
	return dwProcessId;
}

uint64_t GetBase(DWORD procID, const char* name)
{
	MODULEENTRY32 ModuleEntry = { 0 };
	HANDLE SnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procID);

	if (!SnapShot) return NULL;

	ModuleEntry.dwSize = sizeof(ModuleEntry);

	if (!Module32First(SnapShot, &ModuleEntry)) return NULL;

	do
	{
		if (strcmp(ModuleEntry.szModule, name) == 0)
		{
			CloseHandle(SnapShot);
			return reinterpret_cast<uint64_t>(ModuleEntry.modBaseAddr);
		}
	} while (Module32Next(SnapShot, &ModuleEntry));

	CloseHandle(SnapShot);
	return NULL;
}

int shbypass23()
{
	SetConsoleTitleA(("External ScriptHookV Bypass Speedy#5418"));

	DWORD dwProcessId = 0;

	std::string sProcessName = "FiveM_GTAProcess.exe";

	do
	{
		dwProcessId = GetProcessId(sProcessName.c_str());
		Sleep(1000);

	}

	while (!dwProcessId);

	std::cout << ("Found (") << sProcessName.c_str() << ") " << "Pid(" << dwProcessId << ") " << ("Enabling ScriptHookV.") << std::endl;

	std::cout << ("ScriptHookV Enabled") << std::endl;

	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);

	if (handle)
	{
		uint64_t Bypass = GetBase(dwProcessId, ("gta-core-five.dll"));

		void* AllowScriptHook = (BYTE*)(Bypass + ShAllow);

		while (true)
		{
			Sleep(1); // Added this since someone started complaining about CPU usage 

			if (Bypass)
			{
				bool ShAllowed = true;

				WriteProcessMemory(handle, AllowScriptHook, &ShAllowed, sizeof(ShAllowed), NULL);
			}
		}

	}
	else
	{
		std::cout << (" Failed , Try turning antivirus off.") << std::endl;
	}

	CloseHandle(handle);

	return 0;

}