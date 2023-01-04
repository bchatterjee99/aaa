/* sample.c */
#include <stdio.h>
#include <stdlib.h>
#include <glpk.h>

#include "tools.c"

int n;
int m;
int A[200][200];
int b[200];
int c[200];


void input1()
{
    FILE* fp = fopen("input1.txt", "r");
    fscanf(fp, "%d %d\n", &n, &m);
    printf("n = %d, m = %d\n\n", n, m);
    int max_digits = 0;

    // A
    for(int i=0; i<n; i++)
    {
	for(int j=0; j<m; j++)
	{
	    fscanf(fp, "%d", &A[i][j]);
	    max_digits = max1(max_digits, num_digits(A[i][j]));
	}
    }
    // b
    for(int i=0; i<n; i++)
    {
	    fscanf(fp, "%d", &b[i]);
	    max_digits = max1(max_digits, num_digits(b[i]));
    }
    // c
    for(int i=0; i<n; i++)
    {
	    fscanf(fp, "%d", &c[i]);
	    max_digits = max1(max_digits, num_digits(c[i]));
    }


    printf("matrix:\n");
    for(int i=0; i<n; i++)
    {
	print1(b[i], max_digits);
	printf(" <=  ");
	for(int j=0; j<m; j++)
	{
	    print1(A[i][j], max_digits);
	    printf(" ");
	}
	printf(" <= ");
	print1(c[i], max_digits);
	printf("\n");
    }
}

void input2()
{
    FILE* fp = fopen("ineq112.txt", "r");
    // fscanf(fp, "%d %d\n", &n, &m);
    n = 112; m = 112;
    printf("n = %d, m = %d\n\n", n, m);
    int max_digits = 0;

    // A
    for(int i=0; i<n; i++)
    {
	for(int j=0; j<m; j++)
	{
	    fscanf(fp, "%d", &A[i][j]);
	    max_digits = max1(max_digits, num_digits(A[i][j]));
	}
	fscanf(fp, "%d", &b[i]);
	b[i] = -b[i]; c[i] = b[i];
    }
    // b
    for(int i=0; i<n; i++)
    {
	b[i] = b[i] + 57;
	max_digits = max1(max_digits, num_digits(b[i]));
    }
    // c
    for(int i=0; i<n; i++)
    {
	c[i] = c[i] + 72;
	max_digits = max1(max_digits, num_digits(c[i]));
    }


    printf("matrix:\n");
    for(int i=0; i<n; i++)
    {
	print1(b[i], max_digits);
	printf(" <=  ");
	for(int j=0; j<m; j++)
	{
	    print1(A[i][j], max_digits);
	    printf(" ");
	}
	printf(" <= ");
	print1(c[i], max_digits);
	printf("\n");
    }
}

void solve()
{
    glp_prob *lp;
    int ia[1+40000], ja[1+40000];
    double ar[1+40000], z, x1, x2, x3;
    lp = glp_create_prob();
    glp_set_prob_name(lp, "thikache");

    glp_set_obj_dir(lp, GLP_MAX);

    glp_add_rows(lp, n);
    for(int i=0; i<n; i++)
    {
	if(b[i] == c[i])
	    glp_set_row_bnds(lp, i+1, GLP_FX, b[i], c[i]);
	else
	    glp_set_row_bnds(lp, i+1, GLP_DB, b[i], c[i]);
    }

    glp_add_cols(lp, m);
    for(int j=0; j<m; j++)
    {
	// glp_set_col_bnds(lp, j, GLP_LO, 0.0, 0.0);
	glp_set_col_kind(lp, j+1, GLP_BV);
	glp_set_obj_coef(lp, j+1, 1);
    }

    for(int i=0; i<n; i++)
    {
	for(int j=0; j<m; j++)
	{
	    int idx = i * m  + j + 1;
	    // printf("idx = %d,  r: %d, c: %d\n", idx, i+1, j+1);
	    ia[idx] = i + 1;
	    ja[idx] = j + 1;
	    ar[idx] = A[i][j];
	}
	
    }

    glp_iocp parm;
    glp_init_iocp(&parm);
    parm.presolve = GLP_ON;

    glp_load_matrix(lp, n*m, ia, ja, ar);
    glp_intopt(lp, &parm);
    z = glp_mip_obj_val(lp);
    printf("obj val: %lf\n", z);
    for(int j=0; j<m; j++)
    {
	double x = glp_mip_col_val(lp, j+1);
	printf("x%d: %lf, ", j+1, x);
    }
    printf("\n\n");
    glp_delete_prob(lp);
}


int check(int* sol)
{
    int flag = 0;
    for(int i=0; i<n; i++)
    {
	int tmp = 0;
	for(int j=0; j<m; j++)
	    tmp = tmp + A[i][j] * sol[j];
	if(tmp < b[i] || tmp > c[i])
	{
	    printf("constraint %d failed\n", i);
	    flag = 1;
	}
    }
    if(flag == 0)
	printf("passed\n");
    return flag;
}


void test()
{
    int fntr[] = {0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0};

    int fntr1[] = {0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0};

    check(fntr1);
}

int main(void)
{
    input2();
    solve();
    return 0;
}
