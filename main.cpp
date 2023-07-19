#include "unitClass.h"
#include "UI_File.h"
#include <array>
#include <iostream>
#include <conio.h>
#include <vector>
int main()
{
        const int row = 35, col = 35;
        std::array<std::array<char, col>, row> mapArr;

        //* setup of vectors for storing units and constructing starting bases-------------
        std::vector<Unit> blueUnits;
        std::vector<Unit> redUnits;
        Base blueBase(true);
        Base redBase(false);


        greet();
        mapArr = readMap();
        printMap(mapArr);
       //mapMenu();
        blueUnits.push_back(Unit('A',1,true));
        blueUnits[0].info();

        return 0;
}