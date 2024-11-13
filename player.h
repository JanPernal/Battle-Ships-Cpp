#ifndef PLAYER_H
#define PLAYER_H
#include "ShipManager.cc"
#include <iostream>

using namespace std;

class Player : public ShipManager
{
public:
    Player(int sizeOfBoard);
    shipData **initializeBoards(int **shipsQuantityArray, char **firstPlayerSelfBoard, char **firstPlayerEnemyBoard, string playerNickname);
    shipData **initializeAiBoards(int **shipsQuantityArray, char **aiSelfBoard, char **aiEnemyBoard, string playerNickname);
};
#endif