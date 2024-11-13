#ifndef SHIPMANAGER_H
#define SHIPMANAGER_H

#include "Ship.cc"

class ShipManager : public Ship
{
public:
    // todo: Constructor
    ShipManager(int sizeOfBoard);

    // todo: Calculating number of Ships depending on size of board.
    int **calculateAmountOfShips();
    int calculateTotalAmountOfShips(int **shipsQuantityArray);

    // todo: Placing ships on board.
    void printShipsQuantity(int opacity, int quantity);
    char placeShip(int sizeOfShip, char **board, shipData **shipsArray, int shipIndex, bool randomly);
    shipData **placeShipsOnBoard(int **shipsQuantityArray,char **myBoard, char **enemyBoard, string playerNickName);
    shipData **placeRandomShipsOnBoard(int **shipsQuantityArray, char **myBoard, char **enemyBoard, string playerNickname);
};

#endif