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
// �������Ψһ�Ĳ�������ָ���Ľ���������:���Ŀ�����
// �� "Notepad.exe",����ֵ�Ǹý��̵�ID��ʧ�ܷ���0
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
// �˺������������ FindProcess ����������Ŀ����̵�ID
// ��WIN API OpenPorcess ��ô˽��̵ľ��������TerminateProcess
// ǿ�ƽ����������
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
// �� Windows NT/2000/XP �п�����Ȩ�޲����������Ϻ���ʧ��
// ���ԡ�System Ȩ�����е�ϵͳ���̣��������
// �ñ�����ȡ�á�debug Ȩ�޼���,Winlogon.exe ��������ֹŶ :)
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
