#include<stdio.h>
#include<stdlib.h>

int compare(const void *a, const void *b)
{
    const int *x = (int *)a;
    const int *y = (int *)b;

    if (*x > *y)
        return 1;
    else if (*x < *y)
        return -1;

    return 0;
}

int main(){
    // inputs/constants---------------------------------------
    int N_i, N_uis, N_is, N_th, N_max, N_circ=0;
    double foc;
    //--------------------------------------------------------

    scanf("%d", &N_i);
    scanf("%lf", &foc);

    // taking inputs of x,y coordinates-----------------------------------------------------------------------

    double centroids[N_i][2]; //2D array for storing (x,y) coordinates
    double temp[N_i];
    for (int i = 0; i < N_i; i++)
    {
        scanf("%lf", &centroids[i][0]); // x coordinate
        scanf("%lf", &centroids[i][1]); // y coordinate
        temp[i] = centroids[i][0] * centroids[i][0] + centroids[i][1] * centroids[i][1];
    }
    // -------------------------------------------------------------------------------------------------------

    // sorting them in ascending order------------------------------------------------------------------------

    qsort(temp, N_i, sizeof(temp[0]), compare);
    double sorted[N_i][2];
    for (int i = 0; i < N_i; i++)
    {
        printf("%lf ", temp[i]);
    }
    printf("\n");
    for (int i = 0; i < N_i; i++)
    {
        for (int j = 0; j < N_i; j++)
        {
            if (abs(temp[i]-centroids[j][0]*centroids[j][0]-centroids[j][1]*centroids[j][1])<1e-5)
            {
                sorted[i][0] = centroids[j][0];
                sorted[i][1] = centroids[j][1];
            }
        }
    }
    for (int i = 0; i < N_i; i++)
    {
        printf("%lf ", sorted[i][0]);
        printf("%lf\n", sorted[i][1]);
    }
    // -------------------------------------------------------------------------------------------------------
    // generating 3d unit vectors-----------------------------------------------------------------------------
    
    double three_D_coords[N_i][3];
    for (int i = 0; i < N_i; i++)
    {
        double local = sqrt((sorted[i][0] / foc) * (sorted[i][0] / foc) + (sorted[i][1] / foc) * (sorted[i][1] / foc) + 1);
        three_D_coords[i][0] = (sorted[i][0] / foc) * local;
        three_D_coords[i][1] = (sorted[i][1] / foc) * local;
        three_D_coords[i][2] = local;
    }

    // -------------------------------------------------------------------------------------------------------
    int i = 1;
    int circ_flag = 1;
    while (i <= N_max)
    {
        if (!(N_uis >= 4 && N_is < N_th))
        {
            int N_match;
            double four_stars[4][3];


            // ====>> run 4 star matching



            if (N_match==0)
            {
                // circulate unidentified star table
                int siz = 0; // put appropriate value/func of current array size of unidentified stars
                double curr[3] = {three_D_coords[siz-1][0], three_D_coords[siz-1][1], three_D_coords[siz-1][2]};
                for (int i = 0; i < siz; i++)
                {
                    int var; //an auxiliary variable
                    var = three_D_coords[i][0];
                    three_D_coords[i][0] = curr[0];
                    curr[0] = var;
                    var = three_D_coords[i][1];
                    three_D_coords[i][1] = curr[1];
                    curr[1] = var;
                    var = three_D_coords[i][2];
                    three_D_coords[i][2] = curr[2];
                    curr[2] = var;
                }
                N_circ++;
                if (N_circ<=2*N_i)
                {
                    break;
                }
                else
                {
                    i++;
                }
                
            }
            else
            {
                
            }
            
           
        }
        else
        {
            break;
        }
    }
}