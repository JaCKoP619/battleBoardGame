#include <iostream>
#include <conio.h>
#include <cmath>
#include <string>
#include "unitClass.h"
#include "UI_File.h"
#include <vector>

std::vector<Unit> blueUnits;
std::vector<Unit> redUnits;

extern std::array<std::array<char, ROWS>, COLS> terainMap;
const int maxX = 35;
const int maxY = maxX;
const int unitModifiers[7][5] = {
    //? format:
    // *{hp,spd,cost,range,timeOfDeployment}
    {70, 5, 400, 1, 5}, // knights   "K"
    {60, 5, 250, 1, 3}, // Swordsman "S"
    {40, 2, 250, 5, 3}, // Archers   "A"
    {50, 2, 200, 2, 3}, // pikemans  "P"
    {90, 2, 500, 1, 4}, // Ram       "R"
    {50, 2, 800, 7, 6}, // Catapults "C"
    {20, 2, 100, 1, 2}  // Workers   "W"
};
//*Auxilary functions to convert char to an int tor array
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
    default:
        // throw std::runtime_error("Invalid UnitType (char)");
        return 9;
        break;
    }
};
//? Unit methods-----------------------------------------------------------------------------
Unit::Unit(char giveType, int id, bool assignTeam)
{ //! constructor============================================= TESTED OK=============
    unitType = giveType;
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
        x = maxX-1;
        y = maxY-1;
    }
    hp = hpMax;
};
//* returns unit type as char-------------------------------------------------------------TESTED OK-----------
char Unit::getUnitType()
{
    return unitType;
};

int Unit::positionX()
{
    return x;
};

int Unit::positionY()
{
    return y;
};
//* method to set iddle to false when unit conducted an attack
void Unit::setActive()
{
    Unit::iddle = false;
};

void Unit::takeDamage(int damage)
{
    Unit::hp -= damage;
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
//* method to manage finishing turn, with reseting modifiers and controll variables and managing gold collection if unit met the conditions
//*contains checkifDead() method, returns false if unit is dead, to be used with destructor method at the higher scope
bool Unit::turn()
{
    if (hp <= 0)
    {
        return false;
    }
    else
    {
        spd = spdMax;
        iddle = true;
        if (unitType == 'W' && terainMap[std::size_t(positionY())][std::size_t(positionX())] == '6')
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
    }
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

//* method for moving unit witch movement range check--------------------------------------------TESTED OK---------------
void Unit::relocate(int movX, int movY)
{
    if (movX >= maxX || movX < 0 || movY >= maxY || movY < 0)  //check if order is leading outside map range
    {
        std::cout << "Leaving map, belay that order!\n"<< std::endl;
    }
    else
    {
        if (spd >= (sqrt(pow(2.0, (x - movX))) + sqrt(pow(2.0, (y - movY)))))
        {

            x = movX;
            y = movY;
            spd-=(sqrt(pow(2.0, (x - movX))) + sqrt(pow(2.0, (y - movY))));
        }
        else
        {
            std::cout << "Exceeded unit's range!" << std::endl;
            std::cout << "pres any key to continue..." << std::endl;
            getch();
            system("cls");
        }
    }
};

//*?Base methods --------------------------------------------------------------------------
//! base constructor ---------------------------TESTED OK------------------------------------
Base::Base(bool assignTeam) : Unit('B', 0, assignTeam)
{
    spdMax = 0;
    range = 0;
    unitType = 'B';
    ID = 0;
    idCount = 1;
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
        x = maxX - 1;
        y = maxY - 1;
    }
    iddle = true;
    timeRemaining = 0;
};

Base redBase(false); // Base declaration with constructor for external use
Base blueBase(true);

//* display info about the base-------------------------------------------------TESTED OK
void Base::info()
{
    std::string typeStr;

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

        std::cout << "This is a BASE. Position: " << x << " / " << y << ". Hp: " << hp << "/" << hpMax << std::endl;
        std::cout << "Currently Deploying " << typeStr << " unit. Time left: " << timeRemaining << std::endl;
        std::cout << gold << " golden coins in the treasury.\n"
                  << std::endl;
    }
    else // Base is iddle
    {
        std::cout << "This is a BASE. Position: " << x << " / " << y << ". Hp: " << hp << std::endl;
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
//* method for progressing the turn for the base--------------------------------TESTED OK
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
