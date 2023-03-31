#include <iostream>
using namespace std;

char board[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
char currentPlayer = 'X';

void drawBoard() {
    cout << "  1 2 3" << endl;
    for (int i = 0; i < 3; i++) {
        cout << i + 1 << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool checkForWin() {
    // проверка рядов
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return true;
    }

    // проверка столбцов
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return true;
    }

    // проверка диагоналей
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return true;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return true;

    return false;
}

void switchPlayer() {
    if (currentPlayer == 'X')
        currentPlayer = 'O';
    else
        currentPlayer = 'X';
}

bool makeMove(int row, int col) {
    if (board[row][col] == ' ') {
        board[row][col] = currentPlayer;
        return true;
    }
    else {
        return false;
    }
}

int main() {
    int row, col;
    bool gameOver = false;

    while (!gameOver) {
        drawBoard();
        cout << "Player " << currentPlayer << " turn. Enter row and column: ";
        cin >> row >> col;
        row--;
        col--;

        if (makeMove(row, col)) {
            if (checkForWin()) {
                cout << "Player " << currentPlayer << " wins!" << endl;
                gameOver = true;
            }
            else {
                switchPlayer();
            }
        }
        else {
            cout << "That position is already taken. Please choose another." << endl;
        }
    }

    drawBoard();
    return 0;
}
