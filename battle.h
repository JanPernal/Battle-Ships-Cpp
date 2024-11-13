#ifndef BATTLE_H
#define BATTLE_H
#include "Player.cc"
#include <iostream>

using namespace std;

class Battle : public ShipManager
{
public:
    Battle(int sizeOfBoard);
    bool shoot(char **enemyBoard, char **myBoard, shipData **shipsArray, int **shipsQuantityArray, char **mySelfBoard);
    bool checkHitAndSink(coords shotLocation, char **myBoard, char **enemyBoard, shipData **shipsArray, int **shipsQuantityArray);
    void sunkFiller(shipData data, char **myBoard, char **enemyBoard);
    void shootCombo(char **enemyBoard, char **myBoard, shipData **shipsArray, int **shipsQuantityArray, char **mySelfBoard);
    bool shootingTurns(char **player1SelfBoard, char **player1EnemyBoard, char **player2SelfBoard, char **player2EnemyBoard, shipData **player1ShipsArray, shipData **player2ShipsArray, int **shipsQuantityArray, string firstPlayer, string secondPlayer);
    bool isAnyShipAlive(char **enemyBoard);
};
#endif