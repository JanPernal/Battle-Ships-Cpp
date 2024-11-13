#include "shipManager.h"

ShipManager::ShipManager(int sizeOfBoard) : Ship(sizeOfBoard)
{
}

int **ShipManager::calculateAmountOfShips()
{
    float percent = (sizeOfBoard * sizeOfBoard) / 5;
    float firstProportion = 4.0 / 20;
    float secondProportion = 6.0 / 20;
    // todo: tworzymy tablice
    int **ship = new int *[4];

    // todo: rezerwujemy miejsce na wszystkie elementy tablicy
    for (int i = 0; i < 4; i++)
    {
        ship[i] = new int;
    }
    // todo: obliczamy ilosc poszczegolnych statkow
    for (int i = 0; i < 4; i++)
    {
        if (i == 0 || i == 3)
        {
            *(ship[i]) = percent * firstProportion / (i + 1);
        }
        else
        {
            *(ship[i]) = percent * secondProportion / (i + 1);
        }
    }

    return ship;
}

int ShipManager::calculateTotalAmountOfShips(int **shipsQuantityArray)
{
    int opacity = 4;
    int totalAmountOfShips = 0;

    for (int i = 0; i < opacity; i++)
    {
        totalAmountOfShips += *(shipsQuantityArray[i]);
    }
    return totalAmountOfShips;
}

void ShipManager::printShipsQuantity(int opacity, int quantity)
{
    cout << "wypelnij plansze:" << endl;
    cout << quantity << " x " << opacity << "-masztowiec" << endl;
}

char ShipManager::placeShip(int sizeOfShip, char **board, shipData **shipsArray, int shipIndex, bool randomly)
{
    // todo: Get the ship's location and direction from the user
    coords shiplocation = getShipLocation(randomly);
    char direction = 'N';

    if (sizeOfShip != 1)
    {
        direction = getShipDirection(randomly);
    }

    // todo: Check if the ship can be placed on the board
    // todo: Place the ship on the board if it can be placed
    bool isShipCreated = false;
    int row = shiplocation.rowNumber;
    int col = shiplocation.columnNumber;

    if (canPlaceShip(shiplocation, sizeOfShip, direction, board))
    {
        switch (direction)
        {
        case 'N':
        case 'n':
            // todo: Place the ship northwards
            for (int i = 0; i < sizeOfShip; i++)
            {
                board[row - i][col] = '#';
            }
            break;
        case 'E':
        case 'e':
            // todo: Place the ship eastwards
            for (int i = 0; i < sizeOfShip; i++)
            {
                board[row][col + i] = '#';
            }
            break;
        case 'S':
        case 's':
            // todo: Place the ship southwards
            for (int i = 0; i < sizeOfShip; i++)
            {
                board[row + i][col] = '#';
            }
            break;
        case 'W':
        case 'w':
            // todo: Place the ship westwards
            for (int i = 0; i < sizeOfShip; i++)
            {
                board[row][col - i] = '#';
            }
            break;
        }
        isShipCreated = true;

        // todo: Store the ship's data
        shipsArray[shipIndex]->shipDirection = direction;
        shipsArray[shipIndex]->location = shiplocation;
        shipsArray[shipIndex]->sizeOfShip = sizeOfShip;
    }

    return isShipCreated; // todo: Return true if the ship was created successfully
}

shipData **ShipManager::placeShipsOnBoard(int **shipsQuantityArray, char **myBoard, char **enemyBoard, string playerNickName)
{
    bool isShipCreated;
    int opacity = 4;
    int totalAmountOfShips = calculateTotalAmountOfShips(shipsQuantityArray);

    shipData **shipsArray = new shipData *[totalAmountOfShips];
    for (int i = 0; i < totalAmountOfShips; i++)
    {
        shipsArray[i] = new shipData(0, coords(0, 0), 'N');
    }
    int shipIndex = 0;

    for (; opacity > 0; opacity--)
    {
        for (int quantity = *(shipsQuantityArray[opacity - 1]); quantity > 0;)
        {
            printShipsQuantity(opacity, quantity);

            isShipCreated = placeShip(opacity, myBoard, shipsArray, shipIndex, false);
            waitForKeyAndClear();

            printPlayerNickname(playerNickName);
            showBoard(myBoard, enemyBoard);

            if (isShipCreated)
            {
                quantity--;
                shipIndex++;
            }
        }
    }
    return shipsArray;
}

shipData **ShipManager::placeRandomShipsOnBoard(int **shipsQuantityArray, char **myBoard, char **enemyBoard, string playerNickname)
{
    bool isShipCreated;
    int opacity = 4;
    int totalAmountOfShips = calculateTotalAmountOfShips(shipsQuantityArray);

    shipData **shipsArray = new shipData *[totalAmountOfShips];
    for (int i = 0; i < totalAmountOfShips; i++)
    {
        shipsArray[i] = new shipData(0, coords(0, 0), 'N');
    }
    int shipIndex = 0;

    for (; opacity > 0; opacity--)
    {
        for (int quantity = *(shipsQuantityArray[opacity - 1]); quantity > 0;)
        {
            printShipsQuantity(opacity, quantity);

            isShipCreated = placeShip(opacity, myBoard, shipsArray, shipIndex, true);
            clearConsole();

            printPlayerNickname(playerNickname);
            showSingleBoard(myBoard);

            if (isShipCreated)
            {
                quantity--;
                shipIndex++;
            }
        }
    }
    return shipsArray;
}
