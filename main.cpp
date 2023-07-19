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
        blueUnits.push_back(Base(true));
        std::vector<Unit> redUnits;
        redUnits.push_back(Base(false));

        greet();
        mapArr = readMap();
        printMap(mapArr);
        mapMenu();

        return 0;
}