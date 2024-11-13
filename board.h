#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <random>

using namespace std;

class Board
{
protected:
    int sizeOfBoard;

public:
    Board(int size);
    // todo: Pobieranie imienia gracza
    string getPlayerName(int numberOfPlayer);

    //todo: walidacja danych
    int intValidation();
    char characterValidation();

    // todo: Tworzenie pustej planszy
    int getRandomRow();
    char getRandomCol();
    char getRandomDirection();
    char **createEmptyBoard();

    // todo: Wyświetlanie elementów planszy
    void printPlayerNickname(string playerNickname);
    void printAlphabeth();
    void printSheet(bool integer);
    void printFullBlock(char **board, int i, int j);
    void printData(int i, char **board);
    void printData(int i, int **board);

    // todo: Wyświetlanie planszy
    void showBoard(char **myBoard, char **enemyBoard);
    void showSingleBoard(char **playerEnemyBoard);
    void showSingleBoard(int **board);

    // todo: Czyszczenie terminala
    void clearConsole();
    void waitForKeyAndClear();
    void pressAnyKeyToSwapPlayers();
};

#endif