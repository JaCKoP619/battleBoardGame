#ifndef UI_FILE_H
#define UI_FILE_H
#include <array>
const std::size_t ROWS = 35;
const std::size_t COLS = 35;

extern std::array<std::array<char, ROWS>, COLS> mapArr;
void greet();
std::array<std::array<char,ROWS>,COLS> readMap();
void printMap(std::array<std::array<char, COLS>, ROWS> map);
char mapMenu();
std::array<std::array<char,ROWS>,COLS> updateUnitMap(bool team);


#endif