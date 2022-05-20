/*
#define _CRT_SECURE_NO_WARNINGS
*/

#include <stdio.h>
#include <stdlib.h>

int AMOUNT_SOLUTION = 0;

void print_massiv_N(int* arr, int N);
int** create_massiv_N_N(int N); // создание квадратного массива размера N
void delete_massiv_N_N(int** massiv, int N);//удаление квадратного массива
void print_massiv_N_N(int** massiv, int N);//вывод квадратного массива
int** copy_massiv_N_N(int** massiv, int N);// копирование квадратного массива
int* copy_massiv_N(int* arr, int N);//копирование одномерного массива
int empty_massiv(int* arr, int N); // 0 - строка не занята, 1 - строка занята
// возвращает 1, если есть незанятые строки
int first_empty_line(int* arr, int N); // первая незанятая строка
int amount_of_busy_lines(int* arr, int N);// количество занятых строк
void put_the_queen(int** massiv, int* arr, int N, int column, int line);

/*
0 - пустая клетка
1 - клетка, в которую бьёт ферзь
2 - клетка, в которой стоит ферзь
*/

void solution(int** massiv, int* line_information, int N);
void proverka(int** massiv, int N); // проверяет все ли 2 на месте



int main() {
    int size_massiv;
    scanf("%d", &size_massiv);
    printf("\n");
    int** massiv = NULL;
    int* line_information = NULL;
    /*
    line_information отвечает за расстановку ферзей на строках
    arr[0] - 1 (верхняя) строка и т.д.
     */

    massiv = create_massiv_N_N(size_massiv);
    line_information = (int*)calloc(size_massiv, sizeof(int));

    solution(massiv, line_information, size_massiv);
    printf("%d", AMOUNT_SOLUTION);

    delete_massiv_N_N(massiv, size_massiv);
    free(line_information);
}

void print_massiv_N(int* arr, int N) {
    printf(".............\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf(".............\n");
}
int** create_massiv_N_N(int N) {
    int** massiv = (int**)calloc(N, sizeof(int*));
    for (int i = 0; i < N; i++) {
        massiv[i] = (int*)calloc(N, sizeof(int));
    }
    return massiv;
}
void delete_massiv_N_N(int** massiv, int N) {
    for (int i = 0; i < N; i++) {
        free(massiv[i]);
    }
    free(massiv);
}
void print_massiv_N_N(int** massiv, int N) {
    printf("............\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", (massiv[i][j] == 2) ? ('F') : ('*'));
        }
        printf("\n");
    }
    printf("............\n");
}
int** copy_massiv_N_N(int** massiv, int N) {
    int** massiv1 = create_massiv_N_N(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            massiv1[i][j] = massiv[i][j];
        }
    }
    return massiv1;
}
int* copy_massiv_N(int* arr, int N) {
    int* arr1 = (int*)calloc(N, sizeof(int));
    for (int i = 0; i < N; i++) {
        arr1[i] = arr[i];
    }
    return arr1;
}
int empty_massiv(int* arr, int N) {
    for (int i = 0; i < N; i++) {
        if (arr[i] == 0) {
            return 1;
        }
    }
    return 0;
}
int first_empty_line(int* arr, int N) {
    for (int i = 0; i < N; i++) {
        if (arr[i] == 0) {
            return i;
        }
    }
    printf("\nFALSE\n");
    return -1;
}
int amount_of_busy_lines(int* arr, int N) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        if (arr[i] == 1) {
            sum++;
        }
    }
    return sum;
}
void put_the_queen(int** massiv, int* arr, int N, int column, int line) {
    if (massiv[line][column]) {
        return;
    }
    arr[line] = 1;
    /*
    Смотрим каждую клетку и проверяем, попадает ли в нее ферзь
    */
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            if (abs(x - column) == abs(y - line) || x == column || y == line) {
                massiv[y][x] = 1;
            }
        }
    }
    massiv[line][column] = 2; // место, где стоит ферзь
}
void proverka(int** massiv, int N) {
    int sum_2 = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (massiv[i][j] == 2) {
                sum_2++;
            }
        }
    }
    if (sum_2 != N) {
        printf("Error!");
        exit(1);
    }
}
void solution(int** massiv, int* line_information, int N) {
    if (!empty_massiv(line_information, N)) {
        proverka(massiv, N);
        print_massiv_N_N(massiv, N);
        AMOUNT_SOLUTION++;
    }
    else {
        int** massiv1 = copy_massiv_N_N(massiv, N);
        int* line_information1 = copy_massiv_N(line_information, N);
        int line = first_empty_line(line_information1, N);

        for (int column = 0; column < N; column++) {
            put_the_queen(massiv1, line_information1, N, column, line);

            if (!(amount_of_busy_lines(line_information1, N) == amount_of_busy_lines(line_information, N))) {
                solution(massiv1, line_information1, N);
                delete_massiv_N_N(massiv1, N);
                massiv1 = copy_massiv_N_N(massiv, N);//возвращаемся к исходному состоянию
                line_information1[line] = 0;
            }
        }
        free(line_information1);
        delete_massiv_N_N(massiv1, N);
    }
}
