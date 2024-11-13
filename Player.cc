#include "player.h"

Player::Player(int sizeOfBoard) : ShipManager(sizeOfBoard)
{
}

shipData **Player::initializeBoards(int **shipsQuantityArray, char **playerSelfBoard, char **playerEnemyBoard, string playerNickname)
{
    Board gameBoard(sizeOfBoard);
    Ship gameShip(sizeOfBoard);
    ShipManager gameShipManager(sizeOfBoard);

    gameBoard.printPlayerNickname(playerNickname);
    gameBoard.showBoard(playerSelfBoard, playerEnemyBoard);
    shipData **shipsArray = gameShipManager.placeShipsOnBoard(shipsQuantityArray, playerSelfBoard, playerEnemyBoard, playerNickname);
    return shipsArray;
}
shipData **Player::initializeAiBoards(int **shipsQuantityArray, char **aiSelfBoard, char **aiEnemyBoard, string playerNickname)
{
    Board aiBoard(sizeOfBoard);
    Ship aiShip(sizeOfBoard);
    ShipManager aiShipManager(sizeOfBoard);

    aiBoard.printPlayerNickname(playerNickname);
    aiBoard.showSingleBoard(aiSelfBoard);
    shipData **aiShipsArray = aiShipManager.placeRandomShipsOnBoard(shipsQuantityArray, aiSelfBoard, aiEnemyBoard, playerNickname);
    return aiShipsArray;
};
