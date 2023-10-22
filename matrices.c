#include <stdio.h>
#include <stdlib.h>

#define STRING_LENGTH
typedef char String[STRING_LENGTH];
//-----------------------------------------------------------------------------
double* input_matrix(int* rows, int* columns, String name){
	
	double *m1;
	int i, j;	

	printf("Enter # of rows for %s: ", name);
	scanf("%d", rows);
	printf("Enter # of columns for %s: ", name);
	scanf("%d", columns);
	
	m1 = (double*)malloc((*rows) * (*columns) * sizeof(double));
	if (m1 == NULL)
        	return NULL;
	
	for(i = 0; i < *rows; i++){
		for(j = 0; j < *columns; j++){
			printf("Enter entry %d (Row Major Ordering): ", 
					i * (*columns) + j + 1);
				scanf("%lf", &m1[i * (*columns) + j]); 	
		}
	}

	return m1;
}
//-----------------------------------------------------------------------------
int matrix_multiply(double* m1, int m1_rows, int m1_columns, double* m2,
		int m2_rows, int m2_columns, double* m3){
	
	int i, j, k;

	if(m1_columns == m2_rows){
	    for(i = 0; i < m1_rows; i++){
		for(j = 0; j < m2_columns; j++){
		    m3[i * m2_columns + j] = 0;

		    for(k = 0; k < m1_columns; k++){
			m3[i * m2_columns + j] += m1[i * m1_columns + k] 
			    * m2[k * m2_columns + j];
		    }
		}
	    }
		
	    return 1;
	}

	return 0;
}
//-----------------------------------------------------------------------------
void output_matrix(double* matrix, int rows, int columns){
	
	int i, j;

	for(i = 0; i < rows; i++){
		for(j = 0; j < columns; j++){
			printf("%.2lf ", matrix[i * columns + j]); 
		}

		printf("\n");
	}
}
//-----------------------------------------------------------------------------
int main() {

    double *m1,*m2,*m3;
    int m1_rows,m1_columns,m2_rows,m2_columns;

    if (((m1 = input_matrix(&m1_rows,&m1_columns,"Matrix 1")) != NULL) &&
((m2 = input_matrix(&m2_rows,&m2_columns,"Matrix 2")) != NULL) &&
((m3 = malloc(m1_rows*m2_columns*sizeof(double))) != NULL)) {
        printf("Matrix 1\n");
        output_matrix(m1,m1_rows,m1_columns);
        printf("Matrix 2\n");
        output_matrix(m2,m2_rows,m2_columns);
        if (matrix_multiply(m1,m1_rows,m1_columns,m2,m2_rows,m2_columns,m3)) {
            printf("Product\n");
            output_matrix(m3,m1_rows,m2_columns);
            free(m1);
            free(m2);
            free(m3);
            return(0);
        } else {
            printf("Error in dimensions\n");
            free(m1);
            free(m2);
            free(m3);
            return(-1);
        }
    } else {
        free(m1);
        free(m2);
        free(m3);
        printf("Error allocating memory\n");
        return(-2);
    }
}

