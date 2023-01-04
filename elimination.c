#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "tools.c"

int n;
mpq_t A[200][200];
mpq_t B[200][200];
mpq_t zero;
mpq_t A_copy[200][200];
mpq_t det;

void show_matrix(mpq_t M[][200], int n, int m)
{
    for(int i=0; i<n; i++)
    {
	for(int j=0; j<m; j++)
	{
	    mpq_out_str(stdout, 10, M[i][j]);
	    printf(" ");
	}
	printf("\n");
    }
}

void input1()
{
    FILE* fp = fopen("matrix.txt", "r");
    fscanf(fp, "%d", &n);
    printf("n = %d\n", n);
    int max_digits = 0;
    long tmp;

    // A
    for(int i=0; i<n; i++)
    {
	for(int j=0; j<n; j++)
	{
	    fscanf(fp, "%ld", &tmp);
	    mpq_init(A[i][j]);
	    mpq_set_si(A[i][j], tmp, (unsigned long) 1);

	    // backup A
	    mpq_init(A_copy[i][j]);
	    mpq_set(A_copy[i][j], A[i][j]);
	}
    }

}

// A[i] <- A[i] / d
void row_div(mpq_t A[][200], int i, mpq_t d)
{
    for(int j=0; j<n; j++)
    {
	// A[i][j] = A[i][j] / d
	mpq_div(A[i][j], A[i][j], d);
    }
}


// A[a] <- A[a] - A[b] * w
void row_combine(mpq_t A[][200], int a, int b, mpq_t w)
{
    mpq_t tmp; mpq_init(tmp);
    for(int j=0; j<n; j++)
    {
	// A[a][j] = A[a][j] - A[b][j] * w
	mpq_mul(tmp, A[b][j], w);
	mpq_sub(A[a][j], A[a][j], tmp);
    }
    mpq_clear(tmp);
}

// swap A[a] and A[b]
void row_swap(mpq_t A[][200], int a, int b)
{
    mpq_t tmp; mpq_init(tmp);
    for(int j=0; j<n; j++)
    {
	// tmp = A[a][j]
	mpq_set(tmp, A[a][j]);
	// A[a][j] = A[b][j]
	mpq_set(A[a][j], A[b][j]);
        // A[b][j] = tmp
	mpq_set(A[b][j], tmp);
    }
    mpq_clear(tmp);
}

// pivot on ith column 
void pivot(int i)
{
    for(int k=i; k<n; k++)
    {
	if(!mpq_equal(A[k][i], zero))
	{
	    row_swap(A, i, k);
	    mpq_neg(det, det); // determinant sign change
	    row_swap(B, i, k);
	    return;
	}
    }
    printf("\n\n  Non Invertible\n\n");
    exit(1);
}


void init_B()
{
    long tmp;
    for(int i=0; i<n; i++)
    {
	for(int j=0; j<n; j++)
	{
	    mpq_init(B[i][j]);
	    if(i == j) tmp = 1;
	    else tmp = 0;
	    mpq_set_si(B[i][j], tmp, (unsigned long) 1);
	}
    }
}
void invert()
{
    init_B();
    mpq_t tmp; mpq_init(tmp);

    for(int i=0; i<n; i++) // rows and columns
    {
	if(mpq_equal(A[i][i], zero))
	    pivot(i);

	// divide ith row
	mpq_set(tmp, A[i][i]);
	row_div(A, i, tmp);
	row_div(B, i, tmp);

	mpq_mul(det, det, tmp); // det = det * tmp

	/* printf("step %d:-------\n", i); */
	/* show_matrix(A, n, n); */
	/* printf("----------\n"); */
	/* show_matrix(B, n, n); */
	/* printf("---------------\n\n"); */

	// eliminate ith column
	for(int k=0; k<n; k++) // rows 
	{
	    if(k == i) continue; // except ith row
	    mpq_set(tmp, A[k][i]);
	    row_combine(A, k, i, tmp);
	    row_combine(B, k, i, tmp);
	}
    }
    mpq_clear(tmp);
}

// A * B
void mult_test()
{
    printf("mult test:\n");
    printf("----------\n\n");
    printf("det(A) = ");
    mpq_out_str(stdout, 10, det);
    printf("\n\n");
    mpf_t fdet; mpf_init(fdet);
    mpf_set_q(fdet, det);
    printf("det(A) (floating) = ");
    mpf_out_str(stdout, 10, 0, fdet);
    printf("\n\n");

    mpq_t C[200][200];
    mpq_t tmp; mpq_init(tmp);
    for(int i=0; i<n; i++)
    {
	for(int j=0; j<n; j++)
	{
	    mpq_init(C[i][j]);
	    mpq_set_si(C[i][j], (long)0, (unsigned long)1);
	    for(int k=0; k<n; k++)
	    {
		// C[i][j] = C[i][j] + A[i][k] * B[k][j]
		mpq_mul(tmp, A_copy[i][k], B[k][j]);
		mpq_add(C[i][j], C[i][j], tmp);
	    }
	}
    }

    printf("AB:\n");
    show_matrix(C, n, n);
    printf("\n\n");

    mpq_clear(tmp);
    mpq_t one; mpq_init(one);
    mpq_set_si(one, (long)1, (unsigned long)1);
    for(int i=0; i<n; i++)
    {
	for(int j=0; j<n; j++)
	{
	    if(i == j && !mpq_equal(C[i][j], one))
	    {
		printf("mult-test failed\n\n");
		exit(1);
	    }
	    if(i != j && !mpq_equal(C[i][j], zero))
	    {
		printf("mult-test failed\n\n");
		exit(1);
	    }
	    mpq_clear(C[i][j]);
	}
    }
    mpq_clear(one);
}



void init()
{
    mpq_init(zero);
    mpq_set_si(zero, (long)0, (unsigned long)1);
    mpq_init(det);
    mpq_set_si(det, (long)1, (unsigned long)1);
}

void end()
{
    mpq_clear(zero);
    for(int i=0; i<n; i++)
    {
	for(int j=0; j<n; j++)
	{
	    mpq_clear(A[i][j]);
	    mpq_clear(B[i][j]);
	}
    }
}

void gcd(mpz_t p, mpz_t q, mpz_t g)
{
    mpz_t a, b; mpz_init(a); mpz_init(b);
    mpz_set(a, p);
    mpz_set(b, q);

    mpz_t tmp; mpz_init(tmp);
    mpz_t izero; mpz_init(izero);
    mpz_set_ui(izero, (unsigned long)0);
    while(1)
    {
	mpz_set(tmp, b);
	mpz_fdiv_r(b, a, b);
	mpz_set(a, tmp);
	if(mpz_cmp(a, izero) == 0)
	{
	    mpz_set(g, b);
	    break;
	}
	if(mpz_cmp(b, izero) == 0)
	{
	    mpz_set(g, a);
	    break;
	}
    }
    mpz_clear(tmp);
    mpz_clear(izero);
}

void lcm(mpz_t a, mpz_t b, mpz_t l)
{
    mpz_t g; mpz_init(g);
    mpz_t tmp; mpz_init(tmp);

    gcd(a, b, g);
    mpz_mul(tmp, a, b);
    mpz_fdiv_q(l, tmp, g);

    mpz_clear(g);
    mpz_clear(tmp);
}

void gcd_test()
{
    mpz_t a; mpz_init(a);
    mpz_t b; mpz_init(b);
    mpz_t g; mpz_init(g);
    mpz_t l; mpz_init(l);

    mpz_set_ui(a, (unsigned long) 72);
    mpz_set_ui(b, (unsigned long) 180);

    gcd(a, b, g);
    lcm(a, b, l);

    printf("gcd: ");
    mpz_out_str(stdout, 10, g);
    printf("\n\n");

    printf("lcm: ");
    mpz_out_str(stdout, 10, l);
    printf("\n\n");
}

void integerize()
{
    mpz_t d, tmp; mpz_init(d); mpz_init(tmp);
    mpz_set_ui(d, (unsigned long)1);
    for(int i=0; i<n; i++)
    {
	for(int j=0; j<n; j++)
	{
	    mpq_get_den(tmp, B[i][j]);
	    lcm(d, tmp, d);
	}
    }

    mpq_t qd; mpq_init(qd);
    mpq_set_z(qd, d);
    for(int i=0; i<n; i++)
	for(int j=0; j<n; j++)
	    mpq_mul(B[i][j], B[i][j], qd);

    printf("int matrix:\n");
    printf("-----------\n\n");
    printf("1/"); mpz_out_str(stdout, 10, d);
    printf(" * \n\n");
    show_matrix(B, n, n);
    printf("\n\n");

    mpz_clear(d);
    mpz_clear(tmp);
    mpq_clear(qd);
}


void test()
{
    input1();

    printf("matrix:\n");
    show_matrix(A, n, n);
    printf("\n\n");

    /* mpq_t t; mpq_init(t); */
    /* mpq_set_si(t, (long) 3, (unsigned long)1); */
    /* row_div(A, 1, t); */
    /* printf("matrix:\n"); */
    /* show_matrix(A, n, n); */
    /* printf("\n\n"); */

    invert();

    printf("A':\n");
    show_matrix(A, n, n);
    printf("\n\n");

    printf("B:\n");
    show_matrix(B, n, n);
    printf("\n\n");

    mult_test();

    integerize();
}

int main()
{
    init();

    test();

    printf("--------\n\n  thikache\n\n");
    end();
    return 0;
}

