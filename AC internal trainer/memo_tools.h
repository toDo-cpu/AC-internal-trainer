#include <Windows.h>
#include <vector>
#include "Player.h"

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
