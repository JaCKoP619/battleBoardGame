#include <iostream>
#include <cmath>
#include <string>
#include "unitClass.h"
#include "UI_File.h"
#include <vector>
#include <algorithm>
std::vector<Unit> blueUnits;
std::vector<Unit> redUnits;

extern std::array<std::array<char, ROWS>, COLS> terainMap;
const int maxX = 34;
const int maxY = maxX;
//* unit modyfiers like HP spd etc. table, implemented in Unit constructor to easily get the data
const int unitModifiers[7][5] = {
    //? format:
    // *{hp,spd,cost,range,timeOfDeployment}
    {70, 5, 400, 1, 5}, // Knights   "K"
    {60, 5, 250, 1, 3}, // Swordsman "S"
    {40, 2, 250, 5, 3}, // Archers   "A"
    {50, 2, 200, 2, 3}, // Pikemans  "P"
    {90, 2, 500, 1, 4}, // Ram       "R"
    {50, 2, 800, 7, 6}, // Catapults "C"
    {20, 2, 100, 1, 2}  // Workers   "W"
};
//* damage table, relations of attack values between different types of units
const int damageTable[7][8] = {
    // Knight,Swordman,Archer,Pikeman,Ram,Catapult,Worker,Base
    {35, 35, 35, 35, 35, 50, 35, 35}, // Knight
    {30, 30, 30, 20, 20, 30, 30, 30}, // swordsman
    {15, 15, 15, 15, 10, 10, 15, 15}, // Archers
    {35, 15, 15, 15, 15, 10, 15, 10}, // Pikemans
    {40, 40, 40, 40, 40, 40, 40, 50}, // Ram
    {10, 10, 10, 10, 10, 10, 10, 50}, // Catapults
    {5, 5, 5, 5, 5, 5, 5, 1}};        // Workers
//*Auxilary functions to convert char to an int for unitModifiers array
int typeToModifierArr(char chartype)
{
    switch (chartype)
    {
    case 'K':
        return 0;
        break;
    case 'S':
        return 1;
        break;
    case 'A':
        return 2;
        break;
    case 'P':
        return 3;
        break;
    case 'R':
        return 4;
        break;
    case 'C':
        return 5;
        break;
    case 'W':
        return 6;
        break;
    case 'B':
        return 7;
        break;
    default:
        // throw std::runtime_error("Invalid UnitType (char)");
        return 9;
        break;
    }
};

//? Unit methods-----------------------------------------------------------------------------
//! starting constructor============================================= TESTED OK=============
Unit::Unit(char setType, int id, bool assignTeam)
{
    unitType = setType;
    ID = id;
    int tempType = typeToModifierArr(unitType); // using the predefined table of modifiers

    hpMax = unitModifiers[tempType][0];
    spd = unitModifiers[tempType][1];
    cost = unitModifiers[tempType][2];
    range = unitModifiers[tempType][3];
    team = assignTeam;
    iddle = true;

    if (team == true)

    {
        x = 0;
        y = 0;
    }
    else
    {
        x = maxX;
        y = maxY;
    }
    hp = hpMax;
};
//! midgame constructor for .txt file comunication
Unit::Unit(char setType, int setId, bool assignTeam, int setX, int setY, int setHp)
{
    unitType = setType;
    ID = setId;
    int tempType = typeToModifierArr(unitType); // using the predefined table of modifiers

    hpMax = unitModifiers[tempType][0];
    spd = unitModifiers[tempType][1];
    cost = unitModifiers[tempType][2];
    range = unitModifiers[tempType][3];
    team = assignTeam;
    iddle = true;
    x = setX;
    y = setY;
    hp = setHp;
};
//* returns unit type as char-------------------------------------------------------------TESTED OK-----------
char Unit::getUnitType()
{
    return unitType;
};
//*simple return x and y position values------------------------------------------------------TESTED OK-----------
int Unit::positionX()
{
    return x;
};
int Unit::positionY()
{
    return y;
};
//* method to set iddle to false when unit conducted an attack
// TODO: implement properly and test, add damage table
void Unit::takeDamage(int damage)
{
    Unit::hp -= damage;
    std::cout << "Unit " << ID << " has taken damage of " << damage << " and now has" << hp << " HP" << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    getchar();
};
//* checking if unit hp is less than 0, implemented inside turn(),
bool Unit::checkIfDead()
{
    if (Unit::hp <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
};
//* method to manage finishing turn, with reseting modifiers and controll variables and managing gold collection if unit met the conditions-------TESTED OK----
bool Unit::turn()
{

    spd = spdMax;
    iddle = true;
    if (unitType == 'W' && terainMap[std::size_t(positionX())][std::size_t(positionY())] == '6')
    {
        if (team == true)
        {
            blueBase.addGold();
        }
        else
        {
            redBase.addGold();
        }
    }
    return true;
};
//* method to display info about the unit (possibly for listing units)--------------------------TESTED OK---------------
void Unit::info()
{
    std::string typeStr;
    std::string activeStr;
    if (iddle != true)
        activeStr = "Active";

    else
        activeStr = "Iddle";

    switch (unitType)
    {
    case 'K':
        typeStr = "Knight";
        break;
    case 'S':
        typeStr = "Swordsman";
        break;
    case 'A':
        typeStr = "Archer";
        break;
    case 'P':
        typeStr = "Pikeman";
        break;
    case 'R':
        typeStr = "Ram";
        break;
    case 'C':
        typeStr = "Catapult";
        break;
    case 'W':
        typeStr = "Worker";
        break;
    default:
        // throw std::runtime_error("Invalid UnitType (char)");
        break;
    }

    std::cout << "Unit ID: " << ID << " is a " << typeStr << ". Position: " << x << "/" << y << ". Speed: " << spd << ". Range: " << range << std::endl;
    std::cout << "Currently " << activeStr << " and has " << hp << "/" << hpMax << " hp.\n"
              << std::endl;
};
//*returns bool iddle
bool Unit::getStatus()
{
    return iddle;
}
//* method for moving unit witch movement range check--------------------------------------------TESTED OK---------------
// TODO: implement blocking movement to space occupied by enemy unit
void Unit::relocate(int movX, int movY)
{
    bool free;
    // check if ordered tile is occupied by enemy unit
    if (playerTeam == true)
    {
        free = std::none_of(redUnits.begin(), redUnits.end(), [&](Unit &unit)
                            { return (unit.positionX() == movX && unit.positionY() == movY); });
    }
    else if (playerTeam == false)
    {
        free = std::none_of(blueUnits.begin(), blueUnits.end(), [&](Unit &unit)
                            { return (unit.positionX() == movX && unit.positionY() == movY); });
    }

    if (movX > maxX || movX < 0 || movY > maxY || movY < 0) // check if order is leading outside map range
    {
        std::cout << "Leaving map, belay that order!\n"
                  << std::endl;
        std::cout << "press any key to continue..." << std::endl;
        getchar();
    }
    else if (terainMap[std::size_t(movX)][std::size_t(movY)] == '9') // check for inpassable terrain
    {

        std::cout << "Inaccessible terrain, belay that order!\n"
                  << std::endl;
        std::cout << "press any key to continue..." << std::endl;
        getchar();
    }
    else if (spd < abs(x - movX) + abs(y - movY)) // check if outside range of unit movment
    {
        std::cout << "Exceeded unit's range!" << std::endl;
        std::cout << "press any key to continue..." << std::endl;
        getchar();
    }
    else if (free == false)
    {
        std::cout << "Tile is occupied by the enemy" << std::endl;
        std::cout << "pres any key to continue..." << std::endl;
        getchar();
    }
    else if (spd >= abs(x - movX) + abs(y - movY))
    {

        spd -= (abs(x - movX) + abs(y - movY)); // formula for range

        x = movX;
        y = movY;
        std::cout << "Unit relocated sucesfully" << std::endl;
        std::cout << "pres any key to continue..." << std::endl;
    }
};
//* method for changing unit status after attack to forbid more than one attack per turn
void Unit::setActive()
{

    iddle = false;
}
//* simple return membe values ------------------------------------------------------------------TESTED OK---------------
int Unit::getSpd()
{
    return spd;
}
int Unit::getRng()
{
    return range;
}
bool Unit::getTeam()
{
    return team;
}
int Unit::getID() const
{
    return ID;
}
int Unit::getHp()
{
    return hp;
}
//* prepare string for writing to .txt file--------------------------------------------------TESTED OK---------------
std::string Unit::writeToFile()
{
    std::string output;
    if (team == true)
        output = "B ";
    else
        output = "R ";

    output += (std::string(1, getUnitType()) + " " + std::to_string(getID()) + " " + std::to_string(positionX()) + " " + std::to_string(positionY()) + " " + std::to_string(getHp()));
    return output;
}
//*? BASE methods -----------------------------------------------------------------------------------------------------------------
//! base starting constructor ---------------------------TESTED OK------------------------------------
Base::Base(bool assignTeam) : Unit('B', 0, assignTeam)
{
    deployedUnit = '0';
    spdMax = 0;
    range = 0;
    unitType = 'B';
    ID = 0;
    idCount = 2;
    team = assignTeam;
    hp = hpMax = 200; // starting hp points, hpMax is constant
    gold = 2000;      // starting gold
    if (team == true)
    { // setting base position depending on a team
        x = 0;
        y = 0;
    }
    else
    {
        x = maxX;
        y = maxY;
    }
    iddle = true;
    timeRemaining = 0;
};
//! constructor for friendly base for reading from textfile
Base::Base(bool assignTeam, int setHp, char setDeployedType, int setTimeRemaining, long setGold, int setIdCount) : Unit('B', 0, assignTeam)
{

    spdMax = 0;
    range = 0;
    unitType = 'B';
    ID = 0;
    idCount = setIdCount;
    team = assignTeam;
    hpMax = 200;
    hp = setHp;     // sethp from text file
    gold = setGold; // starting gold
    if (team == true)
    { // setting base position depending on a team
        x = 0;
        y = 0;
    }
    else
    {
        x = maxX - 1;
        y = maxY - 1;
    }
    if (setDeployedType == '0')
    {
        iddle = true;
        timeRemaining = 0;
    }
    else
    {
        iddle = false;
        timeRemaining = setTimeRemaining;
        deployedUnit = setDeployedType;
    }
}

//! constructor for enemy base  reading from textfile
Base::Base(bool assignTeam, int setHp, char setDeployedType, int setTimeRemaining, int setIdCount) : Unit('B', 0, assignTeam)
{
    spdMax = 0;
    range = 0;
    unitType = 'B';
    ID = 0;
    idCount = setIdCount;
    team = assignTeam;
    hpMax = 200;
    hp = setHp;  // sethp from text file
    gold = 2000; // starting gold
    if (team == true)
    { // setting base position depending on a team
        x = 0;
        y = 0;
    }
    else
    {
        x = maxX - 1;
        y = maxY - 1;
    }
    if (setDeployedType == '0')
    {
        iddle = true;
        timeRemaining = 0;
    }
    else
    {
        iddle = false;
        timeRemaining = setTimeRemaining;
        deployedUnit = setDeployedType;
    }
}
//* display info about the base-------------------------------------------------TESTED OK
void Base::info()
{
    std::string typeStr;
    std::string teamStr;
    if (team == true)
        teamStr = "\x1B[34mBlue team Base.\x1B[0m ";
    else
        teamStr = "\x1B[31mRed team Base.\x1B[0m ";

    if (iddle != true)
    {
        switch (deployedUnit)
        {
        case 'K':
            typeStr = "Knight";
            break;
        case 'S':
            typeStr = "Swordsman";
            break;
        case 'A':
            typeStr = "Archer";
            break;
        case 'P':
            typeStr = "Pikeman";
            break;
        case 'R':
            typeStr = "Ram";
            break;
        case 'C':
            typeStr = "Catapult";
            break;
        case 'W':
            typeStr = "Worker";
            break;
        case 'B':
            typeStr = "Base";
            break;
        default:
            // throw std::runtime_error("Invalid UnitType (char)");
            break;
        }

        std::cout << "Unit ID: " << ID << ". This is a " << teamStr << "Position: " << x << " / " << y << ". Hp: " << hp << "/" << hpMax << std::endl;
        std::cout << "Currently Deploying " << typeStr << " unit. Time left: " << timeRemaining << std::endl;
        std::cout << gold << " golden coins in the treasury.\n"
                  << std::endl;
    }
    else // Base is iddle
    {
        std::cout << "Unit ID: " << ID << ". This is a " << teamStr << "Position: " << x << " / " << y << ". Hp: " << hp << std::endl;
        std::cout << "Currently Iddle" << std::endl;
        std::cout << gold << " golden coins in the treasury.\n"
                  << std::endl;
    }
};

//*designed for worker to call, adds 50gold to the treasury---------------------TESTED OK
void Base::addGold()
{
    gold += 50;
};


//*'Base' method for unit recruitment-------------------------------------------TESTED OK--
void Base::recruitUnit(char giveType)
{
    int tempType;
    if (iddle == true)
    {

        deployedUnit = giveType;
        tempType = typeToModifierArr(deployedUnit); // using the predefined table of modifiers
        int amount = unitModifiers[tempType][2];
        if (gold >= amount)
        {
            gold -= amount;
            iddle = false; // giving order to base
            timeRemaining = unitModifiers[tempType][4];
        }
        else
        {
            std::cout << "The treasury is empty, my lord!\n"
                      << std::endl;
        }
    }
};
//*workaround method for reading and updating the base class from textfile-------------------------------TESTED OK
void Base::readFromFile(int setHp, char setDeployedType, int setTimeRemaining, int setIdCount, long setGold)
{
    hp = setHp;
    deployedUnit = setDeployedType;
    timeRemaining = setTimeRemaining;
    
    if (timeRemaining > 0)
        iddle = false;

    gold = setGold;
    idCount = setIdCount;
}

//* method for progressing the turn for the base, mostly for recruitment --------------------------------TESTED OK
// TODO maybe will implement something global, this one is for testing 4 now
void Base::turn()
{
    if (iddle == false)
    {
        timeRemaining -= 1;
        if (timeRemaining == 0)
        {
            if (team == true)
            {
                blueUnits.push_back(Unit(deployedUnit, idCount, team));
                iddle = true;
                timeRemaining = 0;
                idCount++;
                deployedUnit = '0';
            }
            else
            {
                redUnits.push_back(Unit(deployedUnit, idCount, team));
                iddle = true;
                timeRemaining = 0;
                idCount++;
                deployedUnit = '0';
            }
        }
    }
};
//* some methods for returning members values from the base class---------------------------------TESTED OK
char Base::getDeployedUnitType()
{
    return deployedUnit;
}
int Base::getID()
{
    return ID;
}
char Base::getUnitType()
{
    return unitType;
}
long Base::getGold()
{
    return gold;
}
int Base::getIdCount()
{
    return idCount;
}
int Base::getTimeRemaining()
{
    return timeRemaining;
}
//* creates string to write to comm file describing the base obiect--------------------------TESTED OK
std::string Base::writeToFile()
{
    std::string output;
    if (team == true)
        output = "B ";
    else
        output = "R ";

    output += (std::string(1, getUnitType()) + " " + std::to_string(getID()) + " " + std::to_string(positionX()) + " " + std::to_string(positionY()) + " " + std::to_string(getHp()) + " " + getDeployedUnitType() + " " + std::to_string(getTimeRemaining()) + " " + std::to_string(getIdCount()));
    return output;
}


//* base global class declaration,, it is in wierd place but can't put it in main, works here 
Base redBase(false); // Base declaration with constructor for external use
Base blueBase(true);