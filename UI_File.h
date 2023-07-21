#ifndef UI_FILE_H
#define UI_FILE_H
#include <array>
const std::size_t ROWS = 35;
const std::size_t COLS = 35;

void greet();
std::array<std::array<char,ROWS>,COLS> readMap();
void printMap(std::array<std::array<char, COLS>, ROWS> mapArr);
char mapMenu();



#endif