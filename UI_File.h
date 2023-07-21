#ifndef UI_FILE_H
#define UI_FILE_H
#include <array>
const std::size_t ROWS = 35;
const std::size_t COLS = 35;

extern std::array<std::array<char, ROWS>, COLS> mapArr;
extern std::array<std::array<char, ROWS>, COLS> unitsMap;
void greet();
std::array<std::array<char,ROWS>,COLS> readMap();
void printMap();
char mapMenu();
void updateUnitMap();
void printUnitMap();

#endif