#include "header.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

void setTerminalWindowSize(int columns, int rows) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole != INVALID_HANDLE_VALUE) {
        SMALL_RECT rect = {0, 0, static_cast<SHORT>(columns - 1), static_cast<SHORT>(rows - 1)};
        COORD size = {static_cast<SHORT>(columns), static_cast<SHORT>(rows)};
        SetConsoleWindowInfo(hConsole, TRUE, &rect);
        SetConsoleScreenBufferSize(hConsole, size);
    }
}

void greet(){
std::cout<<"Press any key to continue..."<<std::endl;
_getch();        

std::cout << "                                o" << std::endl;
std::cout << "                            .-\"'|" << std::endl;
std::cout << "                            |-\"'|" << std::endl;
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
std::cout << "    |  `+'        |8+\"'  _.-'    | | |    +    `+8888888._-'."<< std::endl;
std::cout << "  .d8L  L         J  _.-'        | | |     `.    `+888+^'.-|.`." << std::endl;
std::cout << " d888|  |         J-'            F F F       `.  _.-\"_.-'_.+.`.`."<< std::endl;
std::cout << "d88888L  L     _.  L            J J J          `|. +'_.-'    `_+ `;"<< std::endl;
std::cout << "888888J  |  +-'  \\ L         _.-+.|.+.          F `.`.     .-'_.-\"J"<< std::endl;
std::cout << "8888888|  L L\\    \\|     _.-'     '   `.       J    `.`.,-'.-\"    |"<< std::endl;
std::cout << "8888888PL | | \\    `._.-'               `.     |      `..-\"      J.b"<< std::endl;
std::cout << "8888888 |  L L `.    \\     _.-+.          `.   L+`.     |        F88b"<< std::endl;
std::cout << "8888888  L | |   \\   _..--'_.-|.`.          >-'    `., J        |8888b"<< std::endl;
std::cout << "8888888  |  L L   +:\" _.--'_.-'.`.`.    _.-'     .-' | |       JY88888b"<< std::endl;
std::cout << "8888888   L | |   J \\ \\_.-'     `.`.`.-'     _.-'   J J        F Y88888b"<< std::endl;
std::cout << "Y888888    \\ L L   L \\ `.      _.-'_.-+  _.-'       | |       |   Y88888b"<< std::endl;
std::cout << "`888888b    \\| |   |  `. \\ _.-'_.-'   |-'          J J       J     Y88888b"<< std::endl;
std::cout << " Y888888     +'\\   J    \\ '_.-'       F    ,-T\"\\   | |    .-'      )888888"<< std::endl;
std::cout << "  Y88888b.      \\   L    +'          J    /  | J  J J  .-'        .d888888"<< std::endl;
std::cout << "   Y888888b      \\  |    |           |    F  '.|.-'+|-'         .d88888888"<< std::endl;
std::cout << "    Y888888b      \\ J    |           F   J    -.              .od88888888P"<< std::endl;
std::cout << "     Y888888b      \\ L   |          J    | .' ` \\d8888888888888888888888P"<< std::endl;
std::cout << "      Y888888b      \\|   |          |  .-'`.  `\\ `.88888888888888888888P"<< std::endl;
std::cout << "       Y888888b.     J   |          F-'     \\\\ ` \\ \\88888888888888888P'"<< std::endl;
std::cout << "        Y8888888b     L  |         J       d8`. ` \\`.8888888888888P'"<< std::endl;
std::cout << "         Y8888888b    |  |        .+      d8888\\  ` .'  `Y888888P'"<< std::endl;
std::cout << "         `88888888b   J  |     .-'     .od888888\\.-'" << std::endl;
std::cout << "          Y88888888b   \\ |  .-'     d888888888P'" << std::endl;
std::cout << "           `Y88888888b    \\|-'       d888888888P" << std::endl;
std::cout << "             `Y88888888bo.      .od88888888   hs" << std::endl;
std::cout << "             `8888888888888888888888888888" << std::endl;
std::cout << "              Y88888888888888888888888888P" << std::endl;
std::cout << "               `Y8888888888888888888888P'" << std::endl;
std::cout << "                 `Y8888888888888P'" << std::endl;
std::cout << "                      `Y88888P'" << std::endl;

std::cout<<"Press any key to continue..."<<std::endl;
_getch();              
system("cls");
}

int main(){


greet();


        return 0;
}