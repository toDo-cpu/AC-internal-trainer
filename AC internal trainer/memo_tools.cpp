#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <vector>

#include "memo_tools.h"
#include "pch.h"

//FindAdressWithOffsetsEx is for external 
//FindAdressWithOffsets is for internal
uintptr_t FindAdressWithOffsetsEx(HANDLE hproc, uintptr_t modBaseAdress, std::vector <unsigned int> offsets)
{
    uintptr_t addr = modBaseAdress;

    for (unsigned int i = 0; i < offsets.size(); i++)
    {

        //RRM (in , in , out , in , out)
        ReadProcessMemory(hproc, (BYTE*)addr, &addr, sizeof(addr), 0);
        addr += offsets[i];
    }

    return addr;
}
uintptr_t FindAdressWithOffsets(uintptr_t modBaseAdress, std::vector <unsigned int> offsets)
{
    uintptr_t addr = modBaseAdress;

    for (unsigned int i = 0; i < offsets.size(); i++)
    {
        addr = *(uintptr_t*)addr;
        addr += offsets[i];
    }

    return addr;
}

BOOL PatchEx(DWORD* dst, BYTE* src, unsigned int size, HANDLE hProcess)
{
    DWORD oldPRotect;

    if (VirtualProtectEx(hProcess, dst, size, PAGE_EXECUTE_READWRITE, &oldPRotect) == 0)
    {
        return false;
    }

    if (WriteProcessMemory(hProcess, dst, src, size, 0) == 0)
    {
        return false;
    }

    if (VirtualProtectEx(hProcess, dst, size, oldPRotect, &oldPRotect) == 0)
    {
        return false;
    }

    return true;
}

BOOL NopEx(DWORD* dst, unsigned int size, HANDLE hProcess)
{
    BOOL result = false;
    BYTE* nopArray = new BYTE[size];

    memset(nopArray, 0x90, size);

    if (PatchEx(dst, nopArray, size, hProcess))
    {
        result = true;
    }
    
    delete[] nopArray;
    return result;
}

BOOL Patch(char* dst, char* src, unsigned int size)
{
    DWORD oldprotect;

    if (VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect) == 0)
    {
        return false;
    }

    memcpy_s(dst , size , src , size);

    if(VirtualProtect(dst, size, oldprotect, &oldprotect) == 0)
    {
        return false;
    }

    return true;
}

BOOL Nop(DWORD* dst, unsigned int size)
{
    BOOL result = false;
    BYTE* nopArray = new BYTE[size];

    memset(nopArray, 0x90, size);

    if (Patch((char*)dst, (char*)nopArray, size))
    {
        result = true;
    }

    return result;
}