#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10

char field[MAX][MAX];

int readNumber() {
    char line[100];
    int number;

    while (1) {
        if (fgets(line, sizeof(line), stdin) == NULL) {
            exit(0);
        }
        if (sscanf(line, "%d", &number) == 1) {
            return number;
        }
        printf("Введите число: ");
    }
}

void clearScreen() {
    printf("\033[2J\033[H");
}

void resetField(int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            field[i][j] = '.';
        }
    }
}

void printField(int size) {
    printf("    ");
    for (int j = 0; j < size; j++) {
        printf("%3d", j + 1);
    }
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf("%3d ", i + 1);
        for (int j = 0; j < size; j++) {
            printf("%3c", field[i][j]);
        }
        printf("\n");
    }
}

int hasWon(int size, char sign) {
    for (int i = 0; i < size; i++) {
        int rowWin = 1;
        int colWin = 1;

        for (int j = 0; j < size; j++) {
            if (field[i][j] != sign) rowWin = 0;
            if (field[j][i] != sign) colWin = 0;
        }

        if (rowWin || colWin) return 1;
    }

    int diagonal1 = 1;
    int diagonal2 = 1;

    for (int i = 0; i < size; i++) {
        if (field[i][i] != sign) diagonal1 = 0;
        if (field[i][size - 1 - i] != sign) diagonal2 = 0;
    }

    return diagonal1 || diagonal2;
}

int isFull(int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (field[i][j] == '.') return 0;
        }
    }
    return 1;
}

void botMove(int size, char sign) {
    int row, col;
    do {
        row = rand() % size;
        col = rand() % size;
    } while (field[row][col] != '.');

    field[row][col] = sign;
}

int main() {
    srand(time(NULL));

    printf("КРЕСТИКИ-НОЛИКИ\n\n");

    printf("Режим: 1 - с ботом, 2 - с другом: ");
    int mode = readNumber();
    while (mode != 1 && mode != 2) {
        printf("Выберите 1 или 2: ");
        mode = readNumber();
    }

    printf("Размер поля (от 3 до %d): ", MAX);
    int size = readNumber();
    while (size < 3 || size > MAX) {
        printf("Введите размер от 3 до %d: ", MAX);
        size = readNumber();
    }

    printf("Кто ходит первым? 1 - X, 2 - O: ");
    int firstChoice = readNumber();
    while (firstChoice != 1 && firstChoice != 2) {
        printf("Выберите 1 или 2: ");
        firstChoice = readNumber();
    }
    char firstSign = 'X';
    if (firstChoice == 2) firstSign = 'O';

    char playerSign = 'X';
    if (mode == 1) {
        printf("Ваш знак: 1 - X, 2 - O: ");
        int playerChoice = readNumber();
        while (playerChoice != 1 && playerChoice != 2) {
            printf("Выберите 1 или 2: ");
            playerChoice = readNumber();
        }
        if (playerChoice == 2) playerSign = 'O';
    }

    int again = 1;
    while (again == 1) {
        resetField(size);       
        char turn = firstSign; 

        while (1) {
            clearScreen();
            printf("КРЕСТИКИ-НОЛИКИ (%d x %d)\n\n", size, size);
            printField(size);
            printf("\nСейчас ходит: %c\n", turn);

            if (mode == 1 && turn != playerSign) {
                botMove(size, turn);
                printf("Бот сделал ход.\n");
            } else {
                int row, col;

                while (1) {
                    printf("Строка: ");
                    row = readNumber() - 1;
                    printf("Столбец: ");
                    col = readNumber() - 1;

                    if (row < 0 || row >= size || col < 0 || col >= size) {
                        printf("Такой клетки нет. Попробуйте снова.\n");
                    } else if (field[row][col] != '.') {
                        printf("Клетка занята. Попробуйте снова.\n");
                    } else {
                        field[row][col] = turn;
                        break;
                    }
                }
            }

            if (hasWon(size, turn)) {
                clearScreen();
                printField(size);
                printf("\nПобеда %c!\n", turn);
                break;
            }

            if (isFull(size)) {
                clearScreen();
                printField(size);
                printf("\nНичья!\n");
                break;
            }

            if (turn == 'X') turn = 'O';
            else turn = 'X';
        }

        printf("\nНачать заново? 1 - да, 0 - выход: ");
        again = readNumber();
        while (again != 0 && again != 1) {
            printf("Выберите 1 или 0: ");
            again = readNumber();
        }
    }

    printf("Спасибо за игру!\n");
    return 0;
}
