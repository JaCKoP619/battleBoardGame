
#include "UI_File.h"
#include "unitClass.h"
#include <iostream>
#include <conio.h>
#include <chrono>
#include <fstream>
#include <filesystem>
#include <array>

namespace fs = std::filesystem;
extern std::vector<Unit> blueUnits;
extern std::vector<Unit> redUnits;

std::array<std::array<char, ROWS>, COLS> mapArr;
const int row = 35, col = 35;
std::array<std::array<char, ROWS>, COLS> unitsMap;

//* opening text message display and wait for input to carry on---------------------------------------------------------------
void greet()

{
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
//* read map out of trxt file function ---------------------------------------------------------------------------------------
std::array<std::array<char, 35>, 35> readMap()
{
  fs::path filePath = "map.txt";

  try
  {
    if (fs::exists(filePath))
    {
      try
      {
        fs::file_status fileStatus = fs::status(filePath);
        std::ifstream file(filePath);
        for (std::size_t i = 0; i < row; ++i)
        {
          for (std::size_t j = 0; j < col; ++j)
          {
            file >> mapArr[i][j];
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
      if (fs::exists(filePath) == false)
      {
        throw std::runtime_error("Map file not found at path: " + filePath.string());
      }
    }
  }
  catch (const std::runtime_error &e)
  {
    std::cout << e.what() << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    _getch();
  }
  return mapArr;
}

// * print map function(mostly 4 testing but may reuse) ---------------------------------------------------------------------
void printMap()
{

  for (std::size_t i = 0; i < row; ++i)
  {
    for (std::size_t j = 0; j < col; ++j)
    {
      std::cout << mapArr[i][j];
    }
    std::cout << std::endl;
  }
}

void updateUnitMap()
{
  //  std::cout << blueUnits.size() << std::endl;
  //  size_t i = blueUnits.size()+1;
  //   std::cout << i << std::endl;

  std::size_t x;
  std::size_t y;

  unitsMap = mapArr;
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

char mapMenu()
{
  char input;
  std::cout << "Press 1 to list your units with modifiers" << std::endl;
  std::cout << "Press 2 give order to unit" << std::endl;
  std::cout << "Press 3 to commence recruitment of unit" << std::endl;

  input = static_cast<char>(getch());
  return input;
};

void printUnitMap()
{
  std::size_t x;
  std::size_t y;

  for (std::size_t i = 0; i < row; ++i)
  {
    for (std::size_t j = 0; j < col; ++j)
    {
      if (unitsMap[i][j] != '0' && unitsMap[i][j] != '6' && unitsMap[i][j] != '9')
      {
        bool unitFound = false;

        for (size_t k = 0; k < redUnits.size(); k++)
        {
          x = std::size_t(redUnits[k].positionX());
          y = std::size_t(redUnits[k].positionY());
          if (34 == j && 34 == i)
          {
            std::cout << "\x1B[31m" << unitsMap[i][j] << "\x1B[0m";
            unitFound = true;
            break;
          }
          if (x == j && y == i)
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
            if (0 == j && 0 == i)
            {
              std::cout << "\x1B[34m" << unitsMap[i][j] << "\x1B[0m";
              unitFound = true;
              break;
            }
            else if (x == j && y == i)
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
