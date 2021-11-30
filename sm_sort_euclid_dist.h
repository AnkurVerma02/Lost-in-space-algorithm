#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void sm_sort_euclid_dist(double UIS[][3], double temp[],double sorted[][3], int N_i)
{
    for (int i = 0; i < N_i; i++)
    {
        for (int j = 0; j < N_i; j++)
        {
            if (abs(temp[i] - UIS[j][0] * UIS[j][0] - UIS[j][1] * UIS[j][1]) < 1e-10)
            {
                if (i != 0 && UIS[j][2] == sorted[i - 1][2])
                {
                    continue;
                }
                sorted[i][0] = UIS[j][0];
                sorted[i][1] = UIS[j][1];
                sorted[i][2] = UIS[j][2];
            }
        }
    }
}