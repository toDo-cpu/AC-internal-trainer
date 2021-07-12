#include "pch.h"
#include <math.h>
#include <iostream>
#include "Player.h"
#include "aimbot.h"

#define DEBUG
#define PI 3.14159265

Entity* ResolveBestTarget(EntityList* entList, Entity* localPlayer, int32_t* playerCounter)
{
    Entity* target = nullptr;
    Entity* currentEnt = nullptr;
    float distance = 0.0;
    float shortestDistance = 999999999999;

    if (*playerCounter != 0x0)
    {
        for (int i = 0; i < *playerCounter - 0x1; i++)
        {
            currentEnt = entList->content[i];
#ifdef DEBUG

            std::cout << "Player [" << std::string(currentEnt->name) << ']' << std::endl;

#endif 
            distance = Vec3CalcDistance(&localPlayer->BodyPos, &currentEnt->BodyPos);

#ifdef DEBUG

            std::cout << std::string(currentEnt->name) << " distance is " << distance << std::endl;

#endif 
            if (distance <= shortestDistance && currentEnt->health > 0x0)
            {
                shortestDistance = distance;
                target = entList->content[i];
            }

#ifdef DEBUG
            
            std::cout << "------------------------------------------" << std::endl;

#endif
        }
    }
#ifdef DEBUG
    if (target != nullptr)
        std::cout << "Best target is " << std::string(target->name) << std::endl;
#endif

    return target;
}
 
DWORD WINAPI AimbotThreadFunc(LPVOID lpParam)
{
    HANDLE hStdout;
    pAimbotThreadParams pParams;

    pParams = (pAimbotThreadParams)lpParam;

    EntityList* entList = pParams->pEntList;
    Entity* localPlayer = pParams->pLocalPlayer;
    int32_t* currentPLayerCounter = pParams->pPlayerCounter;

    while (true)
    {
        if ((GetAsyncKeyState(VK_LBUTTON) & 1) & (localPlayer->health > 0x0))
        {
            Entity* target = ResolveBestTarget(entList, localPlayer, currentPLayerCounter);

            if (target != nullptr)
            {

                Vector3 AimAt = Vec3CalcAngle(&localPlayer->HeadCoord, &target->HeadCoord);

                localPlayer->ViewAngles.x = AimAt.x;
                localPlayer->ViewAngles.y = AimAt.y;
                localPlayer->ViewAngles.z = AimAt.z;

                target = nullptr;
            }
        }
        Sleep(5);
    }

    return 0;
}

