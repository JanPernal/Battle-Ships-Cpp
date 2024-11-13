#ifndef BATTLEWITHAI_H
#define BATTLEWITHAI_H
#include "Battle.cc"
#include <iostream>

using namespace std;

class BattleWithAi : public Battle
{
private:
    int **remainingShipsArray;
    int **probabilityBoard;

public:
    int **shipsQuantityArray = calculateAmountOfShips();
    BattleWithAi(int sizeOfBoard);
    coords getPerfectShotLocation(char **aiBoard);

    // todo: metody do obliczenia optymalnego strzału
    bool areOneMastedShipsLeft();
    void resetProbabilityBoard(char **aiBoard);
    void checkProbabilityHorizontally(char **aiBoard);
    void checkProbabilityVertically(char **aiBoard);

    // todo: sprawdzamy czy nie mamy oczywistych strzałów
    coords checkIfThereIsAnyObviousShot(char **aiBoard);
    void increaseProbabilityAroundTheHit(coords shotLocation);
    void decreaseProbabilityDiagonallyFromHit(coords shotLocation);
    void resetProbabilityAroundSunkShip(coords start, int shipSize, char direction);

    // todo: mechanika bitwy
    bool shootAi(char **playerBoard, char **aiBoard, shipData **shipsArray, int **shipsQuantityArray);
    bool checkHitAndSinkAi(coords shotLocation, char **myBoard, char **enemyBoard, int sizeOfBoard, shipData **shipsArray, int **shipsQuantityArray);
    void shootComboAi(char **enemyBoard, char **myBoard, shipData **shipsArray, int **shipsQuantityArray);
    bool shootingTurnsAi(char **player1SelfBoard, char **player1EnemyBoard, char **player2SelfBoard, char **player2EnemyBoard, shipData **player1ShipsArray, shipData **player2ShipsArray, int **shipsQuantityArray, string firstPlayer);
};
#endif