#include "unitClass.h"
#include "UI_File.h"
#include <array>
#include <iostream>
#include <conio.h>
#include <vector>
#include <chrono>
#include <thread>
#include <filesystem>
#include <algorithm>
#include <windows.h>
#include <cstdlib>

extern Base redBase; // Base declaration
extern Base blueBase;

extern std::array<std::array<char, ROWS>, COLS> terainMap;
extern std::array<std::array<char, ROWS>, COLS> unitsMap;
extern std::vector<Unit> blueUnits;
extern std::vector<Unit> redUnits;

namespace fs = std::filesystem;
extern fs::path readRed;   // = "listFromRed.txt";
extern fs::path readBlue;  //= "ListFromBlue.txt";
extern fs::path writeRed;  //= "RedTeam\\list4Red.txt";
extern fs::path writeBlue; //= "BlueTeam\\list4Blue.txt";
extern fs::path mapFile;   //= "map.txt";

const char *runRed = "RedPlayer.exe";
const char *runBlue = "BluePlayer.exe";

const wchar_t *flagsAndValues = L"-f value1 -g value2";

extern int turn;
extern int maxTurn;
extern bool playerTeam;
extern int turnTIME;
int main()
{



        bool victoryBool;
        playerTeam = true;
        turn = 1;
        // setup variables for files location from the mediator point of view
        readRed = "listFromRed.txt";
        readBlue = "ListFromBlue.txt";
        writeRed = "list4Red.txt";
        writeBlue = "list4Blue.txt";
        mapFile = "map.txt";

        greet();
        loadSaveMenu();

        while (true)
        {
                std::system("cls");
                std::cout << "Turn: " << turn << std::endl;
                if (playerTeam)
                        std::cout << "Blue Army turn." << turn << std::endl;
                else
                        std::cout << "Red Army turn." << turn << std::endl;

                mediatorWriteUnits();

                if (playerTeam)
                {

                        system(runBlue);
                        readUnits();
                        blueBase.turn();
                        redUnits.erase(std::remove_if(redUnits.begin(), redUnits.end(), [](Unit &unit)
                                                      { return unit.getHp() <= 0; }),
                                       redUnits.end());
                        // Checking for victory conditions, breaking the loop if met
                        if (redBase.getHp() <= 0)
                        {
                                std::cout << "Red Base destroyed." << std::endl;
                                victoryBool = true;
                                break;
                        }
                }
                else
                {
                        system(runRed);
                        readUnits();
                        redBase.turn();

                        blueUnits.erase(std::remove_if(blueUnits.begin(), blueUnits.end(), [](Unit &unit)
                                                       { return unit.getHp() <= 0; }),
                                        blueUnits.end());
                        if (blueBase.getHp() <= 0)
                        {
                                std::cout << "Blue Base destroyed." << std::endl;
                                victoryBool = false;
                                break;
                        }
                }

                if (turn >= maxTurn)
                        std::cout << "Last turn. The victory is determined by larger number of units on field" << std::endl;
                {
                        if (blueUnits.size() > redUnits.size())
                        {
                                victoryBool = true;
                                break;
                        }
                        else
                        {
                                victoryBool = true;
                                break;
                        }
                }
                if (playerTeam == false)
                        turn++;

                playerTeam = !playerTeam;
        }

        return 0;
}