#include "unitClass.h"
#include "UI_File.h"
#include <array>
#include <iostream>
#include <conio.h>
#include <vector>
extern Base blueBase;
extern Base redBase;
int main()
{
        const int row = 35, col = 35;
        std::array<std::array<char, col>, row> mapArr;

        //* setup of vectors for storing units and constructing starting bases-------------


        greet();
        mapArr = readMap();
        printMap(mapArr);
        blueBase.info();

        blueBase.recruitUnit('K');

        for (int i = 0; i <= 5; i++)
        {
                blueBase.info();
                blueBase.turn();
        }
        blueBase.recruitUnit('A');

        for (int i = 0; i <= 5; i++)
        {
                blueBase.info();
                blueBase.turn();
        }
        blueUnits[0].relocate(1, 1);

        for (size_t i = 0; i < blueUnits.size(); i++)
        {
                blueUnits[i].info();
        }
        std::cout << "Press any key to continue..." << std::endl;
        _getch();
        system("cls");
        return 0;
}