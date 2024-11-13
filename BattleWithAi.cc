#include "battleWithAi.h"
using namespace std;

BattleWithAi::BattleWithAi(int sizeOfBoard) : Battle(sizeOfBoard)
{
    remainingShipsArray = calculateAmountOfShips();

    probabilityBoard = new int *[sizeOfBoard];
    for (int i = 0; i < sizeOfBoard; i++)
    {
        probabilityBoard[i] = new int[sizeOfBoard];
    }
    for (int i = 0; i < sizeOfBoard; ++i)
    {
        for (int j = 0; j < sizeOfBoard; ++j)
        {
            probabilityBoard[i][j] = 1;
        }
    }
}

coords BattleWithAi::getPerfectShotLocation(char **aiBoard)
{
    coords check = checkIfThereIsAnyObviousShot(aiBoard);
    if (check.columnNumber != -1 && check.rowNumber != -1)
    {
        return check;
    }
    resetProbabilityBoard(aiBoard);
    showSingleBoard(probabilityBoard);

    checkProbabilityHorizontally(aiBoard);
    checkProbabilityVertically(aiBoard);
    showSingleBoard(probabilityBoard);

    coords maximum = {0, 0};
    int maxVal = -1;          // Start with a value lower than any possible probability
    int maxX = -1, maxY = -1; // Initialize to invalid coordinates

    for (int i = 0; i < sizeOfBoard; i++)
    {
        for (int j = 0; j < sizeOfBoard; j++)
        {
            if (aiBoard[i][j] == ' ' && probabilityBoard[i][j] > maxVal)
            {
                maxVal = probabilityBoard[i][j];
                maxX = i;
                maxY = j;
                maximum.rowNumber = i;
                maximum.columnNumber = j;
            }
        }
    }

    if (maxX != -1 && maxY != -1)
    {
        cout << "AI chce strzelić w współżędne: " << char(maximum.columnNumber + 'A') << maximum.rowNumber + 1 << endl;
        probabilityBoard[maximum.rowNumber][maximum.columnNumber] = 0;
        return maximum;
    }

    // If no valid location is found, return an invalid coordinate to handle it outside

    return {-1, -1};
}

bool BattleWithAi::areOneMastedShipsLeft()
{
    bool areOneMastedShipsLeft = false;
    if (*remainingShipsArray[0] <= 0)
    {
        return false;
    }
    if (*remainingShipsArray[1] <= 0 && *remainingShipsArray[2] <= 0 && *remainingShipsArray[3] <= 0)
    {
        return true;
    }
    return false;
}

void BattleWithAi::resetProbabilityBoard(char **aiBoard)
{
    for (int row = 0; row < sizeOfBoard; row++)
    {
        for (int col = 0; col < sizeOfBoard; col++)
        {
            if (probabilityBoard[row][col] != 100 && probabilityBoard[row][col] != 0)
            {
                probabilityBoard[row][col] = 1;
            }
        }
    }
}

void BattleWithAi::checkProbabilityHorizontally(char **aiBoard)
{
    // Sprawdzenie poziome
    for (int opacity = 4; opacity > 1; opacity--)
    {
        for (int quantity = 0; quantity < *remainingShipsArray[opacity - 1]; quantity++)
        {
            for (int row = 0; row < sizeOfBoard; row++)
            {
                for (int col = 0; col < sizeOfBoard - (opacity - 1); col++)
                {
                    bool isFree = true;
                    for (int x = 0; x < opacity; x++)
                    {
                        if (aiBoard[row][col + x] != ' ')
                        {
                            isFree = false;
                            break;
                        }
                    }
                    if (isFree) // Dopiero teraz zwiększamy prawdopodobieństwo
                    {
                        for (int x = 0; x < opacity; x++)
                        {
                            probabilityBoard[row][col + x]++;
                        }
                    }
                }
            }
        }
    }
}

void BattleWithAi::checkProbabilityVertically(char **aiBoard)
{
    for (int opacity = 4; opacity > 1; opacity--)
    {
        for (int quantity = 0; quantity < *remainingShipsArray[opacity - 1]; quantity++)
        {
            for (int row = 0; row < sizeOfBoard - (opacity - 1); row++)
            {
                for (int col = 0; col < sizeOfBoard; col++)
                {
                    bool isFree = true;
                    for (int y = 0; y < opacity; y++)
                    {
                        if (aiBoard[row + y][col] != ' ')
                        {
                            isFree = false;
                            break;
                        }
                    }
                    if (isFree) // Dopiero teraz zwiększamy prawdopodobieństwo
                    {
                        for (int y = 0; y < opacity; y++)
                        {
                            probabilityBoard[row + y][col]++;
                        }
                    }
                }
            }
        }
    }
}

coords BattleWithAi::checkIfThereIsAnyObviousShot(char **aiBoard)
{
    for (int row = 0; row < sizeOfBoard; row++)
    {
        for (int col = 0; col < sizeOfBoard; col++)
        {
            if (aiBoard[row][col] == ' ')
            {
                if (probabilityBoard[row][col] == 100)
                {
                    coords location = {col, row};
                    probabilityBoard[row][col] = 0;
                    return location;
                }
            }
            else
            {
                probabilityBoard[row][col] = 0;
            }
        }
    }
    return {-1, -1};
}

void BattleWithAi::increaseProbabilityAroundTheHit(coords shotLocation)
{
    if (shotLocation.rowNumber > 0)
        probabilityBoard[shotLocation.rowNumber - 1][shotLocation.columnNumber] = 100;
    if (shotLocation.columnNumber < sizeOfBoard - 1)
        probabilityBoard[shotLocation.rowNumber][shotLocation.columnNumber + 1] = 100;
    if (shotLocation.rowNumber < sizeOfBoard - 1)
        probabilityBoard[shotLocation.rowNumber + 1][shotLocation.columnNumber] = 100;
    if (shotLocation.columnNumber > 0)
        probabilityBoard[shotLocation.rowNumber][shotLocation.columnNumber - 1] = 100;
}

void BattleWithAi::decreaseProbabilityDiagonallyFromHit(coords shotLocation)
{
    if (shotLocation.rowNumber > 0 && shotLocation.columnNumber > 0)
        probabilityBoard[shotLocation.rowNumber - 1][shotLocation.columnNumber - 1] = 0;
    if (shotLocation.rowNumber > 0 && shotLocation.columnNumber < sizeOfBoard - 1)
        probabilityBoard[shotLocation.rowNumber - 1][shotLocation.columnNumber + 1] = 0;
    if (shotLocation.rowNumber < sizeOfBoard - 1 && shotLocation.columnNumber > 0)
        probabilityBoard[shotLocation.rowNumber + 1][shotLocation.columnNumber - 1] = 0;
    if (shotLocation.rowNumber < sizeOfBoard - 1 && shotLocation.columnNumber < sizeOfBoard - 1)
        probabilityBoard[shotLocation.rowNumber + 1][shotLocation.columnNumber + 1] = 0;
}

bool BattleWithAi::shootAi(char **playerBoard, char **aiBoard, shipData **shipsArray, int **shipsQuantityArray)
{
    coords shotLocation = {0, 0};
    if (areOneMastedShipsLeft())
    {
        shotLocation.columnNumber = getRandomRow();
        shotLocation.rowNumber = getRandomRow();
    }
    else
    {
        coords shotLocation = getPerfectShotLocation(aiBoard);
    }

    // coords shotLocation = getPerfectShotLocation(aiBoard);
    //  Sprawdź, czy otrzymano prawidłowe koordynaty
    if (shotLocation.rowNumber == -1 || shotLocation.columnNumber == -1)
    {
        cout << "Nie można znaleźć prawidłowego miejsca do strzału. Wybieranie losowego miejsca." << endl;
        do
        {
            shotLocation.rowNumber = getRandomRow();
            shotLocation.columnNumber = getRandomRow();
        } while (aiBoard[shotLocation.rowNumber][shotLocation.columnNumber] != ' ');
    }

    cout << "Wybrane koordynaty strzalu: (" << shotLocation.rowNumber << ", " << shotLocation.columnNumber << ")" << endl;

    // Debug: Display the selected shot location
    cout << "Wybrane koordynaty strzalu: (" << shotLocation.rowNumber << ", " << shotLocation.columnNumber << ")" << endl;
    // Check if the location has already been targeted
    if (aiBoard[shotLocation.rowNumber][shotLocation.columnNumber] == '.' || aiBoard[shotLocation.rowNumber][shotLocation.columnNumber] == 'X')
    {
        // Debug: Display message if the location was already targeted
        cout << "Koordynaty (" << shotLocation.rowNumber << ", " << shotLocation.columnNumber << ") byly juz celem." << endl;
        // Mark the probability as zero to avoid selecting it again
        probabilityBoard[shotLocation.rowNumber][shotLocation.columnNumber] = 0;

        // Instead of recursion, find a new target location
        return false; // Indicate a miss or invalid shot
    }

    // Proceed with the shooting logic
    if (playerBoard[shotLocation.rowNumber][shotLocation.columnNumber] == '#')
    {
        cout << "Ai wykonalo strzal w koordynaty: " << char(shotLocation.columnNumber + 'A') << shotLocation.rowNumber + 1 << " i trafilo w"
             << playerBoard[shotLocation.rowNumber][shotLocation.columnNumber] << endl;

        playerBoard[shotLocation.rowNumber][shotLocation.columnNumber] = 'X';
        aiBoard[shotLocation.rowNumber][shotLocation.columnNumber] = 'X';

        // Debug: Display updated boards
        cout << "Zaktualizowane tablice po trafieniu:" << endl;
        showSingleBoard(playerBoard);
        showSingleBoard(aiBoard);
        // Increase probability around the hit
        increaseProbabilityAroundTheHit(shotLocation);
        // Decrease probability diagonally from the hit
        decreaseProbabilityDiagonallyFromHit(shotLocation);
        // Debug: Display probability board after updating
        cout << "Tablica prawdopodobieństwa po aktualizacji:" << endl;
        showSingleBoard(probabilityBoard);
        bool isSunk = checkHitAndSinkAi(shotLocation, aiBoard, playerBoard, sizeOfBoard, shipsArray, shipsQuantityArray);
        if (isSunk)
        {
            cout << "Statek został zatopiony!" << endl;
            resetProbabilityBoard(aiBoard);
            checkProbabilityHorizontally(aiBoard);
            checkProbabilityVertically(aiBoard);
            cout << "Zaktualizowana tablica prawdopodobieństwa po zatopieniu:" << endl;
            showSingleBoard(probabilityBoard);
        }
        return true;
    }
    else
    {
        cout << "Pudlo!" << endl;
        playerBoard[shotLocation.rowNumber][shotLocation.columnNumber] = '.';
        aiBoard[shotLocation.rowNumber][shotLocation.columnNumber] = '.';

        // Debug: Display updated boards after a miss
        cout << "Zaktualizowane tablice po pudle:" << endl;
        showSingleBoard(playerBoard);
        showSingleBoard(aiBoard);
        return false;
    }
}

bool BattleWithAi::checkHitAndSinkAi(coords shotLocation, char **aiBoard, char **playerBoard, int sizeOfBoard, shipData **shipsArray, int **shipsQuantityArray)
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
            if (isShipSunk(data.location, playerBoard, totalAmountOfShips, shipsArray, shipsQuantityArray))
            {
                cout << "Statek zostal zatopiony!" << endl;

                // Resetuj prawdopodobieństwo wokół zatopionego statku
                resetProbabilityAroundSunkShip(data.location, data.sizeOfShip, data.shipDirection);

                sunkFiller(data, aiBoard, playerBoard);
                *remainingShipsArray[sizeOfShip - 1] -= 1;

                // Aktualizuj tablicę prawdopodobieństwa
                resetProbabilityBoard(aiBoard);
                checkProbabilityHorizontally(aiBoard);
                checkProbabilityVertically(aiBoard);

                cout << "Zaktualizowana tablica prawdopodobienstwa po zatopieniu statku:" << endl;
                showSingleBoard(probabilityBoard);

                return true;
            }
            else
            {
                cout << "Statek zostal trafiony!" << endl;
                return false;
            }
        }
    }

    // Jeśli dotarliśmy tutaj, oznacza to, że nie znaleziono trafionego statku
    cout << "Nie znaleziono trafionego statku. To nie powinno się zdarzyć." << endl;
    return false;
}

void BattleWithAi::shootComboAi(char **playerBoard, char **aiBoard, shipData **shipsArray, int **shipsQuantityArray)
{
    int maxAttempts = 10; // Maksymalna liczba prób, aby uniknąć nieskończonej pętli
    int attempts = 0;

    while (attempts < maxAttempts)
    {
        if (shootAi(playerBoard, aiBoard, shipsArray, shipsQuantityArray))
        {
            if (isAnyShipAlive(playerBoard))
            {
                cout << "AI ma dodatkowa ture w zamian za trafienie!" << endl;
                attempts++;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    if (attempts == maxAttempts)
    {
        cout << "Osiągnięto maksymalną liczbę prób. Kończenie tury AI." << endl;
    }
}

bool BattleWithAi::shootingTurnsAi(char **player1SelfBoard, char **player1EnemyBoard, char **aiSelfBoard, char **aiEnemyBoard, shipData **player1ShipsArray, shipData **player2ShipsArray, int **shipsQuantityArray, string firstPlayer)
{
    while (isAnyShipAlive(player1SelfBoard) && isAnyShipAlive(aiSelfBoard))
    {

        cout << "strzela: --" << firstPlayer << "--" << endl;
        showBoard(player1SelfBoard, player1EnemyBoard);

        shootCombo(aiSelfBoard, player1EnemyBoard, player2ShipsArray, shipsQuantityArray, player1SelfBoard);
        if (!isAnyShipAlive(aiSelfBoard))
        {
            cout << "Koniec gry. Wygral/a " << firstPlayer << "!" << endl;
            waitForKeyAndClear();
            return true;
        }
        if (!isAnyShipAlive(player1SelfBoard))
        {
            cout << "Koniec gry. Wygralo AI" << endl;
            waitForKeyAndClear();
            return false;
        }

        cout << "Strzela: --AI--" << endl;
        showSingleBoard(aiEnemyBoard);
        shootComboAi(player1SelfBoard, aiEnemyBoard, player1ShipsArray, shipsQuantityArray);
        if (!isAnyShipAlive(aiSelfBoard))
        {
            cout << "Koniec gry. Wygral/a " << firstPlayer << "!" << endl;
            waitForKeyAndClear();
            return true;
        }
        if (!isAnyShipAlive(player1SelfBoard))
        {
            cout << "Koniec gry. Wygralo AI" << endl;
            waitForKeyAndClear();
            return false;
        }
    }
    return true;
}
void BattleWithAi::resetProbabilityAroundSunkShip(coords start, int shipSize, char direction)
{
    coords end = {0, 0};
    switch (direction)
    {
    case 'N':
    case 'n':
        end = {start.rowNumber - shipSize + 1, start.columnNumber};
        break;
    case 'E':
    case 'e':
        end = {start.rowNumber, start.columnNumber + shipSize - 1};
        break;
    case 'S':
    case 's':
        end = {start.rowNumber + shipSize - 1, start.columnNumber};
        break;
    case 'W':
    case 'w':
        end = {start.rowNumber, start.columnNumber - shipSize + 1};
        break;
    }

    int minRow = max(0, min(start.rowNumber, end.rowNumber) - 1);
    int maxRow = min(sizeOfBoard - 1, max(start.rowNumber, end.rowNumber) + 1);
    int minCol = max(0, min(start.columnNumber, end.columnNumber) - 1);
    int maxCol = min(sizeOfBoard - 1, max(start.columnNumber, end.columnNumber) + 1);

    for (int i = minRow; i <= maxRow; ++i)
    {
        for (int j = minCol; j <= maxCol; ++j)
        {
            probabilityBoard[i][j] = 0;
        }
    }
}
