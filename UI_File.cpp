
#include "UI_File.h"
#include <iostream>
#include <conio.h>
#include <chrono>
#include <fstream>
#include <filesystem>
#include <array>

namespace fs = std::filesystem;

const int row = 35, col = 35;

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
  std::array<std::array<char, col>, row> mapArr;
  fs::path filePath = "map.txt";

  try
  {
    if (fs::exists(filePath))
    {
      try
      {
        fs::file_status fileStatus = fs::status(filePath);
        std::ifstream file(filePath);
        for (std::size_t i = 0; i < row - 1; ++i)
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

// * print map function(mostly 4 testing but may reuse) -----------------------------------------------------------------------
void printMap(std::array<std::array<char, col>, row> mapArr)
{

  for (std::size_t i = 0; i < row - 1; ++i)
  {
    for (std::size_t j = 0; j < col; ++j)
    {
      std::cout << mapArr[i][j];
    }
    std::cout << std::endl;
  }
}

char mapMenu()
{
char input;
std::cout << "Press 1 to list your units with modifiers" << std::endl;
std::cout << "Press 2 give order to unit" << std::endl;
std::cout << "Press 3 to commence recruitment of unit" << std::endl;



input = static_cast<char>(getch());
return input;

}
