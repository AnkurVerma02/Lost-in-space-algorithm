#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print(double arr[][3])
{
    // arr[0][0] += 100;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%lf ", arr[i][j]);
        }
        printf("\n");
    }
}

void merge(double arr[][3], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    double L[n1][3], R[n2][3];

    for (i = 0; i < n1; i++)
        L[i][0] = arr[l + i][0];
        L[i][1] = arr[l + i][1];
        L[i][2] = arr[l + i][2];

    for (j = 0; j < n2; j++)
        R[j][0] = arr[m + 1 + j][0];
        R[j][1] = arr[m + 1 + j][1];
        R[j][2] = arr[m + 1 + j][2];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (sqrt(abs(L[i][1] * L[i][1] + L[i][2] * L[i][2])) < sqrt(abs(R[j][1] * R[j][1] + R[j][2] * R[j][2])))
        {
            arr[k][0] = L[i][0];
            arr[k][1] = L[i][1];
            arr[k][2] = L[i][2];
            i++;
        }
        else
        {
            arr[k][0] = R[j][0];
            arr[k][1] = R[j][1];
            arr[k][2] = R[j][2];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k][0] = L[i][0];
        arr[k][1] = L[i][1];
        arr[k][2] = L[i][2];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k][0] = R[j][0];
        arr[k][1] = R[j][1];
        arr[k][2] = R[j][2];
        j++;
        k++;
    }
}
void Sort(double arr[][3], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        Sort(arr, l, m);
        Sort(arr, m + 1, r);

        merge(arr, l, m, r);
        print(arr);
    }
}