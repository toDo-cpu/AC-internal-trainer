#include "pch.h"
#include <iostream>
#include "dllHelper.h"

void PrintBanner(bool* bAmmo, bool* bHealth, bool* bAmmoNop, bool* bAimbot)
{
    //1 row = 35 chars
    //std::cout << "  |                                   |" << std::endl;
    //"   "  + boolToLabel(bAmmoNop) = char[9]

    int rowFeel = 1;
    std::string blank = std::string(rowFeel, ' ');

    std::system("cls");

    std::cout << "+" << "----Info" << std::string(25, '-') << "+" << std::endl;
    std::cout << "|" << std::string(33, ' ') << "|" << std::endl;
    std::cout << "|" << "   [F2]    Debug         " << std::string(7, ' ') << blank << "|" << std::endl;
    std::cout << "|" << std::string(33, ' ') << "|" << std::endl;
    std::cout << "|" << "   [0]     Eject cheat   " << std::string(7, ' ') << blank << "|" << std::endl;
    std::cout << "|" << std::string(33, ' ') << "|" << std::endl;
    std::cout << "|" << "   [2]     Show/Hide     " << std::string(7, ' ') << blank << "|" << std::endl;
    std::cout << "|" << std::string(33, ' ') << "|" << std::endl;

    std::cout << "+" << "----Freeze values" << std::string(16, '-') << "+" << std::endl;
    std::cout << "|" << std::string(33, ' ') << "|" << std::endl;
    std::cout << "|" << "   [3]     Freeze health " << boolToLabel(bHealth) << "  " << blank << "|" << std::endl;
    std::cout << "|" << std::string(33, ' ') << "|" << std::endl;
    std::cout << "|" << "   [4]     Freeze ammo   " << boolToLabel(bAmmo) << "  " << blank << "|" << std::endl;
    std::cout << "|" << std::string(33, ' ') << "|" << std::endl;

    std::cout << "+" << "----Nop instructions" << std::string(13, '-') << "+" << std::endl;
    std::cout << "|" << std::string(33, ' ') << "|" << std::endl;
    std::cout << "|" << "   [5]     NOP ammo      " << boolToLabel(bAmmoNop) << "  " << blank << "|" << std::endl;
    std::cout << "|" << std::string(33, ' ') << "|" << std::endl;
    std::cout << "+" << "----Aimbot" << std::string(25, '-') << "+" << std::endl;
    std::cout << "|" << std::string(33, ' ') << "|" << std::endl;
    std::cout << "|" << "   [6]     Enable        " << boolToLabel(bAimbot) << "  " << blank << "|" << std::endl;
    std::cout << "|" << std::string(33, ' ') << "|" << std::endl;

    std::cout << "+" << std::string(33, '-') << '+' << std::endl;

}
std::string boolToLabel(bool* mybool)
{
    if (*mybool == true)
    {
        return (std::string)"[ON] ";
    }
    else {
        return (std::string)"[OFF]";
    }
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