# Captrue the Castle- C++ based Game
## Introduction:
The presented software is part of the recruitment task. It is a Terminal based game similar to the sort of chess with 35/35 tiles board, repsesented as an array of characters. The game is intended to be played by two players. the oveall goal is to destroy oponents base by producing units able to move and attack, gathering resources with specialised "wörker" unit, and protecting own base and resources from the enemy trying to achive the same goal. Game is turn-based, with the players performing actions one after another. 

The game has setup maximum turn limit that is set to 1000 turns. After reaching it the game will check victory conditions and pronounce the winning player. Those conditions are:
- Destroying enemy base by dealing damage with your units
  
- If no bases are destroyed at uppon reaching the turn limit, the number of units on the board is counted. The owner of the larger army wins the game.

The game is divided into three applications, that communicate with each other by generating and reading intended to eachother .txt files, that contain informations about state of the game and changes made. changing the file artificialy might break and crash the game, also might resault in the loss of honor. 

### The mediator

### The player

## User inteface
### Home menu
### 1. Maps and unit list
### 2. Unit relocation menu