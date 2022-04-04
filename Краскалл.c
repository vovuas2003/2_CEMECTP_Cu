/*
1. Здесь, пожалуй, оптимально будет ввести ребра и начать их "красить".
2. Вводим матрицу смежности(отсюда можно узнать кол-во ребер) -> превращаем её в массив ребер -> сортируем этот массив
-> выбираем наименьшие ребра, крася их вершины, пока все вершины не будут покрашены в один цвет.
...
Пока все ребра не раскрашены:
	Выбираем ребро
	Если это цикл:
		следующее ребро
*/

#include <stdio.h>
#include <stdlib.h>


typedef struct edge {
	int begin;
	int end;
	int len;
}Edge;


int** create_massiv_distance(int** massiv, int* n); // создание двумерного массива
void print_massiv_distance(int** massiv, int n); // печать двумерного квадратного массива
void delete_massiv(int** massiv, int n); // освобождение памяти
int amount_edge(int **massiv, int n); // возращает количество ребер массива смежности
Edge* create_edge_vector(int **massiv, int n, int size);// создаёт массив ребер
void print_vector_edge(Edge* vector, int size); // печатает ребра
void sorted_vector_edge(Edge* vector, int size);// сортировка массива вектора по длине ребер
void print_massiv_to_edge(int** massiv, int n); // печатает ребра из матрицы смежности
int** solution(Edge* vector, int size, int size_vertex);
int massiv_equal_not_zero(int *massiv, int size) {
	for (int i = 0; i < size; i++) {
		if (massiv[0] != massiv[i] || massiv[0] == 0) {
			return 0;
		}
	}
	return 1;
}
void paint_the_vertices(Edge* vector, int size, int need_vertix, int dop_color, int *paint) {
	for (int i = 0; i < size; i++) {
		//ищем совпадение вершин
		if (vector[i].begin == need_vertix) {//узел, в котором мы находимся
			if (paint[vector[i].end] == dop_color) {
				paint[vector[i].end] = paint[need_vertix];
				paint_the_vertices(vector, size, vector[i].end, dop_color, paint);
			}
		}
		else if (vector[i].end == need_vertix) {
			if (paint[vector[i].begin] == dop_color) {
				paint[vector[i].begin] = paint[need_vertix];
				paint_the_vertices(vector, size, vector[i].begin, dop_color, paint);
			}
		}
	}
}

int main() {
	freopen("KpacKaJl.txt", "r", stdin);
	int** massiv = NULL;
	int n;
	int** problem = NULL;//остовное дерево
	////// подготавливаемся к решению
	massiv = create_massiv_distance(massiv, &n);
	Edge* vector = NULL;
	int size = amount_edge(massiv, n);
	vector = create_edge_vector(massiv, n, size);
	sorted_vector_edge(vector, size);
	/////
	problem = solution(vector, size, n);
	print_massiv_to_edge(problem, n);

	delete_massiv(massiv, n);
	delete_massiv(problem, n);
	free(vector);
}

int** solution(Edge* vector, int size, int size_vertex) {
	int** problem = (int**)calloc(size_vertex, sizeof(int*));// остовное дерево
	for (int i = 0; i < size_vertex; i++) {
		problem[i] = (int*)calloc(size_vertex, sizeof(int));
	}
	int* paint = (int*)calloc(size_vertex, sizeof(int));//краска каждой вершины
	int n = 0;
	int color = 1;
	int dop_color;
	while (n != size ) {//пока все вершины не раскрашены
		// проверяем на цикл
		if ((paint[vector[n].begin] == paint[vector[n].end]) && (paint[vector[n].begin] != 0 || paint[vector[n].end] != 0)) {
			n++;
			continue;
		}
		else {
			if (paint[vector[n].begin] == 0 && paint[vector[n].end] == 0) {//обе вершины незакрашены
				paint[vector[n].begin] = color;
				paint[vector[n].end] = color;
				problem[vector[n].begin][vector[n].end] = vector[n].len;
				color++;
			}
			else if (paint[vector[n].begin] == 0) {//одна вершина закрашена
				paint[vector[n].begin] = paint[vector[n].end];
				problem[vector[n].begin][vector[n].end] = vector[n].len;
			}
			else if (paint[vector[n].end] == 0) {//одна вершина закрашена
				paint[vector[n].end] = paint[vector[n].begin];
				problem[vector[n].begin][vector[n].end] = vector[n].len;
			}
			else {//обе вершины закрашены
				dop_color = paint[vector[n].end];//хотим отследить все соединения с этой вершиной
				paint[vector[n].end] = paint[vector[n].begin];
				problem[vector[n].begin][vector[n].end] = vector[n].len;
				paint_the_vertices(vector, size, vector[n].end, dop_color, paint);
			}
			n++;
		}
	}
	free(paint);
	return problem;
}
void print_massiv_to_edge(int** massiv, int n) {
	printf("..............\n");
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (massiv[i][j] != 0) {
				printf("%i - %i: %i\n", i, j, massiv[i][j]);
			}
		}
	}
}
void sorted_vector_edge(Edge* vector, int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = (size - 1); j > i; j--) {
			if (vector[j - 1].len > vector[j].len) {
				Edge temp = vector[j - 1];
				vector[j - 1] = vector[j];
				vector[j] = temp;
			}
		}
	}
}
void print_vector_edge(Edge* vector, int size) {
	for (int i = 0; i < size; i++) {
		printf("%i-%i: %i\n", vector[i].begin, vector[i].end, vector[i].len);
	}
}
Edge* create_edge_vector(int** massiv, int n, int size) {
	Edge* vector = (Edge*)calloc(size, sizeof(Edge));
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (massiv[i][j] != 0) {
				size--;// заполним с конца, чтобы не вводить лишнюю переменную
				vector[size].begin = i;
				vector[size].end = j;
				vector[size].len = massiv[i][j];
			}
		}
	}
	return vector;
}
int amount_edge(int** massiv, int n) {
	int edge = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (massiv[i][j] != 0) {
				edge++;
			}
		}
	}
	return edge;
}
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
	return massiv;
}
void print_massiv_distance(int** massiv, int n) {
	printf("..........\n");
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

/*
Содержание файла KpacKaJl.txt,
который должен находиться в той же директории, что и exe файл

5
0 9 75 0 0
9 0 95 19 42
75 95 0 51 66
0 19 51 0 31
0 42 66 31 0

Ответ:

0 - 1: 9
1 - 3: 19
2 - 3: 51
3 - 4: 31
*/
