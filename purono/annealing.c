#include <stdio.h>

long C[200][200];
long D[200][200];
long Constraint[200][200];
long b[200], c[200];
int n;
int C_n;
int C_m;
long E[200][200];

void input_matrix(long A[][200], const char* file, int* n)
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
	    A[i][j] = tmp;
	}
    }
    fclose(fp);
}


void input_constraint(long A[][200], long b[], long c[], const char* file, int* C_n, int* C_m)
{
    FILE* fp = fopen(file, "r");

    fscanf(fp, "%d", C_n);
    fscanf(fp, "%d", C_m);

    for(int i=0; i<*C_n; i++)
    {
	for(int j=0; j<*C_m; j++)
	    fscanf(fp, "%d", &A[i][j]);
    }

    for(int i=0; i<*C_n; i++)
	fscanf(fp, "%d", &b[i]);


    for(int i=0; i<*C_n; i++)
	fscanf(fp, "%d", &c[i]);
}


void show_matrix(long A[][200], int n, char* str)
{
    printf("%s:\n", str);
    for(int i=0; i<n; i++)
    {
	for(int j=0; j<n; j++)
	    printf("%d ", A[i][j]);
	printf("\n");
    }
    printf("\n\n");
}

void mult_matrix(long A[][200], long B[][200], long C[][200], int n)
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
void mult_vector(long A[][200], long B[][200], long C[][200], int n)
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


void check(long f[], long Constraint[][200], long b[], long c[], int C_n, int C_m)
{
    printf("Check:\n");
    int flag = 0;
    for(int i=0; i<C_n; i++)
    {
	long tmp = 0;
	for(int j=0; j<C_m; j++)
	    tmp = tmp + f[j] * Constraint[i][j];
	if(tmp < b[i] || tmp > c[i])
	{
	    printf("constraint %d failed\n", i);
	    printf("b = %ld, tmp = %ld, c = %ld\n\n", b[i], tmp, c[i]);
	    flag = 1;
	}
    }
    if(flag == 0) printf("passed\n");
    else printf("failed\n");
    printf("\n\n");
}


void test()
{
    long f1[] = {0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0};

    check(f1, Constraint, b, c, C_n, C_m);
}

// C-inverse = 1/16512 * D
int main()
{
    input_matrix(C, "C.txt", &n);
    input_matrix(D, "D.txt", &n);
    input_constraint(Constraint, b, c, "constraint115.txt", &C_n, &C_m);

    /* mult_matrix(C, D, E, n); */
    /* show_matrix(E, n, "E"); */
    test();

    printf("\n\n thikache\n\n");
    return 0;
}
