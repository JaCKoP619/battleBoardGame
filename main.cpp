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

        Base blueBase(true);
        Base redBase(false);

        greet();
        mapArr = readMap();
        printMap(mapArr);
        blueBase.info();

        blueBase.recruitUnit('K');
        std::cout<< "recruitment starts"<< std::endl;
        blueBase.info();
        



        // for (int i = 0; i <= 6; i++)
        // {
        //         blueBase.info();
        //         blueBase.turn();
        // }

        return 0;
}