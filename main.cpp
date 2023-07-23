#include "unitClass.h"
#include "UI_File.h"
#include <array>
#include <iostream>
#include <conio.h>
#include <vector>
#include <chrono>

extern Base blueBase;
extern Base redBase;
extern std::array<std::array<char, ROWS>, COLS> terainMap;
extern std::array<std::array<char, ROWS>, COLS> unitsMap;
extern std::vector<Unit> blueUnits;
extern std::vector<Unit> redUnits;
int main()
{
        readUnits(false,15);

        std::chrono::seconds pauseDuration(1);

        redBase.info();
        blueBase.info();
        std::cout << "Press any key to continue..." << std::endl;
        _getch();
        terainMap = readMap();
        updateUnitMap();
        listUnitsInfo(false);







        // recruitmentMenu();
        //greet();
        // terainMap = readMap();
        // unitsMap = terainMap; //! do not delete those two at main start

        // blueBase.addGold();
        // blueBase.info();
        // redBase.info();
        // blueBase.recruitUnit('K');
        // redBase.recruitUnit('S');
        // std::cout<<blueBase.getUnitType()<<std::endl;
        // std::cout<<blueBase.writeToFile()<<std::endl;
        // for (int i = 0; i <= 5; i++)
        // {
        //         redBase.turn();
        //         blueBase.turn();
        // }
        // blueBase.recruitUnit('A');
        // redBase.recruitUnit('P');
        // for (int i = 0; i <= 5; i++)
        // {
        //         redBase.turn();
        //         blueBase.turn();
        // }
        // blueUnits[0].relocate(3,2);             //! (y,x), (rows,columns)
        // redUnits[0].relocate(33, 32);
        // writeUnits(true);

        // updateUnitMap();
        // listUnitsInfo(true);

        std::cout << "Press any key to continue..." << std::endl;
        _getch();

        return 0;
}