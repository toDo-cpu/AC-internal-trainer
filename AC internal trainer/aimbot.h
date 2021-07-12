#pragma once

#include <math.h>
#include <iostream>
#include "Player.h"

Entity* ResolveBestTarget(EntityList* entList, Entity* localPlayer, int32_t* playerCounter);

//Aimbot thread
//The program need to create a thread to do the aimbot , becasue he is too slow 

DWORD WINAPI AimbotThreadFunc(LPVOID lpParam);

typedef struct AimbotThreadParams {

	Entity* pLocalPlayer;
	EntityList* pEntList;
	int32_t* pPlayerCounter;

} AimbotThreadParams , *pAimbotThreadParams;