#ifndef GAME_H
#define GAME_H
#include "BattleWithAi.cc"
#include <iostream>

using namespace std;

class Game
{
public:
    Game();
    int validation();
    bool booleanValidation();
    int getSizeOfBoard();
    void displayInstructions();
    void printResult(string player1, string player2, int pl1, int pl2);
    bool isPlayAgainActive();

    void runGame();
};
#endif