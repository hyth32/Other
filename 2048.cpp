#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <stdio.h>

using namespace std;

const int ROWS = 4;
const int COLS = 4;
int game_board[ROWS][COLS];

void init_game() {
    // Заполняем игровое поле пустыми ячейками
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            game_board[i][j] = 0;
        }
    }

    // Добавляем две случайные плитки на игровое поле со значениями 2 или 4
    srand(static_cast<unsigned int>(time(NULL))); // Инициализируем генератор случайных чисел
    int rand_row1 = rand() % ROWS;
    int rand_col1 = rand() % COLS;
    int rand_row2 = rand() % ROWS;
    int rand_col2 = rand() % COLS;

    while (rand_row1 == rand_row2 && rand_col1 == rand_col2) {
        rand_row2 = rand() % ROWS;
        rand_col2 = rand() % COLS;
    }

    game_board[rand_row1][rand_col1] = (rand() % 2 + 1) * 2; // Генерируем случайное число 2 или 4
    game_board[rand_row2][rand_col2] = (rand() % 2 + 1) * 2;
}

const char EMPTY = ' ';
void draw_game() {
    system("cls"); // очищаем консоль перед каждым обновлением

    // Отрисовываем верхнюю границу
    printf("##############\n");


    // Отрисовываем содержимое игрового поля
    for (int i = 0; i < ROWS; i++) {
        printf("#"); // Отрисовываем левую границу

        for (int j = 0; j < ROWS; j++) {
            if (game_board[i][j] == 0) {
                printf("   "); // Отрисовываем пустые ячейки
            }
            else {
                printf("%-3d", game_board[i][j]); // Отрисовываем значения ячеек
            }
        }

        printf("#\n"); // Отрисовываем правую границу
    }

    // Отрисовываем нижнюю границу
    printf("##############\n");
}


enum Direction { UP, DOWN, LEFT, RIGHT };

bool move_tiles(Direction direction) {
    bool moved = false;

    // Двигаем плитки в соответствующем направлении
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            // Если текущая ячейка пуста, переходим к следующей
            if (game_board[i][j] == 0) {
                continue;
            }

            // Иначе, ищем ближайшую ячейку в заданном направлении
            int row = i;
            int col = j;
            while (true) {
                if (direction == UP) {
                    row--;
                }
                else if (direction == DOWN) {
                    row++;
                }
                else if (direction == LEFT) {
                    col--;
                }
                else if (direction == RIGHT) {
                    col++;
                }

                // Если достигли границы доски, останавливаемся
                if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
                    break;
                }

                // Если найдена пустая ячейка, перемещаем текущую плитку туда
                if (game_board[row][col] == 0) {
                    game_board[row][col] = game_board[i][j];
                    game_board[i][j] = 0;
                    i = row;
                    j = col;
                    moved = true;
                }
                else {
                    // Иначе, если найдена ячейка с таким же значением, объединяем их
                    if (game_board[row][col] == game_board[i][j]) {
                        game_board[row][col] *= 2;
                        game_board[i][j] = 0;
                        moved = true;
                    }
                    break;
                }
            }
        }
    }

    return moved;
}

void add_tile() {
    // Находим все пустые ячейки на доске
    vector<pair<int, int>> empty_cells;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (game_board[i][j] == 0) {
                empty_cells.push_back(make_pair(i, j));
            }
        }
    }

    // Если есть пустые ячейки, выбираем случайную и добавляем на нее новую плитку
    if (!empty_cells.empty()) {
        int index = rand() % empty_cells.size();
        int value = (rand() % 10 == 0) ? 4 : 2; // С вероятностью 1/10 добавляем плитку со значением 4
        game_board[empty_cells[index].first][empty_cells[index].second] = value;
    }
}

bool check_game_over() {
    // Проверяем, есть ли на доске пустые ячейки
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (game_board[i][j] == 0) {
                return false; // Если есть хотя бы одна пустая ячейка, игра не окончена
            }
        }
    }

    // Проверяем, можно ли объединить какие-либо плитки на доске
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (j < COLS - 1 && game_board[i][j] == game_board[i][j + 1]) {
                return false; // Если можно объединить плитки в строке, игра не окончена
            }
            if (i < ROWS - 1 && game_board[i][j] == game_board[i + 1][j]) {
                return false; // Если можно объединить плитки в столбце, игра не окончена
            }
        }
    }

    return true; // Если пустых ячеек нет и нельзя объединить плитки, игра окончена
}


int main() {
    init_game();

    while (true) {
        draw_game();

        int move_direction = _getch();

        bool moved;
        switch (move_direction) {
        case 'w':
            moved = move_tiles(UP);
            break;
        case 's':
            moved = move_tiles(DOWN);
            break;
        case 'a':
            moved = move_tiles(LEFT);
            break;
        case 'd':
            moved = move_tiles(RIGHT);
            break;
        default:
            continue;
        }

        if (moved) {
            add_tile();
        }

        if (check_game_over()) {
            printf("Game over!\n");
            break;
        }
    }

    return 0;
}