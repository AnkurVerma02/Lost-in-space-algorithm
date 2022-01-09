#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> /* memset */
// #include <unistd.h>

#include "newsort.h"
#include "sm_sort_euclid_dist.h"
#include "sm_gnrt_3D_vecs.h"
#include "sm_4_star_main.h"
#include "sm_4_star_circulate.h"
// 5060
int sm_K_vec_arr[188808][3];

void bubbleSort(double arr[][3], int n)
{
    int i, j;
    double temp[3];
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j][1] * arr[j][1] + arr[j][2] * arr[j][2] > arr[j+1][1] * arr[j+1][1] + arr[j+1][2] * arr[j+1][2])
            {
                // swap the elements
                temp[0] = arr[j][0];
                temp[1] = arr[j][1];
                temp[2] = arr[j][2];
                arr[j][0] = arr[j + 1][0];
                arr[j][1] = arr[j + 1][1];
                arr[j][2] = arr[j + 1][2];
                arr[j + 1][0] = temp[0];
                arr[j + 1][1] = temp[1];
                arr[j + 1][2] = temp[2];
            }
        }
    }
}

int main()
{
    // inputs/constants---------------------------------------

    int N_i, N_uis, N_max, N_th, N_is, N_gc, N_circ = 0;
    double epsilon, q, m, foc, y_max, y_min, delta;

    // -------------------------------------------------------
    delta = 5e-4;
    N_gc = 5060;
    N_i = 49;
    N_uis = 49;
    N_max = N_i-1;
    N_th = 10;
    N_is = 0;
    y_max = 0.999999999992621;
    y_min = 0.973988966620749;
    epsilon = 2.22e-15;
    foc = 0.025;

    //--------------------------------------------------------

    FILE *file;
    file = fopen("kvec.txt", "r");
    for (int i = 0; i < N_gc; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int tempp;
            fscanf(file, "%d", &tempp);
            sm_K_vec_arr[i][j] = tempp;
        }
    }
    fclose(file);
    
    // double sm_sorted_UIS[N_i][3];
    double sm_3D_vecs[N_i][4];
    int sm_IS[5060][2];
    for (int i = 0; i < 5060; i++)
    {
        sm_IS[i][0] = -1;
        sm_IS[i][1] = -1;
    }

    // printf("%d %d\n",sm_IS[0],sm_IS[4]);
    //--------------------------------------------------------
    
    m = (y_max - y_min + 2 * epsilon) / (N_gc - 1);
    q = y_min - m - epsilon;

    // -------------------------------------------------------

    // scanf("%d", &N_i);
    // scanf("%lf", &foc);

    // taking inputs of x,y coordinates and FEIDs-------------------------------------------------------------

    double UIS[N_i][3]; //2D array for storing (x,y) coordinates and star IDs of unidentified stars
    // double temp[N_i];
    // for (int i = 0; i < N_i; i++)
    // {
    //     scanf("%lf ", &UIS[i][0]); // FEID
    //     scanf("%lf ", &UIS[i][1]); // x coordinate
    //     scanf("%lf ", &UIS[i][2]); // y coordinate
    //     temp[i] = UIS[i][1] * UIS[i][1] + UIS[i][2] * UIS[i][2];
    // }
    FILE *file2;
    file2 = fopen("req.txt", "r");
    for (int i = 0; i < N_i; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            double tempp;
            fscanf(file, "%lf", &tempp);
            UIS[i][j] = tempp;
        }
        // temp[i] = UIS[i][1] * UIS[i][1] + UIS[i][2] * UIS[i][2];
        // printf("%d %.24lf %.24lf\n", (int)UIS[i][0], UIS[i][1], UIS[i][2]);
    }
    // printf("%d %.12lf %.12lf", (int)UIS[1][0], UIS[1][1], UIS[1][2]);
    fclose(file2);
    // -------------------------------------------------------------------------------------------------------

    bubbleSort(UIS, N_i);
    // for (int i = 0; i < N_i; i++)
    // {
    //     printf("%lf %lf %lf \n", UIS[i][0], UIS[i][1], UIS[i][2]);
    // }
    sm_gnrt_3D_vec(sm_3D_vecs, UIS, foc, N_i);
    // for (int i = 0; i < N_i; i++)
    // {
    //     printf("%lf %lf %lf %lf\n", sm_3D_vecs[i][0], sm_3D_vecs[i][1], sm_3D_vecs[i][2], sm_3D_vecs[i][3]);
    // }
    int circ_flag = 1;
    for (int i = 1; i <= N_max; i++)
    {
        if (N_uis >= 4 && N_is < N_th)
        {
            int N_match = 0;
            double four_stars[4][4];;
            for (int countt = 0, j = 0; j < N_i && countt < 4; j++)
            {
                if ((int)sm_3D_vecs[j][0] != -1)
                {
                    for (int k = 0; k < 4; k++)
                    {
                        four_stars[j][k] = sm_3D_vecs[j][k];
                    }
                    countt++;
                }
            }
            // run 4 star matching

            sm_4_star(four_stars, sm_3D_vecs, sm_IS, sm_K_vec_arr, &N_match, N_i, N_gc, delta, q, m);
            if (N_match == 0)
            {
                // circulate
                sm_4_star_circulate(sm_3D_vecs, &N_circ, N_i);
                if (N_circ >= 2 * N_i)
                {
                    break;
                }
            }
        }
        else
        {
            // printf("broken\n");
            break;
        }
    }
    for (int i = 0; i < 5060; i++)
    {
        if (sm_IS[i][0]!=-1)
        {
            printf("%d  %d  %d\n",i,sm_IS[i][0],sm_IS[i][1]);
        }
    }
}
