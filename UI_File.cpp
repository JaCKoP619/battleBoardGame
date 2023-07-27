
#include "UI_File.h"
#include "unitClass.h"
#include <iostream>
#include <conio.h>
#include <chrono>
#include <fstream>
#include <filesystem>
#include <array>
#include <thread>
#include <sstream>
#include <algorithm>

// TODO: temp bool team variable 4 testing
bool playerTeam = false;
// namespace and paths for unit txt files for both teams
namespace fs = std::filesystem;
fs::path readRed = "list4Red.txt";
fs::path readBlue = "list4Blue.txt";
fs::path mapFile = "map.txt";
extern int typeToModifierArr(char chartype);
extern std::vector<Unit> blueUnits;
extern std::vector<Unit> redUnits;
extern const int unitModifiers[7][5];
extern const int damageTable[7][8];

    int row = int(ROWS);
int col = int(COLS);
//* maps: terrain and strategic
std::array<std::array<char, ROWS>, COLS> terainMap;
std::array<std::array<char, ROWS>, COLS> unitsMap;
//* opening text message display and wait for input to carry on---------------------------------------------------------------------TESTED OK
void greet()

{
  char input;
  std::chrono::seconds pauseDuration(1);
  std::cout << R"(
_______  _______  _______ _________          _______  _______                     
(  ____ \(  ___  )(  ____ )\__   __/|\     /|(  ____ )(  ____ \                    
| (    \/| (   ) || (    )|   ) (   | )   ( || (    )|| (    \/                    
| |      | (___) || (____)|   | |   | |   | || (____)|| (__                        
| |      |  ___  ||  _____)   | |   | |   | ||     __)|  __)                       
| |      | (   ) || (         | |   | |   | || (\ (   | (                          
| (____/\| )   ( || )         | |   | (___) || ) \ \__| (____/\                    
(_______/|/     \||/          )_(   (_______)|/   \__/(_______/                    
_________          _______    _______  _______  _______ _________ _        _______ 
\__   __/|\     /|(  ____ \  (  ____ \(  ___  )(  ____ \\__   __/( \      (  ____ \
   ) (   | )   ( || (    \/  | (    \/| (   ) || (    \/   ) (   | (      | (    \/
   | |   | (___) || (__      | |      | (___) || (_____    | |   | |      | (__    
   | |   |  ___  ||  __)     | |      |  ___  |(_____  )   | |   | |      |  __)   
   | |   | (   ) || (        | |      | (   ) |      ) |   | |   | |      | (      
   | |   | )   ( || (____/\  | (____/\| )   ( |/\____) |   | |   | (____/\| (____/\
   )_(   |/     \|(_______/  (_______/|/     \|\_______)   )_(   (_______/(_______/ 
                                 ____                                         
                              .-"    `-.      ,                               
                            .'          '.   /j\                              
                           /              \,/:/#\                /\           
                          ;              ,//' '/#\              //#\          
                          |             /' :   '/#\            /  /#\         
                          :         ,  /' /'    '/#\__..--""""/    /#\__      
                           \       /'\'-._:__    '/#\        ;      /#, """---
                            `-.   / ;#\']" ; """--./#J       ':____...!       
                               `-/   /#\  J  [;[;[;Y]         |      ;        
""""""---....             __.--"/    '/#\ ;   " "  |     !    |   #! |        
             ""--.. _.--""     /      ,/#\'-..____.;_,   |    |   '  |        
                   "-.        :_....___,/#} "####" | '_.-",   | #['  |        
                      '-._      |[;[;[;[;|         |.;'  /;\  |      |        
                      ,   `-.   |        :     _   .;'    /;\ |   #" |        
                      !      `._:      _  ;   ##' .;'      /;\|  _,  |        
                     .#\"""---..._    ';, |      .;{___     /;\  ]#' |__....--
          .--.      ;'/#\         \    ]! |       "| , """--./_J    /         
         /  '%;    /  '/#\         \   !' :        |!# #! #! #|    :`.__      
        i__..'%] _:_   ;##J         \      :"#...._!   '  "  "|__  |    `--.._
         | .--""" !|""""  |"""----...J     | '##"" `-._       |  """---.._    
     ____: |      #|      |         #|     |          "]      ;   ___...-"T,  
    /   :  :      !|      |   _______!_    |           |__..--;"""     ,;MM;  
   :____| :    .-.#|      |  /\      /#\   |          /'               ''MM;  
    |""": |   /   \|   .----+  ;      /#\  :___..--"";                  ,'MM; 
   _Y--:  |  ;     ;.-'      ;  \______/#: /         ;                  ''MM; 
  /    |  | ;_______;     ____!  |"##"""MM!         ;                    ,'MM;
 !_____|  |  |"#"#"|____.'""##"  |       :         ;                     ''MM  
  | """"--!._|     |##""         !       !         :____.....-------"""""" |'
  |          :     |______                        ___!_ "#""#""#"""#"""#"""|  
__|          ;     |MM"MM"""""---..._______...--""MM"MM]                   |   
  "\-.      :      |#                                  :                   |  
    /#'.    |      /##,                                !                   |  
   .',/'\   |       #:#,                                ;       .==.       |  
  /"\'#"\',.|       ##;#,                               !     ,'||||',     |  
        /;/`:       ######,          ____             _ :     M||||||M     |  
       ###          /;"\.__"-._   """                   |===..M!!!!!!M_____|  
                           `--..`--.._____             _!_                    
                                          `--...____,="_.'`-.____        

   ____ _               __       _____                   ___         _ 
  / __/(_)__ _   ___   / /___   / ___/___ _ __ _  ___   / _ ) __ __ (_)
 _\ \ / //  ' \ / _ \ / // -_) / (_ // _ `//  ' \/ -_) / _  |/ // /_   
/___//_//_/_/_// .__//_/ \__/  \___/ \_,_//_/_/_/\__/ /____/ \_, /(_)  
              /_/                                           /___/      
     __       _____ __ __       ___                                    
 __ / /___ _ / ___// //_/___   / _ \                                   
/ // // _ `// /__ / ,<  / _ \ / ___/                                   
\___/ \_,_/ \___//_/|_| \___//_/           
                                                                                    )"
            << std::endl;

  std::cout << "Press any key to continue..." << std::endl;
  _getch();
  system("cls");
}
//* functions for mediator to load at the startup
void displayTeam()
{
  if (playerTeam == true)
  {
    std::cout << "\x1B[34m"
              << R"(
 ______   _____                          _                                     
|_   _ \ |_   _|                        / \                                    
  | |_) |  | |     __   _   .---.      / _ \     _ .--.  _ .--..--.    _   __  
  |  __'.  | |   _[  | | | / /__\\    / ___ \   [ `/'`\][ `.-. .-. |  [ \ [  ] 
 _| |__) |_| |__/ || \_/ |,| \__.,  _/ /   \ \_  | |     | | | | | |   \ '/ /  
|_______/|________|'.__.'_/ '.__.' |____| |____|[___]   [___||__||__][\_:  /   
                                                                      \__.'          
    )"
              << "\x1B[0m" << std::endl;
  }
  else if (playerTeam == false)
  {
    std::cout << "\x1B[31m"
              << R"(
 _______                 __        _                                     
|_   __ \               |  ]      / \                                    
  | |__) |  .---.   .--.| |      / _ \     _ .--.  _ .--..--.    _   __  
  |  __ /  / /__\\/ /'`\' |     / ___ \   [ `/'`\][ `.-. .-. |  [ \ [  ] 
 _| |  \ \_| \__.,| \__/  |   _/ /   \ \_  | |     | | | | | |   \ '/ /  
|____| |___|'.__.' '.__.;__] |____| |____|[___]   [___||__||__][\_:  /   
                                                                \__.'         
    )"
              << "\x1B[0m" << std::endl;
  }
}
void loadSaveMenu()
{

  while (true)
  {
    std::cout << "would you like to load saved file? If not, program will start a new game.\n Y/N?" << std::endl;
    char input = static_cast<char>(getch());
    system("cls");

    if (input == 'y')
    {
      readSave();
      break;
    }
    else if (input == 'n')
      break;
  }
  while (true)
  {
    std::cout << "would you like to load saved file? If not, program will start a new game.\n Y/N?" << std::endl;
    char input = static_cast<char>(getch());
    system("cls");
  }
}

//* read map out of trxt file function ---------------------------------------------------------------------------------------------TESTED OK
std::array<std::array<char, ROWS>, COLS> readMap()
{
  extern fs::path mapFile;

  try
  {
    if (fs::exists(mapFile))
    {
      try
      {
        fs::file_status fileStatus = fs::status(mapFile);
        std::ifstream file(mapFile);
        for (std::size_t i = 0; i < row; ++i)
        {
          for (std::size_t j = 0; j < col; ++j)
          {
            file >> terainMap[j][i];
          }
        }

        file.close();
      }
      catch (const std::filesystem::filesystem_error &e)
      {
        std::cout << e.what() << std::endl;
        std::cout << "Press any key to continue..." << std::endl;
        _getch();
      }
    }
    else
    {
      if (fs::exists(mapFile) == false)
      {
        throw std::runtime_error("Map file not found at path: " + mapFile.string());
      }
    }
  }
  catch (const std::runtime_error &e)
  {
    std::cout << e.what() << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    _getch();
  }
  return terainMap;
}

// * function updating values of unit map based on terrainMap and unit positons
void updateUnitMap()
{
  //  std::cout << blueUnits.size() << std::endl;
  //  size_t i = blueUnits.size()+1;
  //   std::cout << i << std::endl;

  std::size_t x;
  std::size_t y;

  unitsMap = terainMap;
  unitsMap[std::size_t(blueBase.positionX())][std::size_t(blueBase.positionY())] = char(redBase.getUnitType());
  unitsMap[std::size_t(redBase.positionX())][std::size_t(redBase.positionY())] = char(redBase.getUnitType());

  for (std::size_t i = 0; i < blueUnits.size(); i++)
  {

    x = std::size_t(blueUnits[i].positionX());
    y = std::size_t(blueUnits[i].positionY());
    if (unitsMap[y][x] == '0' || unitsMap[y][x] == '6'&&blueUnits[i].getHp()>0)
    
      unitsMap[y][x] = blueUnits[i].getUnitType();
    
    else if (unitsMap[y][x] == 'K' || unitsMap[y][x] == 'S' || unitsMap[y][x] == 'A' || unitsMap[y][x] == 'P' || unitsMap[y][x] == 'R' || unitsMap[y][x] == 'C' || unitsMap[y][x] == 'W' || unitsMap[y][x] == 'B')
    {if (blueUnits[i].getHp()>0)
      unitsMap[y][x] = 'M';
    }
  }
  for (std::size_t i = 0; i < redUnits.size(); i++)
  {
    x = std::size_t(redUnits[i].positionX());
    y = std::size_t(redUnits[i].positionY());
    if (unitsMap[y][x] == '0' || unitsMap[y][x] == '6'&&redUnits[i].getHp()>0)
 
      unitsMap[y][x] = redUnits[i].getUnitType();

    else if (unitsMap[y][x] == 'K' || unitsMap[y][x] == 'S' || unitsMap[y][x] == 'A' || unitsMap[y][x] == 'P' || unitsMap[y][x] == 'R' || unitsMap[y][x] == 'C' || unitsMap[y][x] == 'W' || unitsMap[y][x] == 'B')
    {if (redUnits[i].getHp()>0)
      unitsMap[y][x] = 'M';
    }
  }
};

//* menu for recruiting units, prints base info and lists of units ----------------------------------------------------------------TESTED OK
void recruitmentMenu()
{

  char input;
  system("cls");

  while (true)
  {
    if (playerTeam == true)
    {

      if (blueBase.getStatus() == true)
      {
        system("cls");
        blueBase.info();
        std::cout << "Base is not recruiting at this moment. Would you like to begin recruitment? Y/N" << std::endl;
        input = static_cast<char>(getch());

        if (input == 'y')
        {
          while (true)
          {
            system("cls");
            std::cout << "Input:  | Unit:   |  HP:  | Speed: |  Cost: | Range| Time of deployment" << std::endl;
            std::cout << "1.      |Knight   |  " << unitModifiers[0][0] << "   | " << unitModifiers[0][1] << "      |  " << unitModifiers[0][2] << "   | " << unitModifiers[0][3] << "    | " << unitModifiers[0][4] << " turns" << std::endl;
            std::cout << "2.      |Swordsman|  " << unitModifiers[1][0] << "   | " << unitModifiers[1][1] << "      |  " << unitModifiers[1][2] << "   | " << unitModifiers[1][3] << "    | " << unitModifiers[1][4] << " turns" << std::endl;
            std::cout << "3.      |Archers  |  " << unitModifiers[2][0] << "   | " << unitModifiers[2][1] << "      |  " << unitModifiers[2][2] << "   | " << unitModifiers[2][3] << "    | " << unitModifiers[2][4] << " turns" << std::endl;
            std::cout << "4.      |Pikemans |  " << unitModifiers[3][0] << "   | " << unitModifiers[3][1] << "      |  " << unitModifiers[3][2] << "   | " << unitModifiers[3][3] << "    | " << unitModifiers[3][4] << " turns" << std::endl;
            std::cout << "5.      |Ram      |  " << unitModifiers[4][0] << "   | " << unitModifiers[4][1] << "      |  " << unitModifiers[4][2] << "   | " << unitModifiers[4][3] << "    | " << unitModifiers[4][4] << " turns" << std::endl;
            std::cout << "6.      |Catapults|  " << unitModifiers[5][0] << "   | " << unitModifiers[5][1] << "      |  " << unitModifiers[5][2] << "   | " << unitModifiers[5][3] << "    | " << unitModifiers[5][4] << " turns" << std::endl;
            std::cout << "7.      |Workers  |  " << unitModifiers[6][0] << "   | " << unitModifiers[6][1] << "      |  " << unitModifiers[6][2] << "   | " << unitModifiers[6][3] << "    | " << unitModifiers[6][4] << " turns" << std::endl;
            std::cout << "press the input number to order rectrutation of an unit. To quit press 'q'" << std::endl;

            char recruitmentInput = static_cast<char>(getch());

            if (recruitmentInput == '1')
            {
              blueBase.recruitUnit('K');
              break;
            }
            else if (recruitmentInput == '2')
            {
              blueBase.recruitUnit('S');
              break;
            }
            else if (recruitmentInput == '3')
            {
              blueBase.recruitUnit('A');
              break;
            }
            else if (recruitmentInput == '4')
            {
              blueBase.recruitUnit('P');
              break;
            }
            else if (recruitmentInput == '5')
            {
              blueBase.recruitUnit('R');
              break;
            }
            else if (recruitmentInput == '6')
            {
              blueBase.recruitUnit('C');
              break;
            }
            else if (recruitmentInput == '7')
            {
              blueBase.recruitUnit('W');
              break;
            }
            else if (recruitmentInput == 'q')
            {
              break;
            }
          }
        }
        else if (input == 'n')
          break;
      }
      else
      {
        system("cls");
        blueBase.info();
        std::cout << "Base is currently recruiting. Come back when it deploys recruited unit" << std::endl;
        std::cout << "Press any key to continue..." << std::endl;
        _getch();
        break;
      }
    }

    if (playerTeam == false)
    {

      if (redBase.getStatus() == true)
      {
        system("cls");
        redBase.info();
        std::cout << "Base is not recruiting at this moment. Would you like to begin recruitment? Y/N" << std::endl;
        input = static_cast<char>(getch());

        if (input == 'y')
        {
          while (true)
          {
            system("cls");
            std::cout << "Input:  | Unit:   |  HP:  | Speed: |  Cost: | Range| Time of deployment" << std::endl;
            std::cout << "1.      |Knight   |  " << unitModifiers[0][0] << "   | " << unitModifiers[0][1] << "      |  " << unitModifiers[0][2] << "   | " << unitModifiers[0][3] << "    | " << unitModifiers[0][4] << " turns" << std::endl;
            std::cout << "2.      |Swordsman|  " << unitModifiers[1][0] << "   | " << unitModifiers[1][1] << "      |  " << unitModifiers[1][2] << "   | " << unitModifiers[1][3] << "    | " << unitModifiers[1][4] << " turns" << std::endl;
            std::cout << "3.      |Archers  |  " << unitModifiers[2][0] << "   | " << unitModifiers[2][1] << "      |  " << unitModifiers[2][2] << "   | " << unitModifiers[2][3] << "    | " << unitModifiers[2][4] << " turns" << std::endl;
            std::cout << "4.      |Pikemans |  " << unitModifiers[3][0] << "   | " << unitModifiers[3][1] << "      |  " << unitModifiers[3][2] << "   | " << unitModifiers[3][3] << "    | " << unitModifiers[3][4] << " turns" << std::endl;
            std::cout << "5.      |Ram      |  " << unitModifiers[4][0] << "   | " << unitModifiers[4][1] << "      |  " << unitModifiers[4][2] << "   | " << unitModifiers[4][3] << "    | " << unitModifiers[4][4] << " turns" << std::endl;
            std::cout << "6.      |Catapults|  " << unitModifiers[5][0] << "   | " << unitModifiers[5][1] << "      |  " << unitModifiers[5][2] << "   | " << unitModifiers[5][3] << "    | " << unitModifiers[5][4] << " turns" << std::endl;
            std::cout << "7.      |Workers  |  " << unitModifiers[6][0] << "   | " << unitModifiers[6][1] << "      |  " << unitModifiers[6][2] << "   | " << unitModifiers[6][3] << "    | " << unitModifiers[6][4] << " turns" << std::endl;
            std::cout << "press the input number to order rectrutation of an unit. To quit press 'q'" << std::endl;

            char recruitmentInput = static_cast<char>(getch());

            if (recruitmentInput == '1')
            {
              redBase.recruitUnit('K');
              break;
            }
            else if (recruitmentInput == '2')
            {
              redBase.recruitUnit('S');
              break;
            }
            else if (recruitmentInput == '3')
            {
              redBase.recruitUnit('A');
              break;
            }
            else if (recruitmentInput == '4')
            {
              redBase.recruitUnit('P');
              break;
            }
            else if (recruitmentInput == '5')
            {
              redBase.recruitUnit('R');
              break;
            }
            else if (recruitmentInput == '6')
            {
              redBase.recruitUnit('C');
              break;
            }
            else if (recruitmentInput == '7')
            {
              redBase.recruitUnit('W');
              break;
            }
            else if (recruitmentInput == 'q')
            {
              break;
            }
          }
        }
        else if (input == 'n')
          break;
      }
      else
      {
        system("cls");
        redBase.info();
        std::cout << "Base is currently recruiting. Come back when it deploys recruited unit" << std::endl;
        std::cout << "Press any key to continue..." << std::endl;
        _getch();
        break;
      }
    }
  }
}
//*function printing unitMap array, with checking units aligance and changing print colour for them, also sets 'M' value to indicate multiple units at the same position, TESTED OK, colouring zone not okey but droping that
void relocateMap(Unit &selectedUnit)
{
  std::size_t x;
  std::size_t y;
  system("cls");

  int posX = selectedUnit.positionX();
  int posY = selectedUnit.positionY();
  int range = selectedUnit.getSpd();
  bool unitFound;

  for (std::size_t i = 0; i < row; ++i)
  {
    for (std::size_t j = 0; j < col; ++j)
    {
      unitFound = false;

      if (i == 34 && j == 34) // <-- Adjusted comparison here
      {
        std::cout << "\x1B[34m" << unitsMap[j][i] << "\x1B[0m";
        unitFound = true;
      }
      else if (i == 0 && j == 0) // <-- Adjusted comparison here
      {
        std::cout << "\x1B[31m" << unitsMap[j][i] << "\x1B[0m";
        unitFound = true;
      }

      else if (unitsMap[j][i] == '0' || unitsMap[j][i] == '6')
      {
        if (i >= posY - range && i <= posY + range && j >= posX - range && j <= posX + range)
        {
          std::cout << "\x1B[32m" << unitsMap[j][i] << "\x1B[0m";
          unitFound = true;
        }
        else
        {
          std::cout << unitsMap[j][i]; // Print regular character for tiles outside the range
        }
      }

      else if (unitsMap[j][i] != '0' && unitsMap[j][i] != '6' && unitsMap[j][i] != '9')
      {

        // Check red units
        for (size_t k = 0; k < redUnits.size(); k++)
        {
          x = std::size_t(redUnits[k].positionX());
          y = std::size_t(redUnits[k].positionY());

          if (x == j && y == i) // <-- Adjusted comparison here
          {
            std::cout << "\x1B[31m" << unitsMap[j][i] << "\x1B[0m";
            unitFound = true;
            break;
          }
        }

        // Check blue units if red unit not found
        if (!unitFound)
        {
          for (size_t k = 0; k < blueUnits.size(); k++)
          {
            x = std::size_t(blueUnits[k].positionX());
            y = std::size_t(blueUnits[k].positionY());

            if (x == j && y == i) // <-- Adjusted comparison here
            {
              std::cout << "\x1B[34m" << unitsMap[j][i] << "\x1B[0m";
              unitFound = true;
              break;
            }
          }
        }

        // If unit not found, print regular character
        if (!unitFound)
        {

          std::cout << unitsMap[j][i];
        }
      }

      else
      {
        std::cout << unitsMap[j][i];
      }
    }
    std::cout << std::endl;
  }
  // kinda basic but i'm done with this function and just want to make those ranges correct if i can't print the range in colour properly
  int relocateX;
  int relocateY;
  int relocateXmin = posX - range;
  int relocateYmin = posY - range;
  int relocateXmax = posX + range;
  int relocateYmax = posY + range;

  if (relocateXmin < 0)
    relocateXmin = 0;
  if (relocateYmin < 0)
    relocateYmin = 0;
  if (relocateXmax > row - 1)
    relocateXmax = row - 1;
  if (relocateYmax > col - 1)
    relocateYmax = col - 1;

  std::cout << "Please enter the x and later y coordinates of the unit,\n looking from top to bottom and from left to right" << std::endl;
  std::cout << "unit's range is x: " << (posY - range) << "-" << (posY + range) << " y: " <<(posX - range) << "-" << (posX + range)  << std::endl;
  std::cout << "X:" << std::endl;
  std::cin >> relocateX;
  std::cout << "\nY:" << std::endl;
  std::cin >> relocateY;
  selectedUnit.relocate(relocateX, relocateY);
}

//* Function to conviniently print both maps at same level, with keeping their funcionality ---------------------------------------TESTED OK
void printBothMaps()
{
  std::size_t x;
  std::size_t y;
  updateUnitMap();
  std::cout << "Terrain map:                                              Unit Positions map:" << std::endl;
  for (std::size_t i = 0; i < row; ++i)
  {
    for (std::size_t j = 0; j < col; ++j)
    {
      std::cout << terainMap[j][i];
    }
    std::cout << "                       ";
    for (std::size_t j = 0; j < col; ++j)
    {
      if (unitsMap[j][i] != '0' && unitsMap[j][i] != '6' && unitsMap[j][i] != '9')
      {
        bool unitFound = false;

        for (size_t k = 0; k < redUnits.size(); k++)
        {
          x = std::size_t(redUnits[k].positionX());
          y = std::size_t(redUnits[k].positionY());
          if (34 == i && 34 == j)
          {
            std::cout << "\x1B[31m" << unitsMap[j][i] << "\x1B[0m";
            unitFound = true;
            break;
          }
          if (x == i && y == j)
          {
            std::cout << "\x1B[31m" << unitsMap[j][i] << "\x1B[0m";
            unitFound = true;
            break;
          }
        }

        if (!unitFound)
        {
          for (size_t k = 0; k < blueUnits.size(); k++)
          {
            x = std::size_t(blueUnits[k].positionX());
            y = std::size_t(blueUnits[k].positionY());
            if (0 == i && 0 == j)
            {
              std::cout << "\x1B[34m" << unitsMap[j][i] << "\x1B[0m";
              unitFound = true;
              break;
            }
            else if (x == i&& y == j)
            {
              std::cout << "\x1B[34m" << unitsMap[j][i] << "\x1B[0m";
              unitFound = true;
              break;
            }
          }
        }

        if (!unitFound)
        {
          std::cout << unitsMap[j][i];
        }
      }
      else
      {
        std::cout << unitsMap[j][i];
      }
    }
    std::cout << std::endl;
  }
}
//* function to list player's units, now intended for use inside navigateList() ----------------------------------------------------TESTED OK
void listUnitsInfo(int count)
{

  printBothMaps();
  std::cout << std::endl;
  if (playerTeam == true)
  {
    blueBase.info();
    for (int i = count * 10; i < ((count * 10) + 10); i++)
    {
      if (i < blueUnits.size())
        blueUnits[i].info();
    }
  }
  else
  {
    redBase.info();
    for (int i = count * 10; i < ((count * 10) + 10); i++)
    {
      if (i < redUnits.size())
        redUnits[i].info();
    }
  }
}
//* function to list player's units, with menu allowing to navigate between lists of 10 to prevent overwhelming -----------TESTED OK, after initial issues workls like a charm
void navigateList()
{
  int size;
  int setcount = 0; // this counter is later multiplied by 10 to dislplay 10 units at a time

  while (true)
  {
    if (playerTeam)
      size = blueUnits.size();
    else
      size = redUnits.size();
    system("cls");
    // printBothMaps();
    listUnitsInfo(setcount);
    std::cout << "Enter the unit ID to select, tap 'n' for the next page, tap'p' for the previous page, or 'q' to quit. " << std::endl;
    char option = static_cast<char>(getch());
    if (option == 'q')
    {
      break; // quits the loop
    }
    else if (option == 'n')
    {
      if (setcount * 10 > size)
        setcount++;
    }
    else if (option == 'p')
    {
      if (setcount > 0)
        setcount--;
    }
  }
}
//* Function to write units to file-------------------------------------------------------------------------------------------------TESTED OK
void writeUnits()
{
  if (playerTeam == true)
  {
    // empty the file via trunc and write to it
    std::ofstream outputFile("list4Blue.txt", std::ios::out);

    if (outputFile.is_open())
    {
      outputFile << blueBase.getGold() << std::endl;
      outputFile << blueBase.writeToFile() << std::endl;
      outputFile << redBase.writeToFile();

      for (size_t i = 0; i < blueUnits.size(); i++)
      {
        outputFile << std::endl
                   << blueUnits[i].writeToFile();
      }
      for (size_t i = 0; i < redUnits.size(); i++)
      {
        outputFile << std::endl
                   << redUnits[i].writeToFile();
      }

      std::cout << "Orders sent and will be caried out. press anything to close this window" << std::endl;
      _getch();
      outputFile.close();
    }
    else
    {
      std::cout << "Error opening the file." << std::endl;
      return;
    }
  }
  else
  {
    std::ofstream outputFile("list4Red.txt", std::ios::out);
    if (outputFile.is_open())
    {

      outputFile << blueBase.getGold() << std::endl;
      outputFile << blueBase.writeToFile() << std::endl;
      outputFile << redBase.writeToFile();

      for (size_t i = 0; i < blueUnits.size(); i++)
      {
        outputFile << std::endl
                   << blueUnits[i].writeToFile();
      }
      for (size_t i = 0; i < redUnits.size(); i++)
      {
        outputFile << std::endl
                   << redUnits[i].writeToFile();
      }

      outputFile.close();
    }
    else
    {
      std::cout << "Error opening the file." << std::endl;
      return;
    }
  }
  std::cout << "Orders sent and will be caried out. press anything to close this window" << std::endl;
  _getch();
}
//* function to read saved files----------------------------------------------------------------------------------------------------TESTED OK
void readSave()

{
  long gold;

  fs::path filePath = "saveFile.txt";
  std::string line;
  char readTeam;
  char readType;
  int readID;
  int readX;
  int readY;
  int readHp;
  char readDeployType;
  int readRemainingTime;
  int setIdCounter;

  // assign path depending on team

  std::filesystem::path file(filePath);

  // If file appears within turnTIME:
  try
  {
    fs::file_status fileStatus = fs::status(filePath);
    std::ifstream file(filePath);
    std::istringstream iss;

    // reading units file file
    std::getline(file, line);
    gold = std::stol(line);
    // reading blue Base constructor
    iss.clear();
    std::getline(file, line);

    iss.str(line);
    iss >> readTeam >> readType >> readID >> readX >> readY >> readHp >> readDeployType >> readRemainingTime >> setIdCounter;
    blueBase.readFromFile(readHp, readDeployType, readRemainingTime, setIdCounter, gold);

    // reading red Base constructor
    iss.clear();

    std::getline(file, line);
    gold = std::stol(line);

    std::getline(file, line);
    iss.str(line);
    iss >> readTeam >> readType >> readID >> readX >> readY >> readHp >> readDeployType >> readRemainingTime >> setIdCounter;
    std::cout << readTeam << readType << readID << readX << readY << readHp << std::endl;
    redBase.readFromFile(readHp, readDeployType, readRemainingTime, setIdCounter, gold);

    // reading units
    iss.clear();
    while (std::getline(file, line))
    {

      iss.str(line);
      iss >> readTeam >> readType >> readID >> readX >> readY >> readHp;

      if (readTeam == 'B')
      {
        bool boolTeam = true;
        blueUnits.push_back(Unit(readType, readID, boolTeam, readY, readX, readHp));
      }
      else if (readTeam == 'R')
      {
        bool boolTeam = false;
        redUnits.push_back(Unit(readType, readID, boolTeam, readY, readX, readHp));
      }
      iss.clear();
    }
    file.close();
  }

  catch (const std::filesystem::filesystem_error &e)
  {
    std::cout << e.what() << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    _getch();
  }
}

//*function to write save to text file, similar to writeUnits() but with added gold value for both players--------------------------TESTED OK
void writeSave()
{
  std::ofstream outputFile("saveFile.txt", std::ios::out);

  if (outputFile.is_open())
  {
    outputFile << blueBase.getGold() << std::endl;
    outputFile << blueBase.writeToFile() << std::endl;
    outputFile << redBase.getGold() << std::endl;
    outputFile << redBase.writeToFile() << std::endl;

    for (size_t i = 0; i < blueUnits.size(); i++)
    {
      outputFile << blueUnits[i].writeToFile() << std::endl;
    }
    for (size_t i = 0; i < redUnits.size(); i++)
    {
      outputFile << redUnits[i].writeToFile() << std::endl;
    }

    std::cout << "Game saved, window will close now." << std::endl;
    outputFile.close();
  }
  else
  {
    std::cout << "Error opening the save file." << std::endl;
    return;
  }
}

//* Function to read units info from file--------------------------------------------------TESTED OK (i think)
// TODO: uses chrono so need to change 4 linux
bool readUnits(int turnTIME)
{
  long gold;
  fs::path filePath;
  std::string line;
  char readTeam;
  char readType;
  int readID;
  int readX;
  int readY;
  int readHp;
  char readDeployType;
  int readRemainingTime;
  int setIdCounter;

  // assign path depending on team
  if (playerTeam == true)
  {
    filePath = readBlue;
  }
  else
  {
    filePath = readRed;
  }

  std::filesystem::path file(filePath);
  auto startTime = std::chrono::steady_clock::now();

  // waiting 4 file to appear
  while (!std::filesystem::exists(file))
  {
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

    if (elapsedSeconds >= turnTIME)
    {

      // TODO do something when the file doesn't appear
      //  If the file doesn't appear within the maximum wait time,

      return false;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }

  // If file appears within turnTIME:
  try
  {
    fs::file_status fileStatus = fs::status(filePath);
    std::ifstream file(filePath);
    std::istringstream iss;

    // reading units file file
    std::getline(file, line);
    gold = std::stol(line);
    // reading blue constructor
    iss.clear();
    std::getline(file, line);

    iss.str(line);
    iss >> readTeam >> readType >> readID >> readX >> readY >> readHp >> readDeployType >> readRemainingTime >> setIdCounter;
    if (playerTeam == true)
      blueBase.readFromFile(readHp, readDeployType, readRemainingTime, setIdCounter, gold);
    else
      blueBase.readFromFile(readHp, readDeployType, readRemainingTime, setIdCounter);

    // reading red constructor
    iss.clear();
    std::getline(file, line);

    iss.str(line);
    iss >> readTeam >> readType >> readID >> readX >> readY >> readHp >> readDeployType >> readRemainingTime >> setIdCounter;
    std::cout << readTeam << readType << readID << readX << readY << readHp << std::endl;
    if (playerTeam == true)
      redBase.readFromFile(readHp, readDeployType, readRemainingTime, setIdCounter);
    else
      redBase.readFromFile(readHp, readDeployType, readRemainingTime, setIdCounter, gold);
    iss.clear();

    // reading units
    while (std::getline(file, line))
    {

      iss.str(line);
      iss >> readTeam >> readType >> readID >> readX >> readY >> readHp;

      if (readTeam == 'B')
      {
        bool boolTeam = true;
        blueUnits.push_back(Unit(readType, readID, boolTeam, readY, readX, readHp));
      }
      else if (readTeam == 'R')
      {
        bool boolTeam = false;
        redUnits.push_back(Unit(readType, readID, boolTeam, readY, readX, readHp));
      }
      iss.clear();
    }
    file.close();
    // remove the file to prevent it from being wrotten in a wrong way
    if (std::remove(filePath.string().c_str()) == 0)
      std::cout << "Orders red!" << std::endl;
  }

  catch (const std::filesystem::filesystem_error &e)
  {
    std::cout << e.what() << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    _getch();
  }

  return true;
}

void relocateMenu()
{
  int size;
  int selectedId;
  int setcount = 0; // this counter is later multiplied by 10 to dislplay 10 units at a time

  if (playerTeam)
    size = blueUnits.size();
  else
    size = redUnits.size();
  while (true)
  {
    system("cls");
    // printBothMaps();
    listUnitsInfo(setcount);
    std::cout << "press 'e' to enter unit selection mode, tap 'n' for the next page, tap'p' for the previous page, or 'q' to quit. " << std::endl;
    char option = static_cast<char>(getch());
    if (option == 'q')
    {
      break; // quits the loop
    }
    else if (option == 'n')
    {
      if (setcount * 10 > size)
        setcount++;
    }
    else if (option == 'p')
    {
      if (setcount > 0)
        setcount--;
    }
    else if (option == 'e')
    {
      std::cout << "Please enter the Id number of the unit you would like to relocate: " << std::endl;
      std::cin >> selectedId;
      std::cout << std::endl;
      if (playerTeam == true)
      {
        auto it = std::find_if(blueUnits.begin(), blueUnits.end(), [selectedId](Unit &unit)
                               { return unit.getID() == selectedId; });

        if (it != blueUnits.end())
        {
          Unit &foundUnit = *it;
          relocateMap(foundUnit);
        }
        else
        {
          std::cout << "Invalid unit Id, press anything to go back" << std::endl;
          getch();
          break;
        }
      }
      else if (playerTeam == false)
      {
        auto it = std::find_if(redUnits.begin(), redUnits.end(), [selectedId](Unit &unit)
                               { return unit.getID() == selectedId; });

        if (it != redUnits.end())
        {
          Unit &foundUnit = *it;
          relocateMap(foundUnit);
        }
        else
        {
          std::cout << "Invalid unit Id, press anything to go back" << std::endl;
          getch();
          break;
        }
      }
    }
  }
}
//tested ok
void attackMenu()
{
  int size;
  int selectedId;
  int setcount = 0; // this counter is later multiplied by 10 to dislplay 10 units at a time

  if (playerTeam)
    size = blueUnits.size();
  else
    size = redUnits.size();
  while (true)
  {
    system("cls");
    // printBothMaps();
    std::cout << "Attack Orders" << std::endl;
    listUnitsInfo(setcount);
    std::cout << "press 'e' to enter unit selection mode, tap 'n' for the next page, tap'p' for the previous page, or 'q' to quit. " << std::endl;
    char option = static_cast<char>(getch());
    if (option == 'q')
    {
      break; // quits the loop
    }
    else if (option == 'n')
    {
      if (setcount * 10 < size)
        setcount++;
    }
    else if (option == 'p')
    {
      if (setcount > 0)
        setcount--;
    }
    else if (option == 'e')
    {
      std::cout << "Please enter the Id number of the unit you would like to command to attack: " << std::endl;
      std::cin >> selectedId;
      std::cout << std::endl;
      if (playerTeam == true)
      {
        auto it = std::find_if(blueUnits.begin(), blueUnits.end(), [selectedId](Unit &unit)
                               { return unit.getID() == selectedId; });

        if (it != blueUnits.end() )
        {
          Unit &foundUnit = *it;
          attackMap(foundUnit);
        }
        else
        {
          std::cout << "Invalid unit Id, press anything to go back" << std::endl;
          getch();
          break;
        }
      }
      else if (playerTeam == false)
      {
        auto it = std::find_if(redUnits.begin(), redUnits.end(), [selectedId](Unit &unit)
                               { return unit.getID() == selectedId; });

        if (it != redUnits.end())
        {
          Unit &foundUnit = *it;
          attackMap(foundUnit);
        }
        else
        {
          std::cout << "Invalid unit Id, press anything to go back" << std::endl;
          getch();
          break;
        }
      }
    }
  }
}
void attackMap(Unit &selectedUnit)
{
  std::size_t x;
  std::size_t y;
  system("cls");
  bool unitFound;
  std::vector<Unit *> targetUnits;
  if (playerTeam)
  {
    for (Unit &unit : redUnits)
    {
      if (selectedUnit.getRng() >= abs(selectedUnit.positionX() - unit.positionX()) + abs(selectedUnit.positionY() - unit.positionY()))
      {
        targetUnits.push_back(&unit);
      }
    }
  }
  else
  {
    for (Unit &unit : blueUnits)
    {
      if (selectedUnit.getRng() >= abs(selectedUnit.positionX() - unit.positionX()) + abs(selectedUnit.positionY() - unit.positionY()))
      {
        targetUnits.push_back(&unit);
      }
    }
  }

  for (std::size_t i = 0; i < row; ++i)
  {
    for (std::size_t j = 0; j < col; ++j)
    {
      unitFound = false;

      if (i == 34 && j == 34) // <-- Adjusted comparison here
      {
        std::cout << "\x1B[34m" << unitsMap[j][i] << "\x1B[0m";
        unitFound = true;
      }
      else if (i == 0 && j == 0) // <-- Adjusted comparison here
      {
        std::cout << "\x1B[31m" << unitsMap[j][i] << "\x1B[0m";
        unitFound = true;
      }
      else if (unitsMap[j][i] != '0' && unitsMap[j][i] != '6' && unitsMap[j][i] != '9')
      {

        // Check red units
        for (size_t k = 0; k < redUnits.size(); k++)
        {
          x = std::size_t(redUnits[k].positionX());
          y = std::size_t(redUnits[k].positionY());

          if (x == j && y == i) // <-- Adjusted comparison here
          {
            bool noneInRange = std::none_of(targetUnits.begin(), targetUnits.end(), [i, j](Unit *unitPtr)
                                            { return unitPtr->positionX() == i && unitPtr->positionY() == j; });
            if (!noneInRange)
            {
              std::cout << "\x1B[33m" << unitsMap[j][i] << "\x1B[0m";
              unitFound = true;
              break;
            }
            std::cout << "\x1B[31m" << unitsMap[j][i] << "\x1B[0m";
            unitFound = true;
            break;
          }
        }

        // Check blue units if red unit not found
        if (!unitFound)
        {
          for (size_t k = 0; k < blueUnits.size(); k++)
          {
            x = std::size_t(blueUnits[k].positionX());
            y = std::size_t(blueUnits[k].positionY());

            if (x == j && y == i) // <-- Adjusted comparison here
            {
              std::cout << "\x1B[34m" << unitsMap[j][i] << "\x1B[0m";
              unitFound = true;
              break;
            }
          }
        }

        // If unit not found, print regular character
        if (!unitFound)
        {

          std::cout << unitsMap[j][i];
        }
      }

      else
      {
        std::cout << unitsMap[j][i];
      }
    }
    std::cout << std::endl;
  }

  bool baseInRange;
  std::cout << "Please select one of enemy unit's Id's in range to give order to attack." << std::endl;
  std::cout << "Enemy units in range: " << std::endl;
  if (playerTeam)
  {
    if (selectedUnit.getRng() >= abs(selectedUnit.positionX() - 34) + abs(selectedUnit.positionY() - 34))
    {
      redBase.info();
      baseInRange = true;
    }
  }
  else if (!playerTeam)
  {
    if (selectedUnit.getRng() >= abs(selectedUnit.positionX() - 0) + abs(selectedUnit.positionY() - 0))
    {
      blueBase.info();
      baseInRange = true;
    }
  }

  for (Unit *unitPtr : targetUnits)
  {
    Unit &unit = *unitPtr;
    if (unit.getHp() > 0)
      unit.info();
  }
  std::cout << "Target's Id: " << std::endl;
  int targetId;
  std::cin >> targetId;

  bool wrongId = true;
  Unit *target;
  if (targetId == 0 && baseInRange == true)
  {
    if (playerTeam)
    {
      target = &redBase;
      wrongId = false;
    }
    else
    {
      target = &blueBase;
      wrongId = false;
    }
  }
  else
  {
    auto it = std::find_if(targetUnits.begin(), targetUnits.end(), [targetId](Unit *unitPtr)
                           { return unitPtr->getID() == targetId; });
    wrongId = false;
    target = *it;
  }
  // targetID good
  if (!wrongId)
  {

    int targetModifier;
    int attackerModifier = typeToModifierArr(selectedUnit.getUnitType());
    if (targetId == 0)
      targetModifier = 7;
    else
      targetModifier = typeToModifierArr(target->getUnitType());
    const int damage = damageTable[attackerModifier][targetModifier];

    target->takeDamage(damage);
    selectedUnit.setActive();
  }
  else
  {
    std::cout << "Incorrect Target's Id." << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    _getch();
  }
}