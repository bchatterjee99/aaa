#include <stdio.h>

int n;
long A[200][200];
long B[200][200];

void input_matrix(long A[][200], const char* file)
{
    FILE* fp = fopen(file, "r");
    fscanf(fp, "%d", &n);
    int max_digits = 0;
    long tmp;

    // A
    for(int i=0; i<n; i++)
    {
	for(int j=0; j<n; j++)
	{
	    fscanf(fp, "%ld", &tmp);
	    A[i][j] = tmp;
	}
    }
}

void show_matrix(long M[][200], int n, int m)
{
    for(int i=0; i<n; i++)
    {
	for(int j=0; j<m; j++)
	{
	    printf("%ld", M[i][j]);
	    printf(" ");
	}
	printf("\n");
    }
}

void mult_vector(long A[][200], long b[], long c[], int n)
{
    for(int i=0; i<n; i++)
    {
	c[i] = 0;
	for(int j=0; j<n; j++)
	    c[i] = c[i] + A[i][j] * b[j];
    }
}

// A-inverse = 1/129792 * B
int main()
{
    input_matrix(A, "matrix.txt");
    input_matrix(B, "z-A-inverse.txt");

    long fntr[] = {0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0};

    long c[200];
    long d[200];

    mult_vector(A, fntr, c, n);
    printf("c = ");
    for(int i=0; i<n; i++) printf("%ld ", c[i]);
    printf("\n\n");


    mult_vector(B, c, d, n);
    printf("d = ");
    for(int i=0; i<n; i++) printf("%ld ", d[i] / 129792);
    printf("\n\n");


    printf("\n\n thikache\n\n");
    return 0;
}
