#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mergeSort.h"
#include "sm_sort_euclid_dist.h"
#include "sm_gnrt_3D_vecs.h"
#include "sm_4_star_main.h"
#include "sm_4_star_circulate.h"

int main()
{
    // inputs/constants---------------------------------------
    int N_i, N_uis, N_max, N_th, N_is, N_gc, N_circ = 0;
    int sm_K_vec_arr[N_gc][3];
    double epsilon, q, m, foc;
    double sm_sorted_UIS[N_i][3];
    double sm_3D_vecs[N_i][4];
    int sm_IS[N_uis];
    memset(sm_IS, -1, sizeof(sm_IS[0]) * N_gc);

    //--------------------------------------------------------

    scanf("%d", &N_i);
    scanf("%lf", &foc);

    // taking inputs of x,y coordinates and FEIDs-------------------------------------------------------------

    double UIS[N_i][3]; //2D array for storing (x,y) coordinates and star IDs of unidentified stars
    double temp[N_i];
    for (int i = 0; i < N_i; i++)
    {
        scanf("%lf", &UIS[i][0]); // x coordinate
        scanf("%lf", &UIS[i][1]); // y coordinate
        scanf("%lf", &UIS[i][2]); // FEID
        temp[i] = UIS[i][0] * UIS[i][0] + UIS[i][1] * UIS[i][1];
    }
    // -------------------------------------------------------------------------------------------------------

    mergeSort(temp, 0, N_i - 1);
    sm_sort_euclid_dist(UIS, temp, sm_sorted_UIS, N_i);
    sm_gnrt_3D_vecs(sm_3D_vecs, sm_sorted_UIS, foc, N_i);

    int circ_flag = 1;
    for (int i = 1; i <= N_max; i++)
    {
        if (!(N_uis >= 4 && N_is < N_th))
        {
            int N_match = 0;
            double four_stars[4][4];
            for (int j = 0; j < N_i; j++)
            {
                if (sm_3D_vecs[j][3] != -1)
                {
                    for (int k = 0; k < 4; k++)
                    {
                        four_stars[j][k] = sm_3D_vecs[j][k];
                    }
                }
            }
            
            // run 4 star matching

            sm_4_star(four_stars, sm_3D_vecs, sm_IS, sm_K_vec_arr, &N_match, N_i, N_gc, epsilon, q, m);

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
            break;
        }
    }
}
