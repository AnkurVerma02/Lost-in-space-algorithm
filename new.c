#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// #include "mergeSort.h"
#include "newsort.h"
double sm_K_vec_arr[2][3];

void print1(double arr[]){
    // arr[0][0] += 100;
    for (int i = 0; i < 6; i++)
    {
        printf("%lf ", arr[i]);
    }
}
void print2(double arr[][3])
{
    arr[0][0] += 100;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%lf ", arr[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    
    // FILE *file = fopen("req.txt", "r");
    // double tempp;
    // for (int i = 0; i < 2; i++)
    // {
    //     for (int j = 0; j < 3; j++)
    //     {
    //         fscanf(file, "%lf", &tempp);
    //         sm_K_vec_arr[i][j] = tempp;
    //         printf("%d\n", (int)sm_K_vec_arr[i][0]);
    //     }
    // }
    // double t = 3.98;
    // printf("%d\n", (int)t);
    // fclose(file);
    // sm_K_vec_arr[0][0] += 2;
    // printf("%d", sm_K_vec_arr[0][0]);
    double arr1[6] = {5, 8, 1, 2, 4, 0};
    double arr[4][3] = {{5, 2, 1},
                     {10, 10, 2},
                     {1, 1, 1},
                     {4, 5, 1}};
    Sort(arr, 0, 3);
    print2(arr);
    // print2(arr);
}