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
    FILE* fp = fopen("input.txt", "r");
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

void solve()
{
    glp_prob *lp;
    int ia[1+1000], ja[1+1000];
    double ar[1+1000], z, x1, x2, x3;
    lp = glp_create_prob();
    glp_set_prob_name(lp, "thikache");

    glp_set_obj_dir(lp, GLP_MAX);
    glp_add_rows(lp, n);
    for(int i=0; i<n; i++)
    {
	glp_set_row_bnds(lp, i+1, GLP_DB, b[i], c[i]);
    }
    /* glp_set_row_bnds(lp, 1, GLP_UP, 0.0, 100.0); */
    /* glp_set_row_bnds(lp, 2, GLP_UP, 0.0, 600.0); */
    /* glp_set_row_bnds(lp, 3, GLP_UP, 0.0, 300.0); */
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
	    printf("idx = %d,  r: %d, c: %d\n", idx, i+1, j+1);
	    ia[idx] = i + 1;
	    ja[idx] = j + 1;
	    ar[idx] = A[i][j];
	}
	
    }
    /* ia[1] = 1, ja[1] = 1, ar[1] = 1.0; /\* a[1,1] = 1 *\/ */
    /* ia[2] = 1, ja[2] = 2, ar[2] = 1.0; /\* a[1,2] = 1 *\/ */
    /* ia[3] = 1, ja[3] = 3, ar[3] = 1.0; /\* a[1,3] = 1 *\/ */
    /* ia[4] = 2, ja[4] = 1, ar[4] = 10.0; /\* a[2,1] = 10 *\/ */
    /* ia[5] = 3, ja[5] = 1, ar[5] = 2.0; /\* a[3,1] = 2 *\/ */
    /* ia[6] = 2, ja[6] = 2, ar[6] = 4.0; /\* a[2,2] = 4 *\/ */
    /* ia[7] = 3, ja[7] = 2, ar[7] = 2.0; /\* a[3,2] = 2 *\/ */
    /* ia[8] = 2, ja[8] = 3, ar[8] = 5.0; /\* a[2,3] = 5 *\/ */
    /* ia[9] = 3, ja[9] = 3, ar[9] = 6.0; /\* a[3,3] = 6 *\/ */
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

int main(void)
{
    input1();
    solve();
    return 0;
}
/* eof */
