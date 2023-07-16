#ifndef HEADER_H
#define HEADER_H

void greet();
int typeToModifierArr(char chartype);

class Unit
{
private:
        char type;
        int ID;
        int tempType;
        int x;
        int y;

        int hpMax;
        int spd;
        int cost;
        int range;
        int timeOfDeployment;
        int hpCurr;
        int timeRemaining;
        bool active;

public:
        Unit(char unitType, int ID);
        int positionX();
        int positionY();
        void setActive();
        void damage(int damage);
        bool checkIfDead();
};

#endif