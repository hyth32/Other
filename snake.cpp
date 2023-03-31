#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <ctime>
using namespace std;

bool gameOver;
bool invalidCoord;
const int width = 30;
const int height = 15;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int tailLength;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

void ClearScreen()
{
    // очищение экрана без мигания
    COORD cursorPosition;   cursorPosition.X = 0;   cursorPosition.Y = 0;   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void Setup()
{  
    gameOver = false;
    dir = STOP;
    srand(time(0));
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw()
{
    ClearScreen();

    // верхняя грань
    for (int i = 0; i < width + 2; i++)
        cout << '#';
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            // левая грань
            if (k == 0)
                cout << '#';
            // голова
            if (i == y && k == x)
                cout << '@';
            // фрукт
            else if (i == fruitY && k == fruitX)
                cout << '*';

            else
            {
                // проверка существования хвоста с подходящими координат и отрисовка
                bool printTail = false;
                for (int j = 0; j < tailLength; j++)
                {
                    if (tailX[j] == k && tailY[j] == i)
                    {
                        cout << 'o';
                        printTail = true;
                    }
                }
                // отрисовка пустого пространства если хвоста нет 
                if (!printTail)
                    cout << ' ';
            }

            // правая грань
            if (k == width - 1)
                cout << '#';

        }
        cout << endl;
    }

    // нижняя грань
    for (int i = 0; i < width + 2; i++)
        cout << '#';
    cout << endl;

    // вывод счета
    cout << endl;
    cout << "Score: " << score << endl;

}

void Input()
{
    // проверка нажатия кнопок управления и ограничение по движению 
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w':
            if (dir != DOWN)
                dir = UP;
            break;
        case 'a':
            if (dir != RIGHT)
                dir = LEFT;
            break;
        case 's':
            if (dir != UP)
                dir = DOWN;
            break;
        case 'd':
            if (dir != LEFT)
                dir = RIGHT;
            break;
        case 'k':
            gameOver = true;
            break;
        }

    }
}

void Logic()
{
    // каждую итерацию запоминаем прошлую координату головы и записываем в prevX, prevY
    // изменяем первые значения tailX, tailY на новую координату головы

    // сохраняем tailX[i] и tailY[i] в prevX2 и prevY2 и присваиваем tailX[i] и tailY[i] к prevX и prevY.
    // присваиваем prevX и prevY к prevX2 и prevY2.

    int prevX = tailX[0];
    int prevY = tailY[0];
    int prevX2, prevY2;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < tailLength; i++)
    {
        prevX2 = tailX[i];
        prevY2 = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prevX2;
        prevY = prevY2;
    }
    // изменение координат головы в зависимости от направления
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }

    // врезался в хвост
    for (int i = 0; i < tailLength; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    // съел фрукта 
    if (x == fruitX && y == fruitY)
    {
        score += 1;
        fruitX = rand() % width;
        fruitY = rand() % height;
        // генерация нового фрукта с проверкой совпадения с хвостом
        for (int i = 0; i < tailLength; )
        {
            invalidCoord = false;
            if (tailX[i] == fruitX && tailY[i] == fruitY) {
                invalidCoord = true;
                fruitX = rand() % width;
                fruitY = rand() % height;
                break;
            }
            if (!invalidCoord)
                i++;
        }
        tailLength++;
    }

    // прохождение через границу 
    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 1;
    if (x >= width)
        x = 0;
    else if (x < 0)
        x = width - 1;
}

int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Sleep(80);
        Input();
        Logic();
    }

    return 0;
}