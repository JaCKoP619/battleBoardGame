#include "unitClass.h"
#include "UI_File.h"
#include <array>
#include <iostream>
#include <conio.h>
#include <vector>
extern Base blueBase;
extern Base redBase;
extern std::array<std::array<char, ROWS>, COLS> terainMap;
extern std::array<std::array<char, ROWS>, COLS> unitsMap;
int main()
{

        greet();
        terainMap = readMap();
        unitsMap = terainMap; //! do not delete those two at main start

        blueBase.addGold();
        blueBase.info();
        redBase.info();
        blueBase.recruitUnit('K');
        redBase.recruitUnit('S');

        for (int i = 0; i <= 5; i++)
        {
                redBase.turn();
                blueBase.turn();
        }
        blueBase.recruitUnit('A');
        redBase.recruitUnit('P');
        for (int i = 0; i <= 5; i++)
        {
                redBase.turn();
                blueBase.turn();
        }
        blueUnits[0].relocate(1, 1);
        redUnits[0].relocate(35, 35);
        for (size_t i = 0; i < blueUnits.size(); i++)
        {
                blueUnits[i].info();
        }

        for (size_t i = 0; i < blueUnits.size(); i++)
        {
                redUnits[i].info();
        }
        unitsMap = terainMap;

        updateUnitMap();

        printBothMaps();
        std::cout << "Press any key to continue..." << std::endl;
        _getch();
        listUnitsInfo(true);

        std::cout << "Press any key to continue..." << std::endl;
        _getch();

        return 0;
}