#ifndef CLASS_H
#define CLASS_H
#include <vector>
#include <string>

extern int typeToModifierArr(char chartype);
extern int typeToModifier(char chartype);
extern const int unitModifiers[7][5];
extern const int damageTable[7][8];
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
        int spdMax;    // unit default movement range
        int spd;       // unit movement speed decrementing while moving
        int range;     // unit attack range

private:
        int cost; // unit deployment cost

public:
        Unit(char unitType, int ID, bool assignTeam);
        Unit(char unitType, int ID, bool assignTeam, int setX, int setY, int setHp);
        int positionX(); // returns x position of unit
        int positionY(); // returns y position of unit
        void setActive();
        void takeDamage(int damage);
        bool checkIfDead();
        bool turn();
        void relocate(int movX, int movY); // implementation of unit movement witch movement range (int spd) checking
        virtual void info();
        char getUnitType();
        bool getStatus();
        void attack();
        std::string writeToFile();
        int getID() const;
        int getHp();
        int getSpd();
        int getRng();
        bool getTeam();
       
};
class Base : public Unit
{

protected:
        long gold;         // current gold
        int timeRemaining; // recruitment time remaining
        char deployedUnit; // type of unit being deployed
        int idCount;
        int ID;
        char unitType;


              // number of units deployed, won't be subtracted when unit is killed
public:
        Base(bool assignTeam);
        Base(bool assignTeam, int setHp, char setDeployedType, int setTimeRemaining,long setGold,int setIdCount);
        Base(bool assignTeam, int setHp, char setDeployedType, int setTimeRemaining,int setIdCount);
        void turn();
        void recruitUnit(char giveType);
        void info() override;
        void addGold();
        long getGold();
        std::string writeToFile();
        char getDeployedUnitType();
        int getID();
        char getUnitType();
        int getTimeRemaining();
        int getIdCount();
        void readFromFile( int setHp, char setDeployedType, int setTimeRemaining, int setIdCount, long setGold);
        

};

extern Base blueBase;
extern Base redBase;

extern std::vector<Unit> blueUnits;
extern std::vector<Unit> redUnits;
#endif