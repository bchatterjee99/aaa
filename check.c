#include <stdio.h>

long Constraint112[200][200];
int C112_n, C112_m;
long b112[200];
long c112[200];


long Constraint115[200][200];
int C115_n, C115_m;
long b115[200];
long c115[200];

void input_constraint1(long A[][200], long b[], long c[], const char* file, int* C_n, int* C_m)
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

void check1(long f[], const char * str)
{
    printf("check1 %s:\n", str);
    int flag = 0;
    for(int i=0; i<C112_n; i++)
    {
	long tmp = 0;
	for(int j=0; j<C112_m; j++)
	    tmp = tmp + f[j] * Constraint112[i][j];
	if(tmp < b112[i] || tmp > c112[i])
	{
	    printf("constraint %d failed\n", i);
	    flag = 1;
	}
    }
    if(flag == 0) printf("passed\n");
    printf("\n\n");
}

void check2(long f[], const char * str)
{
    printf("check2 %s:\n", str);
    int flag = 0;
    for(int i=0; i<C115_n; i++)
    {
	long tmp = 0;
	for(int j=0; j<C115_m; j++)
	    tmp = tmp + f[j] * Constraint115[i][j];
	if(tmp < b115[i] || tmp > c115[i])
	{
	    printf("constraint %d failed\n", i);
	    printf("b = %ld, tmp = %ld, c = %ld\n\n", b115[i], tmp, c115[i]);
	    flag = 1;
	}
    }
    if(flag == 0) printf("passed\n");
    else printf("failed\n");
    printf("\n\n");

}

void show_vector(long a[], int n, const char* str)
{
    printf("%s:\n", str);
    for(int i=0; i<n; i++)
	printf("%ld ", a[i]);
    printf("\n\n");
}


int main()
{

    long a1[] = {0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0};

    long a2[] = {0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0};


    long b1[] = {0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0};


    input_constraint1(Constraint112, b112, c112, "constraint112.txt", &C112_n, &C112_m);
    input_constraint1(Constraint115, b115, c115, "constraint115.txt", &C115_n, &C115_m);


    /* printf("C115_n = %d, C115_m = %d\n", C115_n, C115_m); */
    /* for(int i=0; i<116; i++) */
    /* { */
    /* 	for(int j=0; j<115; j++) */
    /* 	{ */
    /* 	    printf("%ld, ", Constraint115[i][j]); */
    /* 	} */
    /* 	printf("\n"); */
    /* } */


    check1(a1, "a1");
    printf("\n\n");

    check1(a2, "a2");
    show_vector(a2, 112, "a2");
    printf("\n\n");

    check2( b1, "b1");
    printf("\n\n");

    for(int i=0; i<8; i++)
    {
	long f[115]; int k = 0;
	for(int j=0; j<115; j++)
	{
	    if(j == 0 || j == 93 || j == 114)
		f[j] = 2;
	    else
		f[j] = a2[k++];
	}
	f[0] = i & 1;
	f[93] = (i >> 1) & 1;
	f[114] = (i >> 2) & 1;

	printf("%d --- ", i);
	show_vector(f, 115, "f");
	check2(f, "f");
    }


    return 0;
}
