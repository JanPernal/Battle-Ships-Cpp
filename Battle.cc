#include "battle.h"

using namespace std;

Battle::Battle(int sizeOfBoard) : ShipManager(sizeOfBoard)
{
}

bool Battle::shoot(char **enemyBoard, char **myBoard, shipData **shipsArray, int **shipsQuantityArray, char **mySelfBoard)
{
    coords shotLocation = getShipLocation(false);
    if (myBoard[shotLocation.rowNumber][shotLocation.columnNumber] == '.' || myBoard[shotLocation.rowNumber][shotLocation.columnNumber] == 'X')
    {
        cout << "Nie mozesz oddac strzalu kolejny raz w to samo miejsce!" << endl;
        return shoot(enemyBoard, myBoard, shipsArray, shipsQuantityArray, mySelfBoard);
    }
    else
    {
        if (enemyBoard[shotLocation.rowNumber][shotLocation.columnNumber] == '#')
        {
            cout << "Trafienie!" << endl;
            enemyBoard[shotLocation.rowNumber][shotLocation.columnNumber] = 'X';
            myBoard[shotLocation.rowNumber][shotLocation.columnNumber] = 'X';

            checkHitAndSink(shotLocation, myBoard, enemyBoard, shipsArray, shipsQuantityArray);
            clearConsole();
            showBoard(myBoard, enemyBoard);
            return true;
        }
        else
        {
            cout << "Pudlo!" << endl;
            enemyBoard[shotLocation.rowNumber][shotLocation.columnNumber] = '.';
            myBoard[shotLocation.rowNumber][shotLocation.columnNumber] = '.';
            clearConsole();
            showBoard(myBoard, enemyBoard);
            return false;
        }
    }
}

bool Battle::checkHitAndSink(coords shotLocation, char **myBoard, char **enemyBoard, shipData **shipsArray, int **shipsQuantityArray)
{
    shipData data = *shipsArray[0];
    int totalAmountOfShips = calculateTotalAmountOfShips(shipsQuantityArray);
    for (int i = 0; i < totalAmountOfShips; i++)
    {
        data = *shipsArray[i];
        int sizeOfShip = data.sizeOfShip;
        bool isHit = false;

        switch (data.shipDirection)
        {
        case 'N':
        case 'n':
            for (int j = 0; j < sizeOfShip; j++)
            {
                if (data.location.rowNumber - j == shotLocation.rowNumber &&
                    data.location.columnNumber == shotLocation.columnNumber)
                {
                    isHit = true;
                    break;
                }
            }
            break;
        case 'E':
        case 'e':
            for (int j = 0; j < sizeOfShip; j++)
            {
                if (data.location.rowNumber == shotLocation.rowNumber &&
                    data.location.columnNumber + j == shotLocation.columnNumber)
                {
                    isHit = true;
                    break;
                }
            }
            break;
        case 'S':
        case 's':
            for (int j = 0; j < sizeOfShip; j++)
            {
                if (data.location.rowNumber + j == shotLocation.rowNumber &&
                    data.location.columnNumber == shotLocation.columnNumber)
                {
                    isHit = true;
                    break;
                }
            }
            break;
        case 'W':
        case 'w':
            for (int j = 0; j < sizeOfShip; j++)
            {
                if (data.location.rowNumber == shotLocation.rowNumber &&
                    data.location.columnNumber - j == shotLocation.columnNumber)
                {
                    isHit = true;
                    break;
                }
            }
            break;
        }

        if (isHit)
        {
            // Statek zostal trafiony, sprawdz czy jest zatopiony
            if (isShipSunk(data.location, enemyBoard, totalAmountOfShips, shipsArray, shipsQuantityArray))
            {
                cout << "Statek " << "zostal zatopiony!" << endl;
                sunkFiller(data, myBoard, enemyBoard);
                return true;
            }
            else
            {
                cout << "Statek " << "zostal trafiony!" << endl;
                return false;
            }
        }
    }

    cout << "Pudlo!" << endl;
    return false;
}

void Battle::sunkFiller(shipData data, char **myBoard, char **enemyBoard)
{
    int startRow = max(0, data.location.rowNumber - 1);
    int endRow = min(sizeOfBoard - 1, data.location.rowNumber + 1);
    int startCol = max(0, data.location.columnNumber - 1);
    int endCol = min(sizeOfBoard - 1, data.location.columnNumber + 1);

    switch (data.shipDirection)
    {
    case 'N':
    case 'n':
        startRow = max(0, data.location.rowNumber - data.sizeOfShip);
        break;
    case 'E':
    case 'e':
        endCol = min(sizeOfBoard - 1, data.location.columnNumber + data.sizeOfShip);
        break;
    case 'S':
    case 's':
        endRow = min(sizeOfBoard - 1, data.location.rowNumber + data.sizeOfShip);
        break;
    case 'W':
    case 'w':
        startCol = max(0, data.location.columnNumber - data.sizeOfShip);
        break;
    }

    for (int r = startRow; r <= endRow; r++)
    {
        for (int c = startCol; c <= endCol; c++)
        {
            if (myBoard[r][c] != 'X')
            {
                myBoard[r][c] = '.';
            }
        }
    }
}

void Battle::shootCombo(char **enemyBoard, char **myBoard, shipData **shipsArray, int **shipsQuantityArray, char **mySelfBoard)
{
    if (shoot(enemyBoard, myBoard, shipsArray, shipsQuantityArray, mySelfBoard))
    {
        clearConsole();
        showBoard(mySelfBoard, myBoard);
        if (isAnyShipAlive(enemyBoard))
        {
            clearConsole();
            cout << "Gratulacje, masz dodatkowa ture!" << endl;
            showBoard(mySelfBoard, myBoard);
            shootCombo(enemyBoard, myBoard, shipsArray, shipsQuantityArray, mySelfBoard);
        }
    }
}

bool Battle::shootingTurns(char **player1SelfBoard, char **player1EnemyBoard, char **player2SelfBoard, char **player2EnemyBoard, shipData **player1ShipsArray, shipData **player2ShipsArray, int **shipsQuantityArray, string firstPlayer, string secondPlayer)
{
    while (isAnyShipAlive(player1SelfBoard) && isAnyShipAlive(player2SelfBoard))
    {
        cout << "strzela: --" << firstPlayer << "--" << endl;
        showBoard(player1SelfBoard, player1EnemyBoard);
        shootCombo(player2SelfBoard, player1EnemyBoard, player2ShipsArray, shipsQuantityArray, player1SelfBoard);

        if (!isAnyShipAlive(player2SelfBoard))
        {
            cout << "Koniec gry. Wygral/a " << firstPlayer << "!" << endl;
            waitForKeyAndClear();
            return true;
        }
        if (!isAnyShipAlive(player1SelfBoard))
        {
            cout << "Koniec gry. Wygral/a " << secondPlayer << "!" << endl;
            waitForKeyAndClear();
            return false;
        }

        pressAnyKeyToSwapPlayers();

        cout << "strzela: --" << secondPlayer << "--" << endl;
        showBoard(player2SelfBoard, player2EnemyBoard);
        shootCombo(player1SelfBoard, player2EnemyBoard, player1ShipsArray, shipsQuantityArray, player2SelfBoard);

        if (!isAnyShipAlive(player2SelfBoard))
        {
            cout << "Koniec gry. Wygral/a " << firstPlayer << "!" << endl;
            waitForKeyAndClear();
            return true;
        }
        if (!isAnyShipAlive(player1SelfBoard))
        {
            cout << "Koniec gry. Wygral/a " << secondPlayer << "!" << endl;
            waitForKeyAndClear();
            return false;
        }
        pressAnyKeyToSwapPlayers();
    }
    return true;
}

bool Battle::isAnyShipAlive(char **enemyBoard)
{
    for (int row = 0; row < sizeOfBoard; row++)
    {
        for (int col = 0; col < sizeOfBoard; col++)
        {
            if (enemyBoard[row][col] == '#')
                return true;
        }
    }
    return false;
}
