#include <stdio.h>
#include <stdlib.h>

int n;
long A[200][200];
long B[200][200];

long Constraint[200][200];
int C_n, C_m;
long b[200];
long c[200];

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

void input_constraint(long A[][200], const char* file, int* C_n, int* C_m)
{
    FILE* fp = fopen(file, "r");

    fscanf(fp, "%d", C_n);
    fscanf(fp, "%d", C_m);

    for(int i=0; i<*C_n; i++)
    {
	for(int j=0; j<*C_m; j++)
	    fscanf(fp, "%d", &Constraint[i][j]);
    }

    for(int i=0; i<*C_m; i++)
	fscanf(fp, "%d", &b[i]);


    for(int i=0; i<*C_m; i++)
	fscanf(fp, "%d", &c[i]);
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


void check(long f[], const char * str)
{
    printf("check %s:\n", str);
    int flag = 0;
    for(int i=0; i<C_n; i++)
    {
	long tmp = 0;
	for(int j=0; j<C_m; j++)
	    tmp = tmp + f[j] * Constraint[i][j];
	if(tmp < b[i] || tmp > c[i])
	{
	    printf("constraint %d failed\n", i);
	    flag = 1;
	}
    }
    if(flag == 0) printf("passed\n");
    printf("\n\n");
}


void show_vec(long* a, int n)
{
    for(int i=0; i<n; i++)
	printf("%ld ", a[i]);
}

void show_fvec(double* a, int n)
{
    for(int i=0; i<n; i++)
	printf("%lf ", a[i]);
}

int main()
{
    input_matrix(A, "A.txt", &n);
    input_matrix(B, "B.txt", &n);
    // A-inverse = 1/129792 * B
    input_constraint(Constraint, "constraint112.txt", &C_n, &C_m);

    long b[] = {0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0};

    long c[200];
    long d[200];
    double e[200];
    double f[200];
    long g[200];

    printf("b = \n");
    show_vec(b, n);
    printf("\n\n");

    check(b, "b");

    // c = A*b
    mult_vector(A, b, c, n);
    printf("c = A*b:\n");
    show_vec(c, n);
    printf("\n\n");

    // check B * c
    mult_vector(B, c, d, n);
    printf("d = B * c:    (B = 129292 * A-inverse)\n");
    show_vec(d, n);
    printf("\n\n");

    // e = d / 129292
    for(int i=0; i<n; i++) e[i] = (double)d[i] / (double)129292.0;
    printf("e = d / 129292.0:\n");
    show_fvec(e, n);
    printf("\n\n");

    // disturb c
    c[10] += 1;
    c[25] -= 1;
    c[75] -= 10;

    // f = (1/129292) B * c
    mult_vector(B, c, d, n);
    for(int i=0; i<n; i++) f[i] = (double)d[i] / (double)129292;
    printf("f = (1/129292)B * c':   (c' = disturbed c)\n");
    show_fvec(f, n);
    printf("\n\n");

    // g = round f
    for(int i=0; i<n; i++)
    {
	if(abs(f[i] - (double)0.0) <= abs(f[i] - (double)1.0))
	    g[i] = 0;
	else
	    g[i] = 1;
    }
    printf("g = round(f):\n");
    show_vec(g, n);
    printf("\n\n");

    check(g, "g");

    printf("\n\n thikache\n\n");
    return 0;
}
