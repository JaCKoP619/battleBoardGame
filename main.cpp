#include "unitClass.h"
#include "UI_File.h"
#include <array>
#include <iostream>
#include <conio.h>
#include <vector>
#include <chrono>
#include <thread>

extern std::array<std::array<char, ROWS>, COLS> terainMap;
extern std::array<std::array<char, ROWS>, COLS> unitsMap;
extern std::vector<Unit> blueUnits;
extern std::vector<Unit> redUnits;


int main()
{
        blueUnits.clear();
        redUnits.clear();

readUnits(15);
 std::this_thread::sleep_for(std::chrono::seconds(1));
terainMap = readMap();
updateUnitMap();
 std::this_thread::sleep_for(std::chrono::seconds(1));


        //         redBase.info();
        //         blueBase.info();
        //         std::cout << "Press any key to continue..." << std::endl;
        //         _getch();
        //         terainMap = readMap();
        //         updateUnitMap();
        //         navigateList();
        while (true)
        {       readUnits(playerTeam);
                system("cls");
                displayTeam();
                printBothMaps();
                std::cout<<std::endl;
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
                {       system("cls");
                        writeSave();
                        break;
                }
        }

        // TODO: damage dealing method, exe file handling, menu for all, menu for damage with movement range indication, same for damage with attack range indication,
        //TODO: fix coordinates bug, test unit activation, setup moderator.exe and clean shit up

        // recruitmentMenu();
        // greet();
        // terainMap = readMap();
        // unitsMap = terainMap; //! do not delete those two at main start

        // blueBase.addGold();
        // blueBase.info();
        // redBase.info();
        // blueBase.recruitUnit('K');
        // redBase.recruitUnit('S');
        // std::cout<<blueBase.getUnitType()<<std::endl;
        // std::cout<<blueBase.writeToFile()<<std::endl;
        // for (int i = 0; i <= 5; i++)
        // {
        //         redBase.turn();
        //         blueBase.turn();
        // }
        // blueBase.recruitUnit('A');
        // redBase.recruitUnit('P');
        // for (int i = 0; i <= 5; i++)
        // {
        //         redBase.turn();
        //         blueBase.turn();
        // }
        // blueUnits[0].relocate(3,2);             //! (y,x), (rows,columns)
        // redUnits[0].relocate(33, 32);
        // writeUnits(true);

        // updateUnitMap();
        // listUnitsInfo(true);

        std::cout << "Press any key to continue..." << std::endl;
        _getch();

        return 0;
}