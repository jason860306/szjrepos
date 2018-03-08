// ProcessUtil.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <Psapi.h>

#pragma comment(lib, "Psapi.lib")

DWORD FindProcess(const _TCHAR *strProcessName);
BOOL KillProcess(const _TCHAR *strProcessName);
BOOL GetDebugPriv();

int _tmain(int argc, _TCHAR* argv[])
{
    if (argc != 2)
    {
        _tprintf(TEXT("%s ProcName\n"), argv[0]);
        return -1;
    }
    const _TCHAR *pProcName = argv[1];
    DWORD dwProcId = 0;
    if (0 == (dwProcId = FindProcess(pProcName)))
    {
        _tprintf(TEXT("can't find process %s\n"), pProcName);
        return -1;
    }
    if (!KillProcess(pProcName))
    {
        _tprintf(TEXT("kill process %s failed\n"), pProcName);
        return -1;
    }
    getchar();
    return 0;
}

//
// FindProcess
// 这个函数唯一的参数是你指定的进程名，如:你的目标进程
// 是 "Notepad.exe",返回值是该进程的ID，失败返回0
//
DWORD FindProcess(const _TCHAR *strProcessName)
{
    DWORD aProcesses[1024], cbNeeded, cbMNeeded;
    HMODULE hMods[1024];
    HANDLE hProcess;
    _TCHAR szProcessName[MAX_PATH] = { TEXT('\0') };

    if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
    {
        return 0;
    }
    for(int i=0; i< (int)(cbNeeded / sizeof(DWORD)); i++)
    {
        hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);
        EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbMNeeded);
        GetModuleFileNameEx( hProcess, hMods[0], szProcessName,sizeof(szProcessName));
        if(_tcsstr(szProcessName, strProcessName))
        {
            _tprintf(_T("%d\t%s\n"), aProcesses[i], szProcessName);
            return(aProcesses[i]);
        }
    }

    return 0;
}

//
// Function: ErrorForce
// 此函数中用上面的 FindProcess 函数获得你的目标进程的ID
// 用WIN API OpenPorcess 获得此进程的句柄，再以TerminateProcess
// 强制结束这个进程
//
BOOL KillProcess(const _TCHAR *strProcessName)
{
    // When the all operation fail this function terminate the "winlogon" Process for force exit the system.
    HANDLE hYourTargetProcess = OpenProcess(PROCESS_QUERY_INFORMATION |   // Required by Alpha
        PROCESS_CREATE_THREAD     |   // For CreateRemoteThread
        PROCESS_VM_OPERATION      |   // For VirtualAllocEx/VirtualFreeEx
        PROCESS_VM_WRITE,             // For WriteProcessMemory
        FALSE, FindProcess(strProcessName));
    if(hYourTargetProcess == NULL)
    {
        return FALSE;
    }
    if (!GetDebugPriv())
    {
        _tprintf(TEXT("opens the access token associated ")
            TEXT("with process: %s failed\n"), strProcessName);
        return FALSE;
    }
    BOOL bTerminate = FALSE;
    if (!(bTerminate = TerminateProcess(hYourTargetProcess, 0)))
    {
        _tprintf(TEXT("terminate process %s failed: %d\n"),
            strProcessName, GetLastError());
    }
    return bTerminate;
}

//
// GetDebugPriv
// 在 Windows NT/2000/XP 中可能因权限不够导致以上函数失败
// 如以　System 权限运行的系统进程，服务进程
// 用本函数取得　debug 权限即可,Winlogon.exe 都可以终止哦 :)
//
BOOL GetDebugPriv()
{
    HANDLE hToken;
    LUID sedebugnameValue;
    TOKEN_PRIVILEGES tkp;

    if (!OpenProcessToken(GetCurrentProcess(),
        TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
    {
        _tprintf(TEXT("OpenProcessToken failed: %d\n"), GetLastError());
        return FALSE;
    }

    if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &sedebugnameValue))
    {
        _tprintf(TEXT("LookupPrivilegeValue failed: %d\n"), GetLastError());
        CloseHandle(hToken);
        return FALSE;
    }

    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Luid = sedebugnameValue;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof tkp, NULL, NULL))
    {
        _tprintf(TEXT("AdjustTokenPrivileges failed: %d\n"), GetLastError());
        CloseHandle(hToken);
        return FALSE;
    }

    return TRUE;
}
