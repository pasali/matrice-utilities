#include <stdio.h>
#define ROWS  4
#define COLS  4

// author: pasali

void substituting(double denk[ROWS][COLS],double sag[ROWS], int x, int y )
{
    int i;
    for(i = 0; i < COLS; i++)
    {
        if (denk[i][y] != 0)
        {
            printf("L%d and L%d are substituting...\n",x,i);
            printf("-------------------------\n");
            double temp[COLS];
            double tut;
            tut = sag[i];
            sag[i] = sag[x];
            sag[x] = tut;
            int k;
            for (k=0; k<COLS; k++) temp[k] = denk[i][k];
            for (k = 0;k < COLS; k++) denk[i][k] = denk[x][k];
            for (k = 0;k < COLS; k++) denk[x][k] = temp[k];
            break;
        }
    }
}

void print_matrice(double denk[ROWS][COLS], double sag[ROWS])
{
    int i,j;
    printf("\n");
    for(i=0; i<ROWS; i++) {
        for (j=0; j<COLS; j++)
            printf("%.1f  ", denk[i][j]);
        printf("    | %.1f\n",sag[i]);
    }
    printf("-------------------------\n");
}


int gauss(double denk[ROWS][COLS], double sag[ROWS])
{
    int i, k, j;
    print_matrice(denk,sag);
    for ( i=0; i < ROWS-1; i++){
        for(k = i+1; k < COLS; k++){
           if(denk[i][i] == 0){ 
                substituting(denk,sag,i,i);
                k--;
           }
           else{
                float kat = (float) denk[k][i] / denk[i][i];
                sag[k] = sag[k] - kat * sag[i];
	            printf("L%d <---- L%d - (%.1f) * L%d\n-------------------------\n", k+1, k+1, kat, i+1);
	            for(j = 0; j < COLS ; j++){
                    denk[k][j] = denk[k][j] - kat * denk[i][j];
                }
           }
	    print_matrice(denk,sag);
        }
    }
}

void solving(double denk[ROWS][COLS],double sag[ROWS])
{
    double results[ROWS];
    int i,j;
    for(i = ROWS -1; i >= 0; i--)
    {
        if(denk[i][i] == 0)
        {
            printf("Can't solve.\n");
            break;
        }
        else
        {
        
            float sum = 0;
            for(j = i + 1 ; j < ROWS; j++)
            {
                sum += denk[i][j] * results[j];
            }
            results[i] = (float) (sag[i]- sum) / denk[i][i];
        }
    }
    
    for(i = 0; i < ROWS;i++)
        printf("x%d ==>  %.1f\n",i, results[i]); 
}



int main()
{

    double  equations[ROWS][COLS] = {{1, 0, -2,3 },
                                      {2,3, -4, 1},
                                      {3, 0, -2, 4},
                                      {0, 1, 4, 5},
				                      };
    double rightside[ROWS] = {4, 6, 0, 8};
    gauss(equations, rightside);
    solving(equations, rightside);

}
