#ifndef CLASS_H
#define CLASS_H
#include <vector>

extern int typeToModifierArr(char chartype);
extern int typeToModifier(char chartype);
extern int unitModifiers[7][5];


class Unit
{
protected:
        bool team; // true for blue and false for red, just a binary expression, not a boolean as true for me and false for enemy.
        int ID;    // unit id, should
        int x;     // x position
        int y;     // y position
        int hpMax; // constant value for maximum hp for given unit type
        int hp;    // current hp, cant exceed hpMax

        bool iddle;    // info if unit has been activated this turn
        char unitType; // info about unit type

private:
        int spd;   // unit movement range for time of turn
        int cost;  // unit deployment cost
        int range; // unit attack range

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
        char getUnitType();
};
class Base : public Unit
{

protected:
        int hpMax;         // starting value of hp points
        int hp;            // currernt hp points, cannot exceed hpMax
        int gold;          // current gold
        int id;            // for base it's always 1
        int x;             // x position of base
        int y;             // y position of base
        int timeRemaining; // recruitment time remaining
        char deployedUnit; // type of unit being deployed
        int idCount;       // number of units deployed, won't be subtracted when unit is killed
public:
        int positionX(); // returns x position of unit
        int positionY(); // returns y position of unit
        Base(bool assignTeam);
        bool checkIfDead();
        void turn();
        void recruitUnit(char giveType);
        void info() override;
        void addGold(int amount);
        void relocate(int movX, int movY);

};


extern Base blueBase;
extern Base redBase;

extern std::vector<Unit> blueUnits;
extern std::vector<Unit> redUnits;
#endif