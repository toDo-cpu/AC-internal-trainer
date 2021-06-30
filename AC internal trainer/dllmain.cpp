// C:\Users\Koa\source\repos\AC internal trainer\Debug\AC internal trainer.dll

#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <string>

#include "memo_tools.h"
#include "cmd.h"
#include "Player.h"

#define BUFFER_NAME_MAX_SIZE 17
#define BUFFER_MAP_NAME_SIZE 11

void PrintBanner();

std::string boolToStr(bool mybool);

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
        bAmmoNop = false;
    //Create cmd
    FILE* f = cmd::CreateCmd();

    PrintBanner();

    //Resolve all base pointer
    uintptr_t moduleBaseAdress = (uintptr_t)GetModuleHandle(L"ac_client.exe");
    uintptr_t myPlayerBaseAdress = moduleBaseAdress + LocalPLayerOffset;
    uintptr_t EntityListPtr = moduleBaseAdress + EntityListPtrOffset;

    //Resole all pointers 
    //Save map name to control if map changed

    char* CurrentMapName = (char*)(moduleBaseAdress + CurrentMapNameOffset);
    char* oldMapName = new char[BUFFER_MAP_NAME_SIZE];

    memcpy_s(oldMapName, BUFFER_MAP_NAME_SIZE, CurrentMapName, BUFFER_MAP_NAME_SIZE);

    //Others ptr
    uintptr_t decAmmoInstructionAdress = moduleBaseAdress + decAmmoInstructionOffset;
    int* playerCounter = (int*)(moduleBaseAdress + PlayerCounterOffset - 0x1);

    //Declare localplayer obj
    PlayerEntity* LocalPlayer = new PlayerEntity(myPlayerBaseAdress);

    //Declare entity list
    std::vector <PlayerEntity> EntityList[10];

    while (true)
    {

        //On the terminal control
        if (strcmp(CurrentMapName, oldMapName) != 0)
        {
            std::cout << "Updating entity list...." << std::endl;

           
            memcpy_s(oldMapName, BUFFER_MAP_NAME_SIZE, CurrentMapName, BUFFER_MAP_NAME_SIZE);
        }
        if (GetAsyncKeyState(VK_F2) & 1)
        {

        }
        if (GetAsyncKeyState(VK_NUMPAD0) & 1)
        {
            delete[] oldMapName;
            fclose(f);
            FreeConsole();
            FreeLibraryAndExitThread(hModule, 0);
            exit(0);
        }
        if (GetAsyncKeyState(VK_NUMPAD1) & 1)
        {
            if (!cmd::IsCmdVisble())
            {
                cmd::ShowCmd();
            }
            PrintBanner();
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
            std::cout << "[INFO] Freeze health "<< boolToStr(bHealth) << std::endl;
        }
        if (GetAsyncKeyState(VK_NUMPAD4) & 1)
        {
            bAmmo  = !bAmmo;

            std::cout << "[INFO] Freeze ammo" << boolToStr(bAmmo) << std::endl;
        }
        if (GetAsyncKeyState(VK_NUMPAD5) & 1)
        {
            bAmmoNop = !bAmmoNop;

            if (bAmmoNop)
            {
                if (Nop((DWORD*)decAmmoInstructionAdress, (unsigned int)2))
                {
                    std::cout << "[INFO] nop decremantation ammo enable" << std::endl;
                }
                else {
                    std::cout << "[WARNING] nop decrementation ammo failed" << std::endl;
                    std::cout << "[SYS_ERROR] "<< GetLastError() << std::endl;
                }
            }
            else {
                if (Patch((char*)decAmmoInstructionAdress, (char*)"\xff\x0E", (unsigned int)2 ))
                {
                    std::cout << "[INFO] dec ammo instruction restored" << std::endl;
                } else {
                    std::cout << "[WARNING] restor ammo decrementation failed" << std::endl;
                    std::cout << "[SYS_ERROR] " << GetLastError() << std::endl;
                }
            }
        }

        //Execute functions
        if (bHealth)
        {
            //Freeze heal value
            *(int*)FindAdressWithOffsets(myPlayerBaseAdress, healthOffsets) = 1337;
        }
        if (bAmmo)
        {
            //Freeze ammo value
            *(int*)FindAdressWithOffsets(myPlayerBaseAdress, ammoOffsets) = 1337;
        }
        Sleep(100);
    }
}
void PrintBanner()
{
    //std::cout << "  |                                   |" << std::endl;
    std::system("cls");
    std::cout << "  +--Menu-----------------------------+" << std::endl;
    std::cout << "  |                                   |" << std::endl;
    std::cout << "  |   [F2] DEBUG                      |" << std::endl;
    std::cout << "  |   [0] eject trainer (exit)        |" << std::endl;
    std::cout << "  |   [1] help                        |" << std::endl;
    std::cout << "  |   [2] hide/Show console           |" << std::endl;
    std::cout << "  |                                   |" << std::endl;
    std::cout << "  +--Freeze---------------------------+" << std::endl;
    std::cout << "  |                                   |" << std::endl;
    std::cout << "  |   [3] freeze health               |" << std::endl;
    std::cout << "  |   [4] freeze ammo                 |" << std::endl;
    std::cout << "  |                                   |" << std::endl;
    std::cout << "  +--Nop------------------------------+" << std::endl;
    std::cout << "  |                                   |" << std::endl;
    std::cout << "  |   [5] nop ammo                    |" << std::endl;
    std::cout << "  |                                   |" << std::endl;
    std::cout << "  +-----------------------------------+" << std::endl;
}
std::string boolToStr(bool mybool)
{
    if (mybool)
    {
        return (std::string)"enable";
    } 
    else {
        return (std::string)"disable";
    }
}
