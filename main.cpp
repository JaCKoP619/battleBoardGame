#include "class.h"
#include "UI_File.h"
#include <array>
#include <iostream>
#include <conio.h>
int main()
{
        const int row = 35, col = 35;
        std::array<std::array<char, col>, row> mapArr;

        greet();
        mapArr = readMap();
        printMap(mapArr);
        std::cout << "Press any key to continue..." << std::endl;
        _getch();
        return 0;
}