#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double SIM[5060][6];

void sm_4_star (double four_stars[][4], double sm_3D_vecs[][4], int sm_IS[], int sm_K_vec_arr[][3], int *N_match, int N_i, int N_gc, double delta, double q, double m)
{
    double p[6];
    int ct = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = i+1; j < 4; j++)
        {
            p[ct] = four_stars[i][1] * four_stars[j][1] + four_stars[i][2] * four_stars[j][2] + four_stars[i][3] * four_stars[j][3];
            // printf("p %.15lf\n", p[ct]);
            ct++;
        }    
    }
    int checks[4][6] = {{1, 1, 1, 0, 0, 0},
                        {1, 0, 0, 1, 1, 0},
                        {0, 1, 0, 1, 0, 1},
                        {0, 0, 1, 0, 1, 1}};

    for (int j = 0; j < 6; j++)
    {
        int k_top = ceil((cos(acos(p[j]) - delta) - q) / m);
        int k_bot = floor((cos(acos(p[j]) + delta) - q) / m);
        printf("k_top = %d, k_bot=%d\n", k_top, k_bot);
        if (k_top <0 || k_bot >= 188808)
        {
            printf("bad values : k_bot = %d, k_top = %d\n", k_bot, k_top);
            return;
        }
        else
        {
            if (k_top>188808)
            {
                k_top = 188807;
            }
            if (k_bot<0)
            {
                k_bot = 0;
            }
            
            int k_start = sm_K_vec_arr[k_bot][0] + 1;
            int k_end = sm_K_vec_arr[k_top][0];
            // printf("k_start = %d, k_end = %d\n", k_start, k_end);
            for (int i = k_start; i <= k_end; i++)
            {
                SIM[sm_K_vec_arr[i][1]][j] = 1;
                SIM[sm_K_vec_arr[i][2]][j] = 1;
            }
        }
    }
    printf("ff\n");
    for (int j = 0; j < 4; j++)
    {
        int matched_rows = 0;
        int k = 0;
        for (; k < N_gc; k++)
        {
            if (SIM[k][0] == checks[j][0]
             && SIM[k][1] == checks[j][1]
             && SIM[k][2] == checks[j][2]
             && SIM[k][3] == checks[j][3] 
             && SIM[k][4] == checks[j][4] 
             && SIM[k][5] == checks[j][5])
            {
                matched_rows++;
                printf("matched\n");
            }
        }
        if (matched_rows == 1)
        {
            printf("1\n");
            if (sm_IS[(int)four_stars[j][0]] == -1)
            {
                printf("2\n");
                N_match++;
                for (int k = 0; k < N_i; k++)
                {
                    // printf("3\n");
                    if ((int)sm_3D_vecs[k][0] == (int)four_stars[j][0])
                    {
                        printf("44\n");
                        sm_3D_vecs[k][0] = -1;
                    }
                }
            }
            sm_IS[(int)four_stars[j][0]] = k;
        }
    }
}