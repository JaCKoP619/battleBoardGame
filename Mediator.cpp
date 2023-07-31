#include "unitClass.h"
#include "UI_File.h"
#include <array>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <filesystem>
#include <algorithm>
#include <cstdlib>


// TODO: test damage for units and bases, killing units and victory conditions checking

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

const char *runRed = "./RedPlayer.exe";
const char *runBlue = "./BluePlayer.exe";

const wchar_t *flagsAndValues = L"-f value1 -g value2";

extern int turn;
extern int maxTurn;
extern bool playerTeam;
extern int turnTIME;
int main()
{
        blueUnits.clear();
        redUnits.clear();
        bool victoryBool;
        playerTeam = true;
        turn = 1;
        // setup variables for files location from the mediator point of view
        readRed = "listFromRed.txt";
        readBlue = "listFromBlue.txt";
        writeRed = "list4Red.txt";
        writeBlue = "list4Blue.txt";
        mapFile = "map.txt";
        blueUnits.push_back(Unit('W', 1, true));
        redUnits.push_back(Unit('W', 1, false));
        greet();
        terainMap = readMap();
        loadSaveMenu();

        while (true)
        {
                std::system("clear");
                std::cout << "Turn: " << turn << std::endl;
                if (playerTeam)
                        std::cout << "\x1B[34mBlue Army turn.\x1B[0m" << std::endl;
                else
                        std::cout << "\x1B[31mRed Army turn.\x1B[0m" << std::endl;

                mediatorWriteUnits();

                if (playerTeam)
                {

                        std::thread bluePlayerThread([]()
                                                     { std::system(runBlue); });

                        // Wait for BluePlayer.exe to finish
                        bluePlayerThread.join();

                        readUnits();

                        // turn tick for base to progres recruitment
                        blueBase.turn();
                        // check for dead units and delete them
                        redUnits.erase(std::remove_if(redUnits.begin(), redUnits.end(), [](Unit &unit)
                                                      { return unit.getHp() <= 0; }),
                                       redUnits.end());
                        for (size_t i = 0; i < blueUnits.size(); i++)
                        {
                                // turn tik for units, reset mostly happens via reopening player.exe but it works for gold production.
                                blueUnits[i].turn();
                        }
                        // check for dead base and break the loop if so
                        if (redBase.getHp() <= 0)
                        {
                                std::cout << "Red Base destroyed. " << redBase.getHp() << std::endl;
                                victoryBool = true;
                                break;
                        }
                }
                else
                {

                        std::thread redPlayerThread([]()
                                                    { std::system(runRed); });

                        // Wait for BluePlayer.exe to finish
                        redPlayerThread.join();
                        readUnits();
                        redBase.turn();

                        blueUnits.erase(std::remove_if(blueUnits.begin(), blueUnits.end(), [](Unit &unit)
                                                       { return unit.getHp() <= 0; }),
                                        blueUnits.end());
                        for (size_t i = 0; i < redUnits.size(); i++)
                        {
                                redUnits[i].turn();
                        }
                        if (blueBase.getHp() <= 0)
                        {
                                std::cout << "Blue Base destroyed." << std::endl;
                                victoryBool = false;
                                break;
                        }
                }

                if (turn >= maxTurn)

                {
                        std::cout << "Last turn. The victory is determined by larger number of units on field" << std::endl;
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
        // TODO: make it preatier
        if (victoryBool)
        {
                std::cout << "Blue team Victory!" << std::endl;
                getchar();
        }
        else
                std::cout << "red team Victory!" << std::endl;
        getchar();
        return 0;
}