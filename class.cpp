#include <iostream>
#include <conio.h>
#include "header.h"

void greet()
{

    std::cout << "Press any key to continue..." << std::endl;
    _getch();

    std::cout << "                                o" << std::endl;
    std::cout << "                           .-\"'|" << std::endl;
    std::cout << "                           |-\"'|" << std::endl;
    std::cout << "                                |   _.-'`." << std::endl;
    std::cout << "                               _|\"-\"_.-'|.`." << std::endl;
    std::cout << "                              |:^.-'_.-'`.;.`." << std::endl;
    std::cout << "                              | `.'.   ,-'_.-'|" << std::endl;
    std::cout << "                              |   + '-'.-'   J" << std::endl;
    std::cout << "           __.            .d88|    `.-'      |" << std::endl;
    std::cout << "      _.--'_..`.    .d88888888|     |       J'b." << std::endl;
    std::cout << "   +:\" ,--'_.|`.`.d88888888888|-.   |    _-.|888b." << std::endl;
    std::cout << "   | \\ \\-'_.--'_.-+888888888+'  _>F F +:'   `88888bo." << std::endl;
    std::cout << "    L \\ +'_.--'   |88888+\"'  _.' J J J  `.    +8888888b." << std::endl;
    std::cout << "    |  `+'        |8+\"'  _.-'    | | |    +    `+8888888._-'." << std::endl;
    std::cout << "  .d8L  L         J  _.-'        | | |     `.    `+888+^'.-|.`." << std::endl;
    std::cout << " d888|  |         J-'            F F F       `.  _.-\"_.-'_.+.`.`." << std::endl;
    std::cout << "d88888L  L     _.  L            J J J          `|. +'_.-'    `_+ `;" << std::endl;
    std::cout << "888888J  |  +-'  \\ L         _.-+.|.+.          F `.`.     .-'_.-\"J" << std::endl;
    std::cout << "8888888|  L L\\    \\|     _.-'     '   `.       J    `.`.,-'.-\"    |" << std::endl;
    std::cout << "8888888PL | | \\    `._.-'               `.     |      `..-\"      J.b" << std::endl;
    std::cout << "8888888 |  L L `.    \\     _.-+.          `.   L+`.     |        F88b" << std::endl;
    std::cout << "8888888  L | |   \\   _..--'_.-|.`.          >-'    `., J        |8888b" << std::endl;
    std::cout << "8888888  |  L L   +:\" _.--'_.-'.`.`.    _.-'     .-' | |       JY88888b" << std::endl;
    std::cout << "8888888   L | |   J \\ \\_.-'     `.`.`.-'     _.-'   J J        F Y88888b" << std::endl;
    std::cout << "Y888888    \\ L L   L \\ `.      _.-'_.-+  _.-'       | |       |   Y88888b" << std::endl;
    std::cout << "`888888b    \\| |   |  `. \\ _.-'_.-'   |-'          J J       J     Y88888b" << std::endl;
    std::cout << " Y888888     +'\\   J    \\ '_.-'       F    ,-T\"\\   | |    .-'      )888888" << std::endl;
    std::cout << "  Y88888b.      \\   L    +'          J    /  | J  J J  .-'        .d888888" << std::endl;
    std::cout << "   Y888888b      \\  |    |           |    F  '.|.-'+|-'         .d88888888" << std::endl;
    std::cout << "    Y888888b      \\ J    |           F   J    -.              .od88888888P" << std::endl;
    std::cout << "     Y888888b      \\ L   |          J    | .' ` \\d8888888888888888888888P" << std::endl;
    std::cout << "      Y888888b      \\|   |          |  .-'`.  `\\ `.88888888888888888888P" << std::endl;
    std::cout << "       Y888888b.     J   |          F-'     \\\\ ` \\ \\88888888888888888P'" << std::endl;
    std::cout << "        Y8888888b     L  |         J       d8`. ` \\`.8888888888888P'" << std::endl;
    std::cout << "         Y8888888b    |  |        .+      d8888\\  ` .'  `Y888888P'" << std::endl;
    std::cout << "         `88888888b   J  |     .-'     .od888888\\.-'" << std::endl;
    std::cout << "          Y88888888b   \\ |  .-'     d888888888P'" << std::endl;
    std::cout << "           `Y88888888b    \\|-'       d888888888P" << std::endl;
    std::cout << "             `Y88888888bo.      .od88888888   hs" << std::endl;
    std::cout << "             `8888888888888888888888888888" << std::endl;
    std::cout << "              Y88888888888888888888888888P" << std::endl;
    std::cout << "               `Y8888888888888888888888P'" << std::endl;
    std::cout << "                 `Y8888888888888P'" << std::endl;
    std::cout << "                      `Y88888P'" << std::endl;

    std::cout << "Press any key to continue..." << std::endl;
    _getch();
    system("cls");
}

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
