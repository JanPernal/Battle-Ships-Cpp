#include "board.h"
#include <iostream>

using namespace std;

Board::Board(int size) : sizeOfBoard(size)
{
}
string Board::getPlayerName(int numberOfPlayer)
{
    string playerName;
    cout << "Graczu nr. " << numberOfPlayer << ", podaj swoja nazwe :" << endl;
    cin >> playerName;
    return playerName;
}

int Board::intValidation()
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

char Board::characterValidation()
{
    char character;
    cin >> character;

    // todo: Sprawdzanie, czy wystąpił błąd
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(100000, '\n');
        cout << "Invalid character, type valid character!";
        cin >> character;
    }
    return character;
}

int Board::getRandomRow()
{
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> distInt(0, sizeOfBoard - 1);
    int randomNumber = distInt(gen);
    return randomNumber;
}

char Board::getRandomCol()
{
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> distChar('A', 'A' + sizeOfBoard - 1);
    int randomCharacter = distChar(gen);
    return randomCharacter;
}

char Board::getRandomDirection()
{
    char directions[] = {'n', 'e', 's', 'w'};
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> distDirection(0, 3);
    char randomDirection = directions[distDirection(gen)];
    return randomDirection;
}

char **Board::createEmptyBoard()
{
    // todo: Allocate memory for the 2D array
    char **board = new char *[sizeOfBoard];
    for (int i = 0; i < sizeOfBoard; ++i)
    {
        board[i] = new char[sizeOfBoard];
    }

    // todo: Initialize the board with empty spaces
    for (int i = 0; i < sizeOfBoard; ++i)
    {
        for (int j = 0; j < sizeOfBoard; ++j)
        {
            board[i][j] = ' ';
        }
    }

    // todo: Return the created board
    return board;
}

void Board::printPlayerNickname(string playerNickname)
{
    cout << "--" << playerNickname << "'s Board--" << endl;
}

void Board::printAlphabeth()
{
    char letter = 'A';
    cout << "   ";
    for (int i = 0; i < sizeOfBoard; i++)
    {
        cout << " " << letter++ << "  ";
    }
    // cout << endl;
}

void Board::printSheet(bool integer)
{
    if (integer)
    {
        cout << "  +";
        for (int k = 0; k < sizeOfBoard; k++)
        {
            cout << "----+";
        }
    }
    else
    {
        cout << "  +";
        for (int k = 0; k < sizeOfBoard; k++)
        {
            cout << "---+";
        }
    }
}

void Board::printFullBlock(char **board, int i, int j)
{
    if (board[i][j] == '#')
    {
        cout << "\u2588";
    }
    else
    {
        cout << board[i][j];
    }
}

void Board::printData(int i, char **board)
{
    // todo: show row number
    cout << i + 1;

    // todo: add spaces after row number
    if (i < 9)
    {
        cout << " ";
    }

    // todo: add first row separator
    cout << "|";

    for (int j = 0; j < sizeOfBoard; j++)
    {

        cout << " ";
        printFullBlock(board, i, j);
        cout << " |";
    }
}

void Board::printData(int i, int **board)
{

    // todo: show row number
    cout << i + 1;

    // todo: add spaces after row number
    if (i < 9)
    {
        cout << " ";
    }

    // todo: add first row separator
    cout << "|";

    for (int j = 0; j < sizeOfBoard; j++)
    {

        cout << " ";
        if (board[i][j] < 10)
        {
            cout << 0;
        }
        cout << board[i][j] << " |";
    }
}

void Board::showBoard(char **myBoard, char **enemyBoard)
{
    string space = "      ";
    cout << endl;
    // todo: show letters of columns
    printAlphabeth();
    cout << space;
    printAlphabeth();
    cout << endl;

    // todo: show Full Board
    for (int i = 0; i < sizeOfBoard; i++)
    {
        printSheet(0);
        cout << space;
        printSheet(0);
        cout << endl;

        printData(i, myBoard);
        cout << space;
        printData(i, enemyBoard);
        cout << endl;
    }
    printSheet(0);
    cout << space;
    printSheet(0);
    cout << endl;
}

void Board::showSingleBoard(char **board)
{
    cout << endl;
    printAlphabeth();
    cout << endl;
    for (int i = 0; i < sizeOfBoard; i++)
    {
        printSheet(0);
        cout << endl;
        printData(i, board);
        cout << endl;
    }
    printSheet(0);
    cout << endl;
}

void Board::showSingleBoard(int **Board)
{
    cout << endl;
    printAlphabeth();
    cout << endl;
    for (int i = 0; i < sizeOfBoard; i++)
    {
        printSheet(1);
        cout << endl;
        printData(i, Board);
        cout << endl;
    }
    printSheet(1);
    cout << endl;
}

void Board::clearConsole()
{
    system("cls");
}

void Board::waitForKeyAndClear()
{
    cout << endl
         << "Nacisnij dowolny klawisz, aby wyczyscic konsole..." << endl;

    _getch();

    clearConsole();
    clearConsole();
}
void Board::pressAnyKeyToSwapPlayers()
{
    cout << "Graczu 1, naciśnij dowolny przycisk by schować swoje plansze..." << endl;
    _getch();
    clearConsole();
    cout << "Graczu 2, naciśnij dowolny przycisk by odsłonić swoje plansze..." << endl;
    _getch();
    clearConsole();
}
