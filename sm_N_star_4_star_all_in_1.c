#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void merge(double arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    double L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(double arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int main(){
    // inputs/constants---------------------------------------
    int N_i, N_uis, N_max, N_th, N_is, N_gc, N_circ = 0;
    int K[N_gc][3];
    double epsilon, q, m, foc;
    int IS[N_uis];
    memset(IS, -1, sizeof(IS[0]) * N_gc);
    
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

    // sorting them in ascending order------------------------------------------------------------------------

    mergeSort(temp,0,N_i-1);

    double sorted[N_i][3];

    for (int i = 0; i < N_i; i++)
    {
        for (int j = 0; j < N_i; j++)
        {
            if (abs(temp[i]-UIS[j][0]*UIS[j][0]-UIS[j][1]*UIS[j][1])<1e-10)
            {
                if (i!=0 && UIS[j][2]==sorted[i-1][2])
                {
                    continue;
                }
                sorted[i][0] = UIS[j][0];
                sorted[i][1] = UIS[j][1];
                sorted[i][2] = UIS[j][2];
            }
        }
    }
    // -------------------------------------------------------------------------------------------------------


    // generating 3d unit vectors-----------------------------------------------------------------------------
    
    double three_D_coords[N_i][4];
    for (int i = 0; i < N_i; i++)
    {
        double local = sqrt((sorted[i][0] / foc) * (sorted[i][0] / foc) + (sorted[i][1] / foc) * (sorted[i][1] / foc) + 1);
        three_D_coords[i][0] = (sorted[i][0] / foc) * local;
        three_D_coords[i][1] = (sorted[i][1] / foc) * local;
        three_D_coords[i][2] = local;
        three_D_coords[i][3] = sorted[i][2];
    }

    // -------------------------------------------------------------------------------------------------------
    int circ_flag = 1;
    for (int i = 1; i <= N_max; i++)
    {
        if (!(N_uis >= 4 && N_is < N_th))
        {
            int newid = 0; // boolean for checking whether the same star has been assigned a new value
            int N_match = 0;
            double four_stars[4][4];
            for (int j = 0; j < N_i; j++)
            {
                if (three_D_coords[j][3]!=-1)
                {
                    for (int k = 0; k < 4; k++)
                    {
                        four_stars[j][k] = three_D_coords[j][k];
                    }
                }
            }
            // make changes to acco

            // ====>> run 4 star matching
            double p[6];
            int checks[4][6] = {{1, 1, 1, 0, 0, 0},
                                {1, 0, 0, 1, 1, 0},
                                {0, 1, 0, 1, 0, 1},
                                {0, 0, 1, 0, 1, 1}};
            double SIM[N_gc][6];
            memset(SIM, 0, sizeof(SIM[0][0]) * N_gc * 6); // Initialising to zero
            for (int j = 0; j < 6; j++)
            {
                int k_top = ceil((cos(acos(p[j]) - epsilon) - q) / m);
                int k_bot = floor((cos(acos(p[j]) + epsilon) - q) / m);
                int k_start = K[k_bot][0] + 1;
                int k_end = K[k_top][0];
                
                for (int i = k_start; i <= k_bot; i++)
                {
                    SIM[K[i][1]][j] = 1;
                    SIM[K[i][2]][j] = 1;
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
                    if (IS[(int)four_stars[j][3]] == -1)
                    {
                        N_match++;
                        for (int k = 0; k < N_i; k++)
                        {
                            if (three_D_coords[k][3] == (int)four_stars[j][3])
                            {
                                three_D_coords[k][3] = -1;
                            }
                        }
                    }
                    IS[(int)four_stars[j][3]] = k;
                }
            }
            if (N_match==0)
            {
                // circulate unidentified star table
                int last = 0;
                for (int j = N_i-1; j >=0; j--)
                {
                    if (three_D_coords[j][3]!=-1)
                    {
                        last = j;
                        break;
                    }
                }
                double curr[4] = {three_D_coords[last][0], three_D_coords[last][1], three_D_coords[last][2], three_D_coords[last][3]};
                for (int j = 0; j <= last; j++)
                {
                    double var; //an auxiliary variable
                    for (int k = 0; k < N_i; k++)
                    {
                        if (three_D_coords[k][3] != -1)
                        {
                            for (int v = 0; v < 4; v++)
                            {
                                var = three_D_coords[k][v];
                                three_D_coords[k][v] = curr[v];
                                curr[v] = var;
                            }
                        }
                    }
                }
                N_circ++;
                if (N_circ>=2*N_i)
                {
                    break;
                }
            }
            else
            {
                // three_D_coords[];
                // N_is += N_match;
                // N_uis -= N_match;
            }
        }
        else
        {
            break;
        }
    }
}