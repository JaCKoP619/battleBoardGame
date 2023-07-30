#include "unitClass.h"
#include "UI_File.h"
#include <array>
#include <iostream>
#include <conio.h>
#include <vector>
#include <chrono>
#include <thread>
#include <filesystem>

extern std::array<std::array<char, ROWS>, COLS> terainMap;
extern std::array<std::array<char, ROWS>, COLS> unitsMap;
extern std::vector<Unit> blueUnits;
extern std::vector<Unit> redUnits;
extern bool playerTeam;
extern fs::path readRed;   // = "listFromRed.txt";';'
extern fs::path writeRed;  //= "RedTeam\\list4Red.txt";
extern fs::path writeBlue; //= "BlueTeam\\list4Blue.txt";
extern fs::path mapFile;   //= "map.txt";

extern Base blueBase;
extern Base redBase;    
extern int turnTIME;
namespace fs = std::filesystem;

int main()
{       turnTIME=1;
        playerTeam=true;
        readBlue = "list4Blue.txt";
        writeBlue = "listFromBlue.txt";
        mapFile = "map.txt";
        blueUnits.clear();
        redUnits.clear();

        //readUnits();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        terainMap = readMap();
        updateUnitMap();
        std::this_thread::sleep_for(std::chrono::seconds(1));


        while (true)
        {
                readUnits();
                system("cls");
                displayTeam();
                printBothMaps();
                std::cout << std::endl;
                std::cout << "Press 1 to get strategic information, along with maps and list of your units." << std::endl;
                std::cout << "Press 2 give order to relocate to unit." << std::endl;
                std::cout << "Press 3 give order for unit to attack" << std::endl;
                std::cout << "Press 4 to check your base status and recruitment menu." << std::endl;
                std::cout << "Press 5 to send orders to your men. This will send data to moderator.exe and close this program." << std::endl;
                std::cout << "Press 6 to create save file." << std::endl;

                char input = static_cast<char>(getch());

                if (input == '1')
                {
                        system("cls");
                        updateUnitMap();
                        navigateList();
                }
                else if (input == '2')
                {
                        relocateMenu();
                }
                else if (input == '3')
                {
                        attackMenu();
                }
                else if (input == '4')
                {
                        recruitmentMenu();
                }
                else if (input == '5')
                {
                        system("cls");
                        writeUnits();

                        break;
                }
                else if (input == '6')
                {
                        system("cls");
                        writeSave();
                        break;
                }
        }

        // TODO: damage dealing method, exe file handling, menu for all, menu for damage with movement range indication, same for damage with attack range indication,
        // TODO: fix coordinates bug, test unit activation, setup moderator.exe and clean shit up


        std::cout << "Press any key to continue..." << std::endl;
        _getch();

        return 0;
}