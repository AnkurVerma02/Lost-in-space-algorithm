#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void sm_4_star (double four_stars[][4], double sm_3D_vecs[][4], double sm_IS[], int sm_K_vec_arr[][3], int *N_match, int N_i, int N_gc, double epsilon, double q, double m)
{
    double p[6];
    int checks[4][6] = {{1, 1, 1, 0, 0, 0},
                        {1, 0, 0, 1, 1, 0},
                        {0, 1, 0, 1, 0, 1},
                        {0, 0, 1, 0, 1, 1}};

    double SIM[N_gc][6];
    memset(SIM, 0, sizeof(SIM[0][0]) * N_gc * 6);
    for (int j = 0; j < 6; j++)
    {
        int k_top = ceil((cos(acos(p[j]) - epsilon) - q) / m);
        int k_bot = floor((cos(acos(p[j]) + epsilon) - q) / m);
        int k_start = sm_K_vec_arr[k_bot][0] + 1;
        int k_end = sm_K_vec_arr[k_top][0];

        for (int i = k_start; i <= k_bot; i++)
        {
            SIM[sm_K_vec_arr[i][1]][j] = 1;
            SIM[sm_K_vec_arr[i][2]][j] = 1;
        }
    }
    for (int j = 0; j < 4; j++)
    {
        int matched_rows = 0;
        int k = 0;
        for (; k < N_gc; k++)
        {
            if (SIM[k][0] == checks[j][0] && SIM[k][1] == checks[j][1] && SIM[k][2] == checks[j][2] && SIM[k][3] == checks[j][3] && SIM[k][4] == checks[j][4] && SIM[k][5] == checks[j][5])
            {
                matched_rows++;
            }
        }
        if (matched_rows == 1)
        {
            if (sm_IS[(int)four_stars[j][3]] == -1)
            {
                N_match++;
                for (int k = 0; k < N_i; k++)
                {
                    if (sm_3D_vecs[k][3] == (int)four_stars[j][3])
                    {
                        sm_3D_vecs[k][3] = -1;
                    }
                }
            }
            sm_IS[(int)four_stars[j][3]] = k;
        }
    }
}
