#include <vector>



//Entity list
unsigned int CurrentMapNameOffset = { 0x109EC0 };
unsigned int PlayerCounterOffset = { 0x10F500 };
unsigned int EntityListPtrOffset = { 0x10f4f8 };

//From player object base adress
unsigned int LocalPLayerOffset = { 0x10f4f4 };
std::vector <unsigned int> ammoOffsets = { 0x374 , 0x14 , 0x0 };
std::vector <unsigned int> healthOffsets = { 0xf8 };
std::vector <unsigned int> nameOffset = { 0x225 };
//Coord
std::vector <unsigned int> HeadCoordXOffsets = { 0x4 };
std::vector <unsigned int> HeadCoordYOffsets = { 0x8 };
std::vector <unsigned int> HeadCoordZOffsets = { 0x0c };

std::vector <unsigned int> BodyCoordXOffsets = { 0x34 };
std::vector <unsigned int> BodyCoordYOffsets = { 0x38 };
std::vector <unsigned int> BodyCoordZOffsets = { 0x3c };


//asm insutrcions offsets
uintptr_t decAmmoInstructionOffset = 0x637e9;