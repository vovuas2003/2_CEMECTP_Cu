#include <stdio.h>
#include <stdlib.h>

int main() {
    //Ввод данных
    int n;
    printf("KOJIu4ECTBO BEPLLIuH: ");
    scanf("%d", &n);
    int m = n;
    int *a = (int *)calloc(n * m, sizeof(int));
    int *b = (int *)calloc(n, sizeof(int));
    printf("MATPuLLA CME}|{HOCTu, CTPOKu - uCXOg9LLLuE nYTu:\n\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i * m + j]);
        }
    }
    printf("\n");
    //Сама сортировка
    int er = 1; //Флаговые переменные
    int f = 1;
    int fl = 1;
    for (int k = 0; k < n; k++) { //Надо расставить все вершины
        er = 0;
        for (int j = 0; j < m; j++) { //Смотрим все столбы слева направо
            f = 1;
            fl = 1;
            for (int i = 0; i < n; i++) { //Смотрим числа в столбце
                if (a[i * m + j] == 1) { //Если есть входящее ребро (1)
                    fl = 0;
                    break;
                }
            }
            if (fl == 0) { // (1) - тогда переходим к другому столбцу
                continue;
            }

            for (int c = 0; c < k; c++) { //Проверяем, не находили ли эту вершину раньше
                if (b[c] == j + 1) {
                    f = 0;
                    break;
                }
            }
            if (f == 0) { //Если находили, переходим к другому столбцу
                continue;
            }
            //Нашли новую вершину
            er = 1; //Обновляем флаговую переменную
            b[k] = j + 1; //Записываем вершину в ответ
            for (int t = 0; t < n; t++) { //Убираем все исходящие от неё рёбра
                a[j * m + t] = 0;
            }
            break; //Нашли вершину, начинаем опять с первого столбца
        }
        if (er == 0) { //Если ни один столбец не подошёл
            break;
        }
    }
    //Вывод ответа
    if (er == 1) {
        for (int i = 0; i < n; i++) {
            printf("%d ", b[i]);
        }
    } else {
        printf("HEBO3MO}|{HO");
    }
    //Освобождаем память
    free(a);
    free(b);
    return 0;
}
