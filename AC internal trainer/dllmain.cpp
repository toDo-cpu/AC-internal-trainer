// C:\Users\Koa\source\repos\AC internal trainer\Debug\AC internal trainer.dll

#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <string>

#include "offsets.h"
#include "memo_tools.h"
#include "cmd.h"
#include "Player.h"
#include "dllHelper.h"
#include "aimbot.h"

#define DEBUG
#define BUFFER_NAME_MAX_SIZE 17
#define BUFFER_MAP_NAME_SIZE 11

DWORD ThreadMain(HMODULE hModule);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(
            nullptr,
            0,
            (LPTHREAD_START_ROUTINE)ThreadMain,
            hModule,
            0,
            nullptr
        ));

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

DWORD ThreadMain(HMODULE hModule)
{

    bool bHealth = false,
        bAmmo = false,
        bAmmoNop = false,
        bAimbot = false;

    HANDLE hAimbotThread = INVALID_HANDLE_VALUE;
    DWORD dwAimbotThreadExitCode = -1;
    pAimbotThreadParams AimbotParams = NULL;
    bool threadAlive = false;
    //Create cmd
    FILE* f = cmd::CreateCmd();

    //&bHealth, &bAmmo , &bAmmoNop
    PrintBanner(&bHealth, &bAmmo , &bAmmoNop, &bAimbot);

    //Resolve all base pointer
    uintptr_t moduleBaseAdress = (uintptr_t)GetModuleHandle(NULL);
    uintptr_t myPlayerBaseAdress = moduleBaseAdress + (uintptr_t)LocalPLayerOffset;
    uintptr_t entListBaseAdress = moduleBaseAdress + (uintptr_t)EntityListPtrOffset;
    uintptr_t playerCounterAdress = moduleBaseAdress + (uintptr_t)PlayerCounterOffset;
    uintptr_t currentMapBaseAdress = moduleBaseAdress + (uintptr_t)CurrentMapNameOffset;
    uintptr_t decAmmoInstructionAdress = moduleBaseAdress + (uintptr_t)decAmmoInstructionOffset;

    //Save map name to control if map changed
    char* CurrentMapName = (char*)(currentMapBaseAdress);

    //number of player in the room ( localplayer counted )
    int32_t* currentPlayerCounter = (int32_t*)(playerCounterAdress);

    //LocalPlayer
    Entity* LocalPlayer = *(Entity**)(myPlayerBaseAdress);

    //EntityList
    EntityList* entList = *(EntityList**)entListBaseAdress;

#ifdef DEBUG
    std::cout << "DEBUG activated" << std::endl;
    std::cout << "uintptr_t moduleBaseAdress            = " << moduleBaseAdress << std::endl;
    std::cout << "uintptr_t myPlayerBaseAdress          = " << myPlayerBaseAdress << std::endl;
    std::cout << "uintptr_t entListBaseAdress           = " << entListBaseAdress << std::endl;
    std::cout << "uintptr_t playerCounterAdress         = " << playerCounterAdress << std::endl;
    std::cout << "uintptr_t currentMapBaseAdress        = " << currentMapBaseAdress << std::endl;
    std::cout << "uintptr_t decAmmoInstructionAdress    = " << decAmmoInstructionAdress << std::endl;
#endif 

    while (true)
    {

        if ((GetAsyncKeyState(VK_NUMPAD6) & 1))
        {
          
            bAimbot = !bAimbot;
            PrintBanner(&bHealth, &bAmmo, &bAmmoNop, &bAimbot);
        }
        if (GetAsyncKeyState(VK_NUMPAD0) & 1)
        {
            break;
        }
        if (GetAsyncKeyState(VK_NUMPAD1) & 1)
        {
            if (!cmd::IsCmdVisble())
            {
                cmd::ShowCmd();
            }

        }
        if (GetAsyncKeyState(VK_NUMPAD2) & 1)
        {
            if (cmd::IsCmdVisble())
            {
                cmd::HideCmd();
            }
            else {
                cmd::ShowCmd();
            }
        }
        if (GetAsyncKeyState(VK_NUMPAD3) & 1)
        {
            bHealth = !bHealth;
            PrintBanner(&bHealth, &bAmmo, &bAmmoNop, &bAimbot);
        }
        if (GetAsyncKeyState(VK_NUMPAD4) & 1)
        {
            bAmmo  = !bAmmo;

            PrintBanner(&bHealth, &bAmmo, &bAmmoNop, &bAimbot);
        }
        if (GetAsyncKeyState(VK_NUMPAD5) & 1)
        {
            bAmmoNop = !bAmmoNop;

            if (bAmmoNop)
            {
                if (!Nop((DWORD*)decAmmoInstructionAdress, (unsigned int)2))
                {

                    PrintBanner(&bHealth, &bAmmo, &bAmmoNop, &bAimbot);
                    bAmmoNop = !bAmmoNop;
                    std::cout << "[WARNING] nop decrementation ammo failed" << std::endl;
                    std::cout << "[SYS_ERROR] " << GetLastError() << std::endl;
                }
            }
            else {
                if (!Patch((char*)decAmmoInstructionAdress, (char*)"\xff\x0E", (unsigned int)2))
                {

                    PrintBanner(&bHealth, &bAmmo, &bAmmoNop, &bAimbot);
                    bAmmoNop = !bAmmoNop;
                    std::cout << "[WARNING] restor ammo decrementation failed" << std::endl;
                    std::cout << "[SYS_ERROR] " << GetLastError() << std::endl;
                }
            }
        }
        //Execute functions
        if (bHealth)
        {
            //Freeze heal value
            LocalPlayer->health = 1337;
        }
        if (bAmmo)
        {
            //Freeze ammo value
            LocalPlayer->health = 1337;
        }
        //Control threads
            if (hAimbotThread == INVALID_HANDLE_VALUE && threadAlive == false && bAimbot)
            {
                //Create aimbot thread
                AimbotParams = (pAimbotThreadParams)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(AimbotThreadParams));

                if (AimbotParams == NULL)
                {
#ifdef DEBUG
                    std::cout << "[DEBUG][ERROR at 181] Couldn't alloc memory" << std::endl;          
#endif
                }
                else {
                    AimbotParams->pEntList = entList;
                    AimbotParams->pLocalPlayer = LocalPlayer;
                    AimbotParams->pPlayerCounter = currentPlayerCounter;
                
                    hAimbotThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AimbotThreadFunc, AimbotParams, 0, &dwAimbotThreadExitCode);

                    if (hAimbotThread == INVALID_HANDLE_VALUE)
                    {
#ifdef DEBUG
                        std::cout << "[DEBUG][ERROR at 194] Couldn't create thread" << std::endl;
#endif
                    }
                    else {

                        threadAlive = true;


                        PrintBanner(&bHealth, &bAmmo, &bAmmoNop, &bAimbot);
                    }
                }
            }
            if (!bAimbot && threadAlive == true)
            {
                if (GetExitCodeThread(hAimbotThread, &dwAimbotThreadExitCode)) 
                {
                    if (TerminateThread(hAimbotThread, dwAimbotThreadExitCode))
                    {
                        threadAlive = false;
                        hAimbotThread = INVALID_HANDLE_VALUE;

                        HeapFree(GetProcessHeap(), 0, AimbotParams);
                        AimbotParams = NULL;


                        PrintBanner(&bHealth, &bAmmo, &bAmmoNop, &bAimbot);
                    }
                }
            }
        Sleep(50);
    }
    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}