#include <iostream>
#include <conio.h>
#include <cmath>
#include <string>
#include "unitClass.h"
#include <vector>

std::vector<Unit> blueUnits;
std::vector<Unit> redUnits;
const int maxX = 35;
const int maxY = maxX;
int unitModifiers[7][5] = {
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
// Auxilary functions to convert char to an int tor array
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
        return NULL;
        break;
    default:
        // throw std::runtime_error("Invalid UnitType (char)");
        return NULL;
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
        x = maxX;
        y = maxY;
    }
    hp = hpMax;
};

int Unit::positionX()
{
    return x;
};

int Unit::positionY()
{
    return y;
};

void Unit::setActive()
{
    Unit::iddle = false;
};

void Unit::takeDamage(int damage)
{
    Unit::hp -= damage;
};

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

//* method to display info about the unit (possibly for listing units)-----TESTED OK---------------------
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

//* method for moving unit witch movement range check-----------------------------------------------------------
void Unit::relocate(int movX, int movY)
{
    if (movX>maxX || movX<0 ||movY>maxY || movY<0)
    {
        std::cout<<"Leaving map, belay that order!\n"<<std::endl;
    }
    else
    {
        if (spd >= (sqrt(pow(2.0, (x - movX))) + sqrt(pow(2.0, (y - movY)))))
        {

            x = movX;
            y = movY;
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
    unitType = 'B';
    ID = 0;
    idCount = 1;
    team = assignTeam;
    hp = hpMax = 200;
    gold = 1000; // starting gold
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
void Base::relocate(int movX, int movY){
    // does nothing
};

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

void Base::addGold(int amount)
{
    gold += amount;
};

//'Base' method for unit recruitment---------------------------TESTED OK------------------------------------
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
//* method for progressing the turn for the base------------------------------------------------TESTED OK
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
                timeRemaining = NULL;
                idCount++;
                deployedUnit = NULL;
            }
            else
            {
                redUnits.push_back(Unit(deployedUnit, idCount, team));
                iddle = true;
                timeRemaining = NULL;
                idCount++;
                deployedUnit = NULL;
            }
        }
    }
};
