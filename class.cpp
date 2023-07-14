#include <iostream>
using namespace std;

int unitModifiers[7][5] = {
    //? format: 
    //{hp,spd,cost,range,timeOfDeployment}
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

class Unit
{
private:
    int ID;     // Unit ID
    char type;  // unit type
    int hpMax;  // max hp points for given unit type
    int hpCurr; // current hp point of the unit

    int spd;              // speed of the unit
    int cost;             // build cost of the unit
    int range;            // range of attack
    int timeOfDeployment; // time of deployment to the field
    int timeRemaining;    // time remaining for the unit to deploy
    bool active;          // indicates if the unit was activated this turn
    int x;                // x position of the unit
    int y;                // y position of the unit

public:
    Unit(char unitType, int id)
    { //! constructor
        Unit::type = unitType;
        Unit::ID = id;
        int tempType = typeToModifierArr(unitType); // using the predefined table of modifiers

        Unit::hpMax = unitModifiers[tempType][0];
        Unit::spd = unitModifiers[tempType][1];
        Unit::cost = unitModifiers[tempType][2];
        Unit::range = unitModifiers[tempType][3];
        Unit::timeOfDeployment = unitModifiers[tempType][4];

        Unit::hpCurr = Unit::hpMax;
        Unit::timeRemaining = Unit::timeOfDeployment;
    };

    int position()
    {
        return Unit::x, Unit::y;
    };

    void setActive()
    {
        Unit::active = true;
    };

    void damage(int damage)
    {
        Unit::hpCurr -= damage;
    };

    bool checkIfDead()
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
};
