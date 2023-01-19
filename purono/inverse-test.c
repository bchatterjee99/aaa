#include <stdio.h>

long A[200][200];
long B[200][200];
long C[200][200];
int n;

void input_matrix(long D[][200], const char* file, int* n)
{
    FILE* fp = fopen(file, "r");
    fscanf(fp, "%d", n);
    int max_digits = 0;
    long tmp;

    // A
    for(int i=0; i<*n; i++)
    {
	for(int j=0; j<*n; j++)
	{
	    fscanf(fp, "%ld", &tmp);
	    D[i][j] = tmp;
	}
    }
    fclose(fp);
}


// C = A * B
void mult(long A[][200], long B[][200], long C[][200], int n)
{
    for(int i=0; i<n; i++)
    {
	for(int j=0; j<n; j++)
	{
	    C[i][j] = 0;
	    for(int k=0; k<n; k++)
		C[i][j] = C[i][j] + A[i][k] * B[k][j];
	    
	}
    }
}

void show_matrix(long D[][200], int n)
{
    for(int i=0; i<n; i++)
    {
	for(int j=0; j<n; j++)
	    printf("%ld ", D[i][j]);
	printf("\n");
    }
}

int main()
{
    input_matrix(A, "A.txt", &n);
    input_matrix(B, "B.txt", &n);

    mult(A, B, C, n);


    /* printf("A:\n"); */
    /* show_matrix(A, n); */
    /* printf("B:\n"); */
    /* show_matrix(B, n); */


    printf("AB: ");
    show_matrix(C, n);
    printf("\n\n");

    return 0;
}
