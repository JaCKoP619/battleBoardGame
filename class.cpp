#include <iostream>
#include <conio.h>
#include "class.h"


int unitModifiers[7][5] = {
    //? format:
    // *{hp,spd,cost,range,timeOfDeployment}
    {70, 5, 400, 1, 5}, // knights   "K"
    {60, 5, 250, 1, 3}, // Swordsman "S"
    {40, 2, 250, 1, 3}, // Archers   "A"
    {50, 2, 200, 2, 3}, // pikemans  "P"
    {90, 2, 500, 1, 4}, // Ram       "R"
    {50, 2, 800, 7, 6}, // Catapults "C"
    {20, 2, 100, 1, 2}  // Workers   "W"
};

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
        throw std::runtime_error("Invalid UnitType (char)");
        break;
    }
}

Unit::Unit(char unitType, int id)
{ //! constructor
    type = unitType;
    ID = id;
    tempType = typeToModifierArr(unitType); // using the predefined table of modifiers

    hpMax = unitModifiers[tempType][0];
    spd = unitModifiers[tempType][1];
    cost = unitModifiers[tempType][2];
    range = unitModifiers[tempType][3];
    timeOfDeployment = unitModifiers[tempType][4];

    hpCurr = hpMax;
    timeRemaining = timeOfDeployment;
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
    Unit::active = true;
};

void Unit::damage(int damage)
{
    Unit::hpCurr -= damage;
};

bool Unit::checkIfDead()
{
    if (Unit::hpCurr <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
};
