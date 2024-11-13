#include "game.h"

int Game::getSizeOfBoard()
{
    float sizeOfBoard;
    cout << "Podaj wielkosc planszy [5-25]:" << endl;
    sizeOfBoard = validation();
    if (sizeOfBoard >= 5 && sizeOfBoard <= 25)
    {
        return sizeOfBoard;
    }
    else
    {
        return getSizeOfBoard();
    }
}

void Game::displayInstructions()
{
    cout << "===== Instrukcja gry w statki =====\n";
    cout << "1. Plansza: Gra toczy sie na planszy o ustalonym rozmiarze.\n";
    cout << "2. Statki: Kazdy gracz rozklada na swojej planszy swoje statki (np. 1-, 2-, 3- i 4-masztowe).\n";
    cout << "3. Ruchy: Gracze na zmiane oddaja strzaly, podajac wspolrzedne celu (np. A5, B7).\n";
    cout << "4. Trafienia i Pudla:\n";
    cout << "   - Jesli strzal trafi w statek przeciwnika, jest \"Trafiony\".\n";
    cout << "   - Jesli wszystkie pola statku zostana trafione, statek jest \"Zatopiony\".\n";
    cout << "5. Cel gry: Zatopic wszystkie statki przeciwnika przed nim!\n";
    cout << "====================================\n";
}

Game::Game()
{
}

int Game::validation()
{
    int number;
    cin >> number;

    // todo: Sprawdzanie, czy wystąpił błąd
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(100000, '\n');
        cout << "Invalid number, type integer number!";
        cin >> number;
    }
    return number;
}

bool Game::booleanValidation()
{
    bool boolean;
    cin >> boolean;

    while (cin.fail())
    {
        cin.clear();
        cin.ignore(100000, '\n');
        cout << "Nieprawidłowa wartość, wpisz 0 albo 1!";
        cin >> boolean;
    }
    return boolean;
}

void Game::printResult(string player1, string player2, int pl1, int pl2)
{
    cout << "| " << player1 << " |[" << pl1 << " : " << pl2 << "]| " << player2 << " |" << endl;
}

bool Game::isPlayAgainActive()
{
    bool playAgain = false;
    cout << "Jesli chcesz zagrac ponownie wcisnij ->1<-, jesli chcesz zamknac gre wciscnij 0. :" << endl;
    playAgain = booleanValidation();

    return playAgain;
}

void Game::runGame()
{
    displayInstructions();
    int sizeOfBoard = getSizeOfBoard();
    Board newBoard(sizeOfBoard);
    newBoard.clearConsole();
    int firstPlayerWins = 0;
    int secondPlayerWins = 0;
    bool playAgain = true;

    bool isChoosedAi;
    cout << "Jesli chcesz zagrac z drugim graczem wcisnij 0," << endl
         << "Jesli chcesz zagrac z komputerem wcisnij 1" << endl;
    isChoosedAi = booleanValidation();
    if (isChoosedAi)
    {
        BattleWithAi newBattle(sizeOfBoard);
        newBattle.clearConsole();
        string firstPlayer = newBattle.getPlayerName(1);
        newBattle.waitForKeyAndClear();

        int **shipsQuantityArray = newBattle.calculateAmountOfShips();

        Player players(sizeOfBoard);
        //     GRA z AI
        while (playAgain)
        {
            printResult(firstPlayer, "AI", firstPlayerWins, secondPlayerWins);

            char **firstPlayerSelfBoard = newBattle.createEmptyBoard();
            char **firstPlayerEnemyBoard = newBattle.createEmptyBoard();
            char **aiSelfBoard = newBattle.createEmptyBoard();
            char **aiEnemyBoard = newBattle.createEmptyBoard();
            bool isChosedManual;
            cout << "Jesli chcesz manualnie wypelnić plansze: wcisnij 0," << endl
                 << "Jesli chcesz by została wypełniona losowo: wciscnij 1" << endl;
            isChosedManual = booleanValidation();
            shipData **firstPlayerShipsArray;
            if (isChosedManual)
            {
                firstPlayerShipsArray = players.initializeAiBoards(shipsQuantityArray, firstPlayerSelfBoard, firstPlayerEnemyBoard, firstPlayer);
            }
            else
            {
                firstPlayerShipsArray = players.initializeBoards(shipsQuantityArray, firstPlayerSelfBoard, firstPlayerEnemyBoard, firstPlayer);
            }
            cout << "Wszystkie statki wypelnione!" << endl;
            newBattle.waitForKeyAndClear();

            shipData **aiShipsArray = players.initializeAiBoards(shipsQuantityArray, aiSelfBoard, aiEnemyBoard, "AI");
            newBattle.clearConsole();
            cout << "Wszystkie statki wypelnione!" << endl;
            newBattle.waitForKeyAndClear();

            bool result = newBattle.shootingTurnsAi(firstPlayerSelfBoard, firstPlayerEnemyBoard, aiSelfBoard, aiEnemyBoard, firstPlayerShipsArray, aiShipsArray, shipsQuantityArray, firstPlayer);
            if (result)
            {
                firstPlayerWins += 1;
            }
            else
            {
                secondPlayerWins += 1;
            }

            printResult(firstPlayer, "AI", firstPlayerWins, secondPlayerWins);
            newBattle.waitForKeyAndClear();

            playAgain = isPlayAgainActive();
        }
        newBattle.clearConsole();
        exit(0);
    }
    else
    {
        Battle newBattle(sizeOfBoard);
        newBattle.clearConsole();
        string firstPlayer = newBattle.getPlayerName(1);
        newBattle.clearConsole();
        string secondPlayer = newBattle.getPlayerName(2);
        newBattle.waitForKeyAndClear();

        int **shipsQuantityArray = newBattle.calculateAmountOfShips();

        Player players(sizeOfBoard);
        while (playAgain)
        {
            printResult(firstPlayer, secondPlayer, firstPlayerWins, secondPlayerWins);

            char **firstPlayerSelfBoard = newBattle.createEmptyBoard();
            char **firstPlayerEnemyBoard = newBattle.createEmptyBoard();
            char **secondPlayerSelfBoard = newBattle.createEmptyBoard();
            char **secondPlayerEnemyBoard = newBattle.createEmptyBoard();

            // todo: gracz pierwszy tworzy plansze
            cout << endl
                 << "--Wypełnia " << firstPlayer << "--" << endl
                 << endl;

            bool isChosedManual = 1;

            cout << "Jesli chcesz manualnie wypelnić plansze: wcisnij 0," << endl
                 << "Jesli chcesz by została wypełniona losowo: wciscnij 1" << endl;

            newBattle.showBoard(firstPlayerSelfBoard, firstPlayerEnemyBoard);
            isChosedManual = booleanValidation();

            shipData **firstPlayerShipsArray;
            if (isChosedManual)
            {
                firstPlayerShipsArray = players.initializeAiBoards(shipsQuantityArray, firstPlayerSelfBoard, firstPlayerEnemyBoard, firstPlayer);
            }
            else
            {
                firstPlayerShipsArray = players.initializeBoards(shipsQuantityArray, firstPlayerSelfBoard, firstPlayerEnemyBoard, firstPlayer);
            }

            cout << "Wszystkie statki wypelnione!" << endl;
            newBattle.pressAnyKeyToSwapPlayers();

            cout << endl
                 << "--Wypełnia " << secondPlayer << "--" << endl
                 << endl;
            isChosedManual = 1;
            cout << "Jesli chcesz manualnie wypelnić plansze: wcisnij 0," << endl
                 << "Jesli chcesz by została wypełniona losowo: wciscnij 1" << endl;
            newBattle.showBoard(secondPlayerSelfBoard, secondPlayerEnemyBoard);
            isChosedManual = booleanValidation();
            shipData **secondPlayerShipsArray;
            if (isChosedManual)
            {
                secondPlayerShipsArray = players.initializeAiBoards(shipsQuantityArray, secondPlayerSelfBoard, secondPlayerEnemyBoard, secondPlayer);
            }
            else
            {
                secondPlayerShipsArray = players.initializeBoards(shipsQuantityArray, secondPlayerSelfBoard, secondPlayerEnemyBoard, secondPlayer);
            }
            cout << "Wszystkie statki wypelnione!" << endl;
            newBattle.pressAnyKeyToSwapPlayers();

            bool result = newBattle.shootingTurns(firstPlayerSelfBoard, firstPlayerEnemyBoard, secondPlayerSelfBoard, secondPlayerEnemyBoard, firstPlayerShipsArray, secondPlayerShipsArray, shipsQuantityArray, firstPlayer, secondPlayer);
            if (result)
            {
                firstPlayerWins += 1;
            }
            else
            {
                secondPlayerWins += 1;
            }

            printResult(firstPlayer, secondPlayer, firstPlayerWins, secondPlayerWins);
            newBattle.waitForKeyAndClear();

            playAgain = isPlayAgainActive();
        }
        newBattle.clearConsole();
        exit(0);
    }
}
