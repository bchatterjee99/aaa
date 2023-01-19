#include <stdio.h>
#include "ilp.h"

long C[200][200]; // 115x115 constraint matrix
long D[200][200]; // C-inverse * 16512
#define INV_DIV 16512
long Constraint[200][200];
long b[200], c[200];
int n;
int C_n;
int C_m;
long E[200][200];


void test()
{
    long f1[] = {0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0};

    long state[200];
    mult_vector(f1, )

}


// C-inverse = 1/INV_DIV * D
int main()
{
    input_matrix(C, "C.txt", &n);
    input_matrix(D, "D.txt", &n);
    input_constraint(Constraint, b, c, "constraint115.txt", &C_n, &C_m);


    test();

    printf("\n\n thikache\n\n");
    return 0;
}
