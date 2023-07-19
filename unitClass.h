#ifndef CLASS_H
#define CLASS_H

int typeToModifierArr(char chartype);

std::vector<Unit> blueUnits;
std::vector<Unit> redUnits;
class Unit
{
protected:
        bool team; // true for blue and false for red, just a binary expression, not a boolean as true for me and false for enemy.
        int ID;    // unit id, should
        int x;     // x position
        int y;     // y position
        int hpMax; // constant value for maximum hp for given unit type
        int hp;    // current hp, cant exceed hpMax

        bool active; // info if unit has been activated this turn
        char type;   // info about unit type

private:
        int spd;              // unit movement range for time of turn
        int cost;             // unit deployment cost
        int range;            // unit attack range
        int timeOfDeployment; // TODO dont know if will be used here or in the Base clas

public:
        Unit(char unitType, int ID, bool assignTeam);
        int positionX(); // returns x position of unit
        int positionY(); // returns y position of unit
        void setActive();
        void takeDamage(int damage);
        bool checkIfDead();
        bool turn();
        void relocate(int movX, int movY); // implementation of unit movement witch movement range (int spd) checking
        virtual void info();
};
class Base : public Unit
{

protected:
        bool iddle; // check if base is recruiting unit
        int hpMax;  // starting value of hp points
        int hp;     // currernt hp points, cannot exceed hpMax
        int gold;   // current gold
        bool team;  // same as for unit class
        int id;     // for base it's always 1
        int x;      // x position of base
        int y;      // y position of base
        int timeRemaining;
        char deployedUnit; // type of unit being deployed
        int idCount;        // number of units deployed, won't be subtracted when unit is killed
public:
        Base(bool assignTeam);
        bool checkIfDead();
        void turn();
        void recruitUnit(char type, int id);
        void info() override;
};

#endif