#include <stdio.h>
#include <stdlib.h>

int** create_massiv_N_N(int N);
void delete_massiv_N_N(int** massiv, int N);
int sum_of_moves(int** massiv, int N, int x1, int y1); // количество ходов из этой клетки
void solution(int** massiv, int N, int x1, int y1, int* horse); // x1 - строка, y1 - столбец
void massiv_N_N_to_null(int** massiv, int N);
void print_massiv_N_N(int** massiv, int N);
int checking(int** massiv, int N); // простая проверка суммой
int big_checking(int** massiv, int N); // 0 - решения нет, 1 - решение есть, 2 - решение при другой стартовой клетке

int main() {
	int size_massiv;
	scanf("%d", &size_massiv);
	int** massiv = NULL; // доска
	int horse = 1; // счётчик ходов
	int x1, y1; //координаты старта (нумерация с 1)
	scanf("%d %d", &x1, &y1);
	printf("\n");
    x1--;
    y1--;

    if (x1 < 0 || x1 >=size_massiv || y1 < 0 || y1 >=size_massiv) {
        printf("Error of starting position!\n");
        return 1;
    }

	massiv = create_massiv_N_N(size_massiv);
	massiv[x1][y1] = 1; // ставим коня

	solution(massiv, size_massiv, x1, y1, &horse);
	int number_solution = big_checking(massiv, size_massiv);

	if (number_solution == 1) {
		printf("OK!\n\n");
		print_massiv_N_N(massiv, size_massiv);
	} else if (number_solution == 2) {
		printf("Change starting position!\n\n");
		print_massiv_N_N(massiv, size_massiv);
	} else {
		printf("Can't find solution!\n");
	}

	delete_massiv_N_N(massiv, size_massiv);
    return 0;
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

int sum_of_moves(int** massiv, int N, int x1, int y1) {

	int sum = 0;
	int moving[8][2] = { // ходы коня
		{-2, -1}, {-2, 1},
		{2, -1}, {2, 1},
		{-1, -2}, {1, -2},
		{-1, 2}, {1, 2}
	};
	int x3 = 0, y3 = 0;

	for (int i = 0; i < 8; i++) { // движемся по возможным ходам
		x3 = x1 + moving[i][0];
		y3 = y1 + moving[i][1];

		if ((x3 >= 0 && y3 >= 0) && (x3 < N && y3 < N)) { // проверяем возможность хода
			if (massiv[x3][y3] == 0) { // если клетка свободна
				sum += 1;
			}
		}
	}
	return sum;
}

void solution(int** massiv, int N, int x1, int y1, int* horse) {
	int moving[8][2] = {
		{-2, -1}, {-2, 1},// 2 вниз влево-вправо
		{2, -1}, {2, 1},// 2 вверх влево-вправо
		{-1, -2}, {1, -2},// 2 влево вверх-вниз
		{-1, 2}, {1, 2}// 2 вправо вверх-вниз
	};
	int min = 9;
	int x2 = 0, y2 = 0;
	int x3 = 0, y3 = 0; // выбранные клетки

	int sum = 0;
	int flag = 0;
	// flag == 0 все доступные клетки заняты, конь в тупике
	// flag == 1 ещё есть доступные клетки продолжаем ходить

	for (int i = 0; i < 8; i++) { // движемся по возможным ходам
		x2 = x1 + moving[i][0];
		y2 = y1 + moving[i][1];
		if ((x2 >= 0 && y2 >= 0) && (x2 < N && y2 < N)) { // проверяем возможность хода
			if (massiv[x2][y2] == 0) { // если клетка свободна
				sum = sum_of_moves(massiv, N, x2, y2);
				if (sum < min) {
					flag = 1;
					min = sum;
					x3 = x2;
					y3 = y2;
				}
			}
		}
	}

	if (flag) {
		*horse += 1;
		massiv[x3][y3] = *horse;
		solution(massiv, N, x3, y3, horse);
	}

}

void massiv_N_N_to_null(int** massiv, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			massiv[i][j] = 0;
		}
	}
}

void print_massiv_N_N(int** massiv, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%5d", massiv[i][j]);
		}
		printf("\n");
	}
}

int checking(int** massiv, int N) {
	long long unsigned sum = 0;
	long long unsigned total_sum = 0;
	if (N % 2 == 1) {
		sum = (1 + N * N) / 2 * ( N * N);
	}
	else {
		sum = (N * N) / 2 * (N * N + 1);
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			total_sum += massiv[i][j];
		}
	}
	if (sum == total_sum) {
		return 1;
	}
	return 0;
}

int  big_checking(int** massiv, int N) {
	if (checking(massiv, N)) {
		return 1;
	}
	else {
		int horse = 1;// начинаем перебирать все начальные позиции
		for (int x1 = 0; x1 < N; x1++) {
			for (int y1 = 0; y1 < N; y1++) {
				horse = 1;
				massiv_N_N_to_null(massiv, N);
				massiv[x1][y1] = 1;
				solution(massiv, N, x1, y1, &horse);
				if (checking(massiv, N)) {
					return 2;
				}
			}
		}
		return 0;
	}
}
