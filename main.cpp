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

        // recruitmentMenu();
        // greet();
        // terainMap = readMap();
        // unitsMap = terainMap; //! do not delete those two at main start

        blueBase.addGold();
        blueBase.info();
        redBase.info();
        blueBase.recruitUnit('K');
        redBase.recruitUnit('S');
        std::cout<<blueBase.writeToFile()<<std::endl;
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

        // updateUnitMap();
        // listUnitsInfo(true);

        std::cout << "Press any key to continue..." << std::endl;
        _getch();

        return 0;
}