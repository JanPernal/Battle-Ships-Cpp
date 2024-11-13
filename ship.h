#ifndef SHIP_H
#define SHIP_H

#include "Board.cc"

struct coords
{
    int columnNumber;
    int rowNumber;
    coords(int columnNumber, int rowNumber) : columnNumber(columnNumber), rowNumber(rowNumber) {}
};

struct shipData
{
    int sizeOfShip;
    coords location;
    char shipDirection;
    shipData(int sizeOfShip, coords location, char shipDirection) : 
    sizeOfShip(sizeOfShip), location(location), 
    shipDirection(shipDirection) {}
};

class Ship : public Board
{
public:
    // todo: constructor
    Ship(int sizeOfBoard);

    // todo: Get ship data methods:
    char getColumn();
    int getRow();
    char getShipDirection(bool randomly);
    coords getShipLocation(bool randomly);

    // todo: Ship placement validation:
    bool isShipInsideBoard(coords shiplocation, int sizeOfShip, 
    char direction);
    bool isShipOnOtherShip(coords shiplocation, int sizeOfShip, 
    char direction, char **board);
    bool isSpacesAroundShip(coords shiplocation, int sizeOfShip, 
    char direction, char **board);
    bool canPlaceShip(coords shiplocation, int sizeOfShip, 
    char direction, char **board);

    // todo: Ship placement and game logic:
    bool isShipSunk(coords shipLocation, char **enemyBoard, int totalAmountOfShips, shipData **shipsArray, int **shipsQuantityArray);
};

#endif