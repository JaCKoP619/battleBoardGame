#include "class.h"
#include "UI_File.h"
#include <array> 

int main()
{
const int row = 35, col = 35;
std::array<std::array<char, col>, row> mapArr;


        greet();
        mapArr =readMap();
        printMap(mapArr);
        
        return 0;
}