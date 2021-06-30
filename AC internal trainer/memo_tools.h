#include <Windows.h>
#include <vector>
#include "Player.h"
#include "Vec3.h"

//Get the pid of a process name
DWORD GetProcId(LPCTSTR ProcessName);

//Get module base adresse of a process
uintptr_t GetModuleBaseAddress(DWORD procId, LPCTSTR ProcessName);

//Resolve adresse with offsets
uintptr_t FindAdressWithOffsetsEx(HANDLE hproc, uintptr_t modBaseAdress, std::vector <unsigned int> offsets);
uintptr_t FindAdressWithOffsets(uintptr_t modBaseAdress, std::vector <unsigned int> offsets);

//Patch
BOOL PatchEx(DWORD* dst, BYTE* src, unsigned int size, HANDLE hProcess);
BOOL Patch(char* dst, char* src, unsigned int size);

//NOP
BOOL NopEx(
	DWORD* dst,
	unsigned int size,
	HANDLE hProcess
);
BOOL Nop(	
	DWORD* dst,
	unsigned int size
);

Vec3 ResolveCoordStruct(std::vector <unsigned int> x, std::vector <unsigned int> y, std::vector <unsigned int> z, uintptr_t entBaseAdress);