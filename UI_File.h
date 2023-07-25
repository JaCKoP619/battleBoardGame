#ifndef UI_FILE_H
#define UI_FILE_H
#include <array>
#include <vector>
#include "unitClass.h"
const std::size_t ROWS = 35;
const std::size_t COLS = 35;

extern std::array<std::array<char, ROWS>, COLS> terainMap;
extern std::array<std::array<char, ROWS>, COLS> unitsMap;
extern std::vector<Unit> blueUnits;
extern std::vector<Unit> redUnits;
extern bool playerTeam;
void greet();
void displayTeam();
std::array<std::array<char,ROWS>,COLS> readMap();
void printMap();
char menu();
void updateUnitMap();
void relocateMap( Unit& selectedUnit);
void printBothMaps();
void listUnitsInfo(int coun);
void recruitmentMenu();
void writeUnits(bool team);
bool readUnits(int TurnTIME);
void readSave();
void writeSave();
void navigateList();
void loadSaveMenu();
void relocateMenu();



#endif