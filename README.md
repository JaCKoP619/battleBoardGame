# Captrue the Castle- C++ Terminal based Game
## Introduction:
The presented software is part of the recruitment task. It is a Terminal based game similar to the sort of chess with 35/35 tiles board, repsesented as an array of characters. The game is intended to be played by two players. the oveall goal is to destroy oponents base by producing units able to move and attack, gathering resources with specialised "wörker" unit, and protecting own base and resources from the enemy trying to achive the same goal. Game is turn-based, with the players performing actions one after another. 

The game has setup maximum turn limit that is set to 1000 turns. After reaching it the game will check victory conditions and pronounce the winning player. Those conditions are:
- Destroying enemy base by dealing damage with your units
  
- If no bases are destroyed at uppon reaching the turn limit, the number of units on the board is counted. The owner of the larger army wins the game.

The game is divided into three applications, that communicate with each other by generating and reading intended to eachother .txt files, that contain informations about state of the game and changes made. changing the file artificialy might break and crash the game, also will resault in the loss of honor. 

### The mediator
The mediator is program starting the game, serving as a relay and controling the data transfer between the player programs, performing end turn operations and checking if the victory condition has been met. it also implemens the turn clock and turn counter. Uppon starting the app the greeting message will appear. Later user will be asked if the save file will be provided. the save file can be generated at the main menu of the plaer program, to save the current state of the game for later. Mediator is sole application designed to be used by a human user, and calling program responsible for handling the game from the user perspective is done by via it's terminal window.

### The player
The player program is responsible for communication with the user, gathering commands, displaying info about current map layout and units statuses, and monitors inputed data in order to prevent from incorrect use. 


## User inteface
### Home menu
### 1. Maps and unit list
### 2. Unit relocation menu
