#include <stdio.h>
#include <windows.h>
#include <psapi.h>
#define VERIFY(arg) if (!(arg)) MSSError(#arg)

static void PrintLastError()
{
    DWORD err = GetLastError();
    if (err == 0)
        return;
    LPSTR msg = NULL;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),  (LPSTR)&msg, 0, NULL);
    printf("%s", msg);
    LocalFree(msg);
}

void GetCurrentProcessName(char* processName, uint32_t strMaxSize)
{
    HMODULE module;
    DWORD sizeNeeded;
    if (EnumProcessModules(GetCurrentProcess(), &module, sizeof(module), &sizeNeeded))
        GetModuleBaseName(GetCurrentProcess(), module, processName, strMaxSize);
}

static void Lowercase(char* str)
{
    for (int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
}

static void FPrintLastError()
{
    FILE* file = fopen("D:\\toto.txt", "a+");
    DWORD err = GetLastError();
    if (err == 0)
        return;
    LPSTR msg = NULL;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&msg, 0, NULL);
    fprintf(file, "%s", msg);
    LocalFree(msg);
    fclose(file);
}

static void MSSError(const char* msg)
{
    printf("Call failed: %s\n", msg);
    PrintLastError();
    DebugBreak();
}

static void MyPrintWindow(HWND win)
{
    printf("\n");
    static char buf[512];
    GetClassName(win, buf, 100);
    printf("    CLASS: %s \n", buf);
    GetWindowText(win, buf, 100);
    printf("   TEXT: %s \n", buf);
    DWORD dwPID = 0x0000000000000000;
    VERIFY(GetWindowThreadProcessId(win, &dwPID));
    printf("    PID: %i \n", dwPID);
    HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_VM_READ, FALSE, dwPID);
    VERIFY(process);
    static char pathStr[512];
    GetModuleFileNameEx(process, NULL, pathStr, 512);
    printf("    Filename: %s \n", pathStr);
}