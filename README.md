# Captrue the Castle- C++ Terminal based Game
## Introduction:
The presented software is part of the recruitment task. It is a Terminal based game similar to the sort of chess with 35/35 tiles board, repsesented as an array of characters. The game is intended to be played by two players. the oveall goal is to destroy oponents base by producing units able to move and attack, gathering resources with specialised "wörker" unit, and protecting own base and resources from the enemy trying to achive the same goal. Game is turn-based, with the players performing actions one after another. 

The game has setup maximum turn limit that is set to 1000 turns. After reaching it the game will check victory conditions and pronounce the winning player. Those conditions are:
- Destroying enemy base by dealing damage with your units
  
- If no bases are destroyed at uppon reaching the turn limit, the number of units on the board is counted. The owner of the larger army wins the game.

The game is divided into three applications, that communicate with each other by generating and reading intended to eachother .txt files, that contain informations about state of the game and changes made. changing the file artificialy might break and crash the game, also will resault in the loss of honor. 

### The mediator
The mediator is program starting the game, serving as a relay and controling the data transfer between the player programs, performing end turn operations and checking if the victory condition has been met. it also implemens the turn clock and turn counter. Uppon starting the app the greeting message will appear. Later user will be asked if the save file will be provided. the save file can be generated at the main menu of the plaer program, to save the current state of the game for later. Mediator is sole application designed to be used by a human user, and calling program responsible for handling the game from the user perspective is done by via it's terminal window.

The mediator .exe file in order to work prolerly must be located at the same directory with following files:
- map.txt -text file cointaining 35x35 array of characters representing the map of terrain.
- PlayerRed.exe -.exe file responsible for handling the game for one of the players.
- PlayerBlue.exe- .exe file for second player.  

### The player
The player program is responsible for communication with the user, gathering commands, displaying info about current map layout and units statuses, and monitors inputed data in order to prevent from incorrect use. There are two programs, each for a diffrent player, and are ment to be used alternately as players switch places between turns. When the game is launched, and when turn is closed the program for according player will close, switchinng back to mediator.exe, which handles the in-between turns operations, and forwards the data to the other player program. They are distinguished by the title diplaying "Blue" or "Red" Army at the corresponding color.
## Startup 
When launching the game by running the Mediator.exe the greeting screen is displayed with a prompt to press any button to continue. Next, user is presented with the option to load save file, that is possible to generate during the game (note that save option is not fully tested, and might cause some issues). If the user decides to launch the new game he is asked to input the number of turns per game, that limits the game duration and will trigger the game over and check victory codntitions.  




## User inteface
### Home menu
### 1. Maps and unit list
### 2. Unit relocation menu
### 3.Unit attack menu
### 4. Base status and recruitment.
### 5  
