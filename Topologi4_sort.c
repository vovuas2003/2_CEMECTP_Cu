#include <stdio.h>
#include <stdlib.h>

int main() {
    //���� ������
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
    //���� ����������
    int er = 1; //�������� ����������
    int f = 1;
    int fl = 1;
    for (int k = 0; k < n; k++) { //���� ���������� ��� �������
        er = 0;
        for (int j = 0; j < m; j++) { //������� ��� ������ ����� �������
            f = 1;
            fl = 1;
            for (int i = 0; i < n; i++) { //������� ����� � �������
                if (a[i * m + j] == 1) { //���� ���� �������� ����� (1)
                    fl = 0;
                    break;
                }
            }
            if (fl == 0) { // (1) - ����� ��������� � ������� �������
                continue;
            }

            for (int c = 0; c < k; c++) { //���������, �� �������� �� ��� ������� ������
                if (b[c] == j + 1) {
                    f = 0;
                    break;
                }
            }
            if (f == 0) { //���� ��������, ��������� � ������� �������
                continue;
            }
            //����� ����� �������
            er = 1; //��������� �������� ����������
            b[k] = j + 1; //���������� ������� � �����
            for (int t = 0; t < n; t++) { //������� ��� ��������� �� �� ����
                a[j * m + t] = 0;
            }
            break; //����� �������, �������� ����� � ������� �������
        }
        if (er == 0) { //���� �� ���� ������� �� �������
            break;
        }
    }
    //����� ������
    if (er == 1) {
        for (int i = 0; i < n; i++) {
            printf("%d ", b[i]);
        }
    } else {
        printf("HEBO3MO}|{HO");
    }
    //����������� ������
    free(a);
    free(b);
    return 0;
}
