#include <stdio.h>
#define ROWS  4
#define COLS  4

// author: pasali

void substituting(double mat[ROWS][COLS], int x, int y )
{
    int i;
    for(i = 0; i < COLS; i++){
        if (mat[i][y] != 0){
            printf("L%d and L%d are substituting...\n",x,i);
            printf("-------------------------\n");
            double temp[COLS];
            int k;
            for (k=0; k<COLS; k++) temp[k] = mat[i][k];
            for (k = 0;k < COLS; k++) mat[i][k] = mat[x][k];
            for (k = 0;k < COLS; k++) mat[x][k] = temp[k];
            break;
        }
    }
}

void det(double mat[ROWS][COLS])
{
    gauss(mat);
    int i,j;
    double result = 1.0;
    for(i=0; i<ROWS; i++) {
        result *= mat[i][i];
    }
    printf("Determinant = %.f\n", result);
}


int gauss(double mat[ROWS][COLS])
{
    int i, k, j;
 
    for ( i=0; i < ROWS-1; i++){
        for(k = i+1; k < COLS; k++){
           if(mat[i][i] == 0){ 
                substituting(mat,i,i);
                k--;
           }
           else{
                float kat = (float) mat[k][i] / mat[i][i];
	        //printf("L%d <---- L%d - (%.1f) * L%d\n-------------------------\n", k+1, k+1, kat, i+1);
	        for(j = 0; j < COLS ; j++){
                    mat[k][j] = mat[k][j] - kat * mat[i][j];
                }
           }
        }
    }
}

int main()
{

    double  mat[ROWS][COLS] = {{1, 0, -2,3 },
                               {2,3, -4, 1},
                               {3, 0, -2, 4},
                               {0, 1, 4, 5},
				           };
    det(mat);
    return 0;
}
