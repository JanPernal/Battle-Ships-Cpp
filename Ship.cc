#include "ship.h"
#include <iostream>

using namespace std;

// todo: Constructor for the Ship class
Ship::Ship(int sizeOfBoard) : Board(sizeOfBoard)
{
}

// todo: Function to get the column input from the user
char Ship::getColumn()
{
    char column;
    char letter = 'A' + sizeOfBoard - 1;
    cout << "Podaj kolumne: [" << 'A' << " - " << letter << "]:" << endl;
    column = characterValidation();
    if ((column >= 'A' && column <= 'A' + sizeOfBoard - 1) || (column >= 'a' && column <= 'a' + sizeOfBoard - 1))
    {
        return column;
    }
    else
    {
        cout << "Niepoprawny numer kolumny!" << endl;
        return getColumn(); // todo: Recursive call if input is invalid
    }
}

// todo: Function to get the row input from the user
int Ship::getRow()
{
    int row;
    cout << "Podaj rzad [" << 1 << " - " << sizeOfBoard << "]:" << endl;
    row = intValidation();
    if (row >= 1 && row <= sizeOfBoard)
    {
        return row;
    }
    else
    {
        cout << "Niepoprawny numer rzedu" << endl;
        return getRow(); // todo: Recursive call if input is invalid
    }
}

// todo: Function to get the direction input from the user
char Ship::getShipDirection(bool randomly)
{
    char direction;
    if (randomly)
    {
        direction = getRandomDirection();
    }
    else
    {
        cout << "Podaj kierunek, w ktory statek jest zwrocony (N, E, S, W):" << endl;
        direction = characterValidation();
    }

    if (direction == 'N' || direction == 'E' || direction == 'S' || direction == 'W' ||
        direction == 'n' || direction == 'e' || direction == 's' || direction == 'w')
    {
        return direction;
    }
    else
    {
        cout << "Niepoprawny kierunek!" << endl;
        return getShipDirection(randomly); // todo: Recursive call if input is invalid
    }
}

// todo: Function to get the ship's location (coordinates)
coords Ship::getShipLocation(bool randomly)
{
    char column;
    int row;
    if (randomly)
    {
        column = getRandomCol();
        row = getRandomRow();
    }
    else
    {
        column = getColumn();
        row = getRow();
    }

    if ((column >= 'A' && column <= 'Z') && (row >= 1 && row <= sizeOfBoard))
    {
        // todo: Convert column letter to index (A = 0, B = 1, etc.)
        return coords(column - 'A', row - 1);
    }
    else if ((column >= 'a' && column <= 'z') && (row >= 1 && row <= sizeOfBoard))
    {
        // todo: Convert column letter to index (a = 0, b = 1, etc.)
        return coords(column - 'a', row - 1);
    }
    else
    {
        return getShipLocation(randomly); // todo: Recursive call if input is invalid
    }
}

// todo: Function to check if the ship is within the board boundaries
bool Ship::isShipInsideBoard(coords shiplocation, int sizeOfShip, char direction)
{
    switch (direction)
    {
    case 'N':
    case 'n':
        // todo: Check if the ship is within the boundaries when placed northwards
        if (shiplocation.rowNumber >= sizeOfShip - 1)
        {
            return true;
        }
        break;
    case 'E':
    case 'e':
        // todo: Check if the ship is within the boundaries when placed eastwards
        if (shiplocation.columnNumber <= sizeOfBoard - sizeOfShip)
        {
            return true;
        }
        break;
    case 'S':
    case 's':
        // todo: Check if the ship is within the boundaries when placed southwards
        if (shiplocation.rowNumber <= sizeOfBoard - sizeOfShip)
        {
            return true;
        }
        break;
    case 'W':
    case 'w':
        // todo: Check if the ship is within the boundaries when placed westwards
        if (shiplocation.columnNumber >= sizeOfShip - 1)
        {
            return true;
        }
        break;
    }
    return false; // todo: Return false if the ship is not within the boundaries
}

// todo: Function to check if the ship is not overlapping with any other ship
bool Ship::isShipOnOtherShip(coords shiplocation, int sizeOfShip, char direction, char **board)
{
    switch (direction)
    {
    case 'N':
    case 'n':
        // todo: Check if the ship overlaps with any other ship when placed northwards
        for (int i = 0; i < sizeOfShip; i++)
        {
            if (board[shiplocation.rowNumber - i][shiplocation.columnNumber] != ' ')
            {
                return false;
            }
        }
        break;
    case 'E':
    case 'e':
        // todo: Check if the ship overlaps with any other ship when placed eastwards
        for (int i = 0; i < sizeOfShip; i++)
        {
            if (board[shiplocation.rowNumber][shiplocation.columnNumber + i] != ' ')
            {
                return false;
            }
        }
        break;
    case 'S':
    case 's':
        // todo: Check if the ship overlaps with any other ship when placed southwards
        for (int i = 0; i < sizeOfShip; i++)
        {
            if (board[shiplocation.rowNumber + i][shiplocation.columnNumber] != ' ')
            {
                return false;
            }
        }
        break;
    case 'W':
    case 'w':
        // todo: Check if the ship overlaps with any other ship when placed westwards
        for (int i = 0; i < sizeOfShip; i++)
        {
            if (board[shiplocation.rowNumber][shiplocation.columnNumber - i] != ' ')
            {
                return false;
            }
        }
        break;
    }
    return true; // todo: Return true if the ship is not overlapping with any other ship
}

// todo: Function to check if the ship has enough space around it to be placed
bool Ship::isSpacesAroundShip(coords shiplocation, int sizeOfShip, char direction, char **board)
{
    // Ustawienie domyślnych granic wokół statku (obszar 1 pola na około)
    int startRow = max(0, shiplocation.rowNumber - 1);
    int endRow = min(sizeOfBoard - 1, shiplocation.rowNumber + 1);
    int startCol = max(0, shiplocation.columnNumber - 1);
    int endCol = min(sizeOfBoard - 1, shiplocation.columnNumber + 1);

    switch (direction)
    {
    case 'N':
    case 'n':
        startRow = max(0, shiplocation.rowNumber - sizeOfShip);
        break;
    case 'E':
    case 'e':
        endCol = min(sizeOfBoard - 1, shiplocation.columnNumber + sizeOfShip);
        break;
    case 'S':
    case 's':
        endRow = min(sizeOfBoard - 1, shiplocation.rowNumber + sizeOfShip);
        break;
    case 'W':
    case 'w':
        startCol = max(0, shiplocation.columnNumber - sizeOfShip);
        break;
    }

    for (int row = startRow; row <= endRow; row++)
    {
        for (int col = startCol; col <= endCol; col++)
        {
            // Check if the current position is part of the ship being placed
            bool isPartOfShip = false;
            switch (direction)
            {
            case 'N':
            case 'n':
                isPartOfShip = (col == shiplocation.columnNumber && row >= shiplocation.rowNumber - sizeOfShip + 1 && row <= shiplocation.rowNumber);
                break;
            case 'E':
            case 'e':
                isPartOfShip = (row == shiplocation.rowNumber && col >= shiplocation.columnNumber && col < shiplocation.columnNumber + sizeOfShip);
                break;
            case 'S':
            case 's':
                isPartOfShip = (col == shiplocation.columnNumber && row >= shiplocation.rowNumber && row < shiplocation.rowNumber + sizeOfShip);
                break;
            case 'W':
            case 'w':
                isPartOfShip = (row == shiplocation.rowNumber && col >= shiplocation.columnNumber - sizeOfShip + 1 && col <= shiplocation.columnNumber);
                break;
            }

            // If it's not part of the ship being placed and there's already a ship there, return false
            if (!isPartOfShip && board[row][col] != ' ')
            {
                return false;
            }
        }
    }

    return true; // Zwróć true, jeśli wokół statku jest wystarczająca przestrzeń
}

// todo: Function to check if the ship can be placed on the board
bool Ship::canPlaceShip(coords shiplocation, int sizeOfShip, char direction, char **board)
{
    bool canPlaceShip = isShipInsideBoard(shiplocation, sizeOfShip, direction);
    if (canPlaceShip)
    {
        canPlaceShip = isShipOnOtherShip(shiplocation, sizeOfShip, direction, board);
        if (canPlaceShip)
        {
            canPlaceShip = isSpacesAroundShip(shiplocation, sizeOfShip, direction, board);
        }
    }
    return canPlaceShip;
}

// todo: Function to check if the ship is sunk
bool Ship::isShipSunk(coords shipLocation, char **enemyBoard, int totalAmountOfShips, shipData **shipsArray, int **shipsQuantityArray)
{
    for (int i = 0; i < totalAmountOfShips; i++)
    {
        shipData &data = *shipsArray[i];
        if (data.location.rowNumber == shipLocation.rowNumber &&
            data.location.columnNumber == shipLocation.columnNumber)
        {
            int sizeOfShip = data.sizeOfShip;
            switch (data.shipDirection)
            {
            case 'N':
            case 'n':
                // todo: Check if the ship is sunk when placed northwards
                for (int j = 0; j < sizeOfShip; j++)
                {
                    if (enemyBoard[data.location.rowNumber - j][data.location.columnNumber] == '#')
                    {
                        return false;
                    }
                }
                break;
            case 'E':
            case 'e':
                // todo: Check if the ship is sunk when placed eastwards
                for (int j = 0; j < sizeOfShip; j++)
                {
                    if (enemyBoard[data.location.rowNumber][data.location.columnNumber + j] == '#')
                    {
                        return false;
                    }
                }
                break;
            case 'S':
            case 's':
                // todo: Check if the ship is sunk when placed southwards
                for (int j = 0; j < sizeOfShip; j++)
                {
                    if (enemyBoard[data.location.rowNumber + j][data.location.columnNumber] == '#')
                    {
                        return false;
                    }
                }
                break;
            case 'W':
            case 'w':
                // todo: Check if the ship is sunk when placed westwards
                for (int j = 0; j < sizeOfShip; j++)
                {
                    if (enemyBoard[data.location.rowNumber][data.location.columnNumber - j] == '#')
                    {
                        return false;
                    }
                }
                break;
            }
            return true; // todo: Return true if the ship is sunk
        }
    }
    return false; // todo: Return false if the ship is not sunk
}