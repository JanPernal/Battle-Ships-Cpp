#include <iostream>
#include <windows.h>
#include "Game.cc"

using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    Game newGame;
    newGame.runGame();
}
