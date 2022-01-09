#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void sm_sort_euclid_dist(double UIS[][3], double temp[],double sm_sorted_UIS[][3], int N_i)
{
    for (int i = 0; i < N_i; i++)
    {
        for (int j = 0; j < N_i; j++)
        {
            if (abs(temp[i] - UIS[j][1] * UIS[j][1] - UIS[j][2] * UIS[j][2]) < 1e-16)
            {
                if (i != 0 && (int)UIS[j][0] == (int)sm_sorted_UIS[i - 1][0])
                {
                    continue;
                }
                else
                {
                    sm_sorted_UIS[i][0] = UIS[j][0];
                    sm_sorted_UIS[i][1] = UIS[j][1];
                    sm_sorted_UIS[i][2] = UIS[j][2];
                    break;
                }
                
            }
        }
    }
}