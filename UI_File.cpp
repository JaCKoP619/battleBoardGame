
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

// TODO: temp bool team variable 4 testing
bool playerTeam = true;
// namespace and paths for unit txt files for both teams
namespace fs = std::filesystem;
fs::path readRed = "list4Red.txt";
fs::path readBlue = "list4Blue.txt";
fs::path mapFile = "map.txt";

extern std::vector<Unit> blueUnits;
extern std::vector<Unit> redUnits;
extern const int unitModifiers[7][5];

int row = int(ROWS);
int col = int(COLS);
//* maps: terrain and strategic
std::array<std::array<char, ROWS>, COLS> terainMap;
std::array<std::array<char, ROWS>, COLS> unitsMap;
//* opening text message display and wait for input to carry on---------------------------------------------------------------TESTED OK----------
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
  do
  {
    std::cout << "would you like to load saved file? (not implemented yet) If not, program will start a new game.\n Y/N?" << std::endl;
    input = static_cast<char>(getch());
    system("cls");
  } while (input != 'n');
}
//* read map out of trxt file function ---------------------------------------------------------------------------------------TESTED OK----------
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
            file >> terainMap[i][j];
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

// * print map function(mostly 4 testing but may reuse) ---------------------------------------------------------------------
void printMap()
{

  for (std::size_t i = 0; i < row; ++i)
  {
    for (std::size_t j = 0; j < col; ++j)
    {
      std::cout << terainMap[i][j];
    }
    std::cout << std::endl;
  }
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
    if (unitsMap[x][y] == '0' || unitsMap[x][y] == '6')
    {
      unitsMap[x][y] = blueUnits[i].getUnitType();
    }
    else if (unitsMap[x][y] == 'K' || unitsMap[x][y] == 'S' || unitsMap[x][y] == 'A' || unitsMap[x][y] == 'P' || unitsMap[x][y] == 'R' || unitsMap[x][y] == 'C' || unitsMap[x][y] == 'W' || unitsMap[x][y] == 'B')
    {
      unitsMap[x][y] = 'M';
    }
  }
  for (std::size_t i = 0; i < redUnits.size(); i++)
  {
    x = std::size_t(redUnits[i].positionX());
    y = std::size_t(redUnits[i].positionY());
    if (unitsMap[x][y] == '0' || unitsMap[x][y] == '6')
    {
      unitsMap[x][y] = redUnits[i].getUnitType();
    }
    else if (unitsMap[x][y] == 'K' || unitsMap[x][y] == 'S' || unitsMap[x][y] == 'A' || unitsMap[x][y] == 'P' || unitsMap[x][y] == 'R' || unitsMap[x][y] == 'C' || unitsMap[x][y] == 'W' || unitsMap[x][y] == 'B')
    {
      unitsMap[x][y] = 'M';
    }
  }
};

char Menu()
{
  char input;
  std::cout << "Press 1 to get strategic information, along with maps and list of your units." << std::endl;
  std::cout << "Press 2 give order to relocate to unit." << std::endl;
  std::cout << "Press 3 give order to relocate to unit" << std::endl;
  std::cout << "Press 4 to check your base status and recruitment menu." << std::endl;
  std::cout << "Press 5 to send orders to your men." << std::endl;
  std::cout << "Press 6 to create save file." << std::endl;

  input = static_cast<char>(getch());
  return input;
};
void recruitmentMenu()
{
  char input;
  system("cls");
  if (playerTeam == true)
  {
    blueBase.info();
    if (blueBase.getStatus() == true)
    {
      std::cout << "Base is not recruiting at this moment. Would you like to begin recruitment? Y/N" << std::endl;
      input = static_cast<char>(getch());
      switch (input)
      {
      case 'y':
        std::cout << "Input:  | Unit:   |  HP:  | Speed: |  Cost: | Range| Time of deployment" << std::endl;
        std::cout << "1.      |Knight   |  " << unitModifiers[0][0] << "   | " << unitModifiers[0][1] << "      |  " << unitModifiers[0][2] << "   | " << unitModifiers[0][3] << "    | " << unitModifiers[0][4] << " turns" << std::endl;
        std::cout << "2.      |Swordsman|  " << unitModifiers[1][0] << "   | " << unitModifiers[1][1] << "      |  " << unitModifiers[1][2] << "   | " << unitModifiers[1][3] << "    | " << unitModifiers[1][4] << " turns" << std::endl;
        std::cout << "3.      |Archers  |  " << unitModifiers[2][0] << "   | " << unitModifiers[2][1] << "      |  " << unitModifiers[2][2] << "   | " << unitModifiers[2][3] << "    | " << unitModifiers[2][4] << " turns" << std::endl;
        std::cout << "4.      |Pikemans |  " << unitModifiers[3][0] << "   | " << unitModifiers[3][1] << "      |  " << unitModifiers[3][2] << "   | " << unitModifiers[3][3] << "    | " << unitModifiers[3][4] << " turns" << std::endl;
        std::cout << "5.      |Ram      |  " << unitModifiers[4][0] << "   | " << unitModifiers[4][1] << "      |  " << unitModifiers[4][2] << "   | " << unitModifiers[4][3] << "    | " << unitModifiers[4][4] << " turns" << std::endl;
        std::cout << "6.      |Catapults|  " << unitModifiers[5][0] << "   | " << unitModifiers[5][1] << "      |  " << unitModifiers[5][2] << "   | " << unitModifiers[5][3] << "    | " << unitModifiers[5][4] << " turns" << std::endl;
        std::cout << "7.      |Workers  |  " << unitModifiers[6][0] << "   | " << unitModifiers[6][1] << "      |  " << unitModifiers[6][2] << "   | " << unitModifiers[6][3] << "    | " << unitModifiers[6][4] << " turns" << std::endl;
      case 'n':
        break;
      }
    }
  }
}

//*function printing unitMap array, with checking units aligance and changing print colour for them, also sets 'M' value to indicate multiple units at the same position, TESTED OK
void printUnitMap()
{
  std::size_t x;
  std::size_t y;
  bool unitFound;

  for (std::size_t i = 0; i < row; ++i)
  {
    for (std::size_t j = 0; j < col; ++j)
    {
      if (unitsMap[i][j] != '0' && unitsMap[i][j] != '6' && unitsMap[i][j] != '9')
      {
        unitFound = false;

        // Check red units
        for (size_t k = 0; k < redUnits.size(); k++)
        {
          x = std::size_t(redUnits[k].positionX());
          y = std::size_t(redUnits[k].positionY());

          if (x == i && y == j) // <-- Adjusted comparison here
          {
            std::cout << "\x1B[31m" << unitsMap[i][j] << "\x1B[0m";
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

            if (x == i && y == j) // <-- Adjusted comparison here
            {
              std::cout << "\x1B[34m" << unitsMap[i][j] << "\x1B[0m";
              unitFound = true;
              break;
            }
          }
        }

        // If unit not found, print regular character
        if (!unitFound)
        {
          std::cout << unitsMap[i][j];
        }
      }
      else
      {
        std::cout << unitsMap[i][j];
      }
    }
    std::cout << std::endl;
  }
}

//* Function to conviniently print both maps at same level, with keeping their funcionality ------------------------------TESTED OK
void printBothMaps()
{
  std::size_t x;
  std::size_t y;
  std::cout << "Terrain map:                                              Unit Positions map:" << std::endl;
  for (std::size_t i = 0; i < row; ++i)
  {
    for (std::size_t j = 0; j < col; ++j)
    {
      std::cout << terainMap[i][j];
    }
    std::cout << "                       ";
    for (std::size_t j = 0; j < col; ++j)
    {
      if (unitsMap[i][j] != '0' && unitsMap[i][j] != '6' && unitsMap[i][j] != '9')
      {
        bool unitFound = false;

        for (size_t k = 0; k < redUnits.size(); k++)
        {
          x = std::size_t(redUnits[k].positionX());
          y = std::size_t(redUnits[k].positionY());
          if (34 == i && 34 == j)
          {
            std::cout << "\x1B[31m" << unitsMap[i][j] << "\x1B[0m";
            unitFound = true;
            break;
          }
          if (x == i && y == j)
          {
            std::cout << "\x1B[31m" << unitsMap[i][j] << "\x1B[0m";
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
              std::cout << "\x1B[34m" << unitsMap[i][j] << "\x1B[0m";
              unitFound = true;
              break;
            }
            else if (x == i && y == j)
            {
              std::cout << "\x1B[34m" << unitsMap[i][j] << "\x1B[0m";
              unitFound = true;
              break;
            }
          }
        }

        if (!unitFound)
        {
          std::cout << unitsMap[i][j];
        }
      }
      else
      {
        std::cout << unitsMap[i][j];
      }
    }
    std::cout << std::endl;
  }
}

void listUnitsInfo(bool team)
{
  system("cls");

  printBothMaps();
  std::cout << std::endl;
  if (team == true)
  {
     blueBase.info();
    for (size_t i = 0; i < blueUnits.size(); i++)
    {
      blueUnits[i].info();
    }
  }
  else
  {
    redBase.info();
    for (size_t i = 0; i < redUnits.size(); i++)
    {
      blueUnits[i].info();
    }
  }
}

void writeUnits(bool team)
{
  if (team == true)
  {
    std::ofstream outputFile("list4Blue.txt", std::ios::out);

    if (outputFile.is_open())
    {
      outputFile << blueBase.getGold() << std::endl;
      outputFile << blueBase.writeToFile() << std::endl;
      outputFile << redBase.writeToFile() << std::endl;

      for (size_t i = 0; i < blueUnits.size(); i++)
      {
        outputFile << blueUnits[i].writeToFile() << std::endl;
      }
      for (size_t i = 0; i < redUnits.size(); i++)
      {
        outputFile << redUnits[i].writeToFile() << std::endl;
      }
    }
    else
    {
      std::cout << "Error opening the file." << std::endl;
      return;
    }
    outputFile.close();
  }
  else
  {
    std::ofstream outputFile("list4Red.txt", std::ios::out);
    if (outputFile.is_open())
    {

      outputFile << blueBase.getGold() << std::endl;
      outputFile << blueBase.writeToFile() << std::endl;
      outputFile << redBase.writeToFile() << std::endl;

      for (size_t i = 0; i < blueUnits.size(); i++)
      {
        outputFile << blueUnits[i].writeToFile() << std::endl;
      }
    }
    else
    {
      std::cout << "Error opening the file." << std::endl;
      return;
    }
    outputFile.close();
  }
}

//* Function to read units info from file
// TODO: uses chrono so need to change 4 linux
bool readUnits(bool auxteam, int turnTIME)
{
  long gold;
  extern fs::path readBlue;
  extern fs::path readRed;
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
  if (auxteam == true)
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
      // If the file doesn't appear within the maximum wait time,
      // execute a different function and return false.
      return false;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
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
    std::getline(file, line);

    iss.str(line);
    iss >> readTeam >> readType >> readID >> readX >> readY >> readHp >> readDeployType >> readRemainingTime >> setIdCounter;
    if (auxteam == true)
       blueBase.readFromFile(readHp, readDeployType, readRemainingTime, setIdCounter, gold);
    else
       blueBase.readFromFile( readHp, readDeployType, readRemainingTime, setIdCounter);

    // reading red constructor
    std::getline(file, line);

    iss.clear();
    iss.str(line);
    iss >> readTeam >> readType >> readID >> readX >> readY >> readHp >> readDeployType >> readRemainingTime >> setIdCounter;
    std::cout<<readTeam<<readType<<readID<<readX<<readY<<readHp<<std::endl;
    if (auxteam == true)
      redBase.readFromFile(true, readHp, readDeployType, readRemainingTime, setIdCounter);
    else
      redBase.readFromFile(readHp, readDeployType, readRemainingTime, setIdCounter,gold);

    while (std::getline(file, line))
    {
      iss.clear();
      iss.str(line);
      iss >> readTeam >> readType >> readID >> readX >> readY >> readHp;
      std::cout<<readTeam<<readType<<readID<<readX<<readY<<readHp<<std::endl;
      if (readTeam == 'B')
      {
        bool boolTeam = true;
        blueUnits.push_back(Unit(readType, readID, boolTeam, readY, readX, readHp));
      }
      else
      {
        bool boolTeam = false;
        redUnits.push_back(Unit(readType, readID, boolTeam, readY, readX, readHp));
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

  return true;
}
