#include "unitClass.h"
#include "UI_File.h"
#include <array>
#include <iostream>
#include <conio.h>
#include <vector>
extern Base blueBase;
extern Base redBase;
extern std::array<std::array<char, ROWS>, COLS> mapArr;
int main()
{


        //* setup of vectors for storing units and constructing starting bases-------------
std::array<std::array<char, ROWS>, COLS> blueUnitsMap;

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
        blueUnitsMap=updateUnitMap(true);
        printMap(blueUnitsMap);




        std::cout << "Press any key to continue..." << std::endl;
        _getch();
        system("cls");
        return 0;
}