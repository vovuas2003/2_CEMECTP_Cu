/*
1. Всё строится на том, что мы предполагаем нахождение "минимальной" вершины
2. То есть нужно реализовать 3 цикла. Очень хорошо это рассмотрено в этом видео: https://youtu.be/HwK67u7zaEE
*/

#include <stdio.h>
#include <stdlib.h>

int** create_massiv_distance(int** massiv, int* n); // создание двумерного массива
void print_massiv_distance(int** massiv, int n); // печать двумерного массива
void delete_massiv(int** massiv, int n); // освобождение памяти
void solution(int** massiv, int n);

int main() {
	int** massiv_distance = NULL;
	int n; // n - кол-во строк, m - кол-во столбцов
	massiv_distance = create_massiv_distance(massiv_distance, &n);
	solution(massiv_distance, n);

	print_massiv_distance(massiv_distance, n);
	delete_massiv(massiv_distance, n);

}

//если маршрута нет, вводится очень большое число, к примеру, 99999(для всех "непутейных")
int** create_massiv_distance(int** massiv, int* n) {
	scanf("%i", n);
	massiv = (int**)calloc(*n, sizeof(int*));
	for (int i = 0; i < *n; i++) {
		massiv[i] = (int*)calloc(*n, sizeof(int));
	}
	for (int i = 0; i < *n; i++) {
		for (int j = 0; j < *n; j++) {
			scanf("%i", &massiv[i][j]);
		}
	}
	printf("\n");
	return massiv;
}
void print_massiv_distance(int** massiv, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%i ", massiv[i][j]);
		}
		printf("\n");
	}
}
void delete_massiv(int** massiv, int n) {
	for (int i = 0; i < n; i++) {
		free(massiv[i]);
	}
	free(massiv);
}
void solution(int** massiv, int n) {
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (massiv[i][k] + massiv[k][j] < massiv[i][j]) {
					massiv[i][j] = massiv[i][k] + massiv[k][j];
					//чтобы узнать маршрут, надо создать массив,
					//в который будем вписывать k
					//massiv_route[i][j] = k
				}
			}
		}
	}
}

/*
Пример теста: 3 вершины

0 8 5
3 0 999
999 2 0

Ответ:

0 7 5
3 0 8
5 2 0
*/
