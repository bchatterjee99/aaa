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

#define Max_Temp 100
#define Start_Temp 80
int Temperature;


void test()
{
    long f1[] = {0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0};

    check(f1, Constraint, b, c, C_n, C_m);
}

// get next state
void step(long curr_state[], long next_state[])
{
    for(int i=0; i<n; i++)
    {
	next_state[i] = curr_state[i];

        // prob decrease with temperature
	if(rand() % Max_Temp <= Temperature)  
	{
	    // +/- [0 .. 5]
	    curr_state[i] = curr_state[i] + (5 - rand()%10);
	    if(curr_state[i] >= c[i]) curr_state[i] = c[i];
	}
    }
}

double abs1(double x)
{
    if(x >= 0) return x;
    return -x;
}

// binarize vector
// return distance from boolean vector
double binarize(double v[], long binary[])
{
    double e = 0;
    for(int i=0; i<n; i++)
    {
	double t = (double) state_inv[i] / (double)INV_DIV;
	if(abs(t - 0.0) <= abs(t - 1.0))
	{
	    binary[i] = 0;
	    e = e + abs(t - 0.0);
	}
	else
	{
	    binary[i] = 1;
	    e = e + abs(t - 1.0);
	}
    }
    return e;
    
}

// energy of state
double energy(long state[])
{
    double e1 = 0;
    double e2 = 0;

    long state_inv[200];
    long binary[200];

    // state_inv = D * state
    mult_vector(D, state, state_inv, n);
    // binarize state_inv
    e1 = binarize(state_inv, binary);


}

void annealing()
{
    long f1[] = {0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0};

    long curr_state[200];
    long next_state[200];

    // curr_state = C * f1
    mult_vector(C, f1, curr_state, n);

    // annealing
    Temperature = Start_Temp;
    while(1)
    {
	// get next-state
	step(curr_state, next_state);
	double E1 = energy(curr_state);
	double E2 = energy(next_state);
    }
    
}

// C-inverse = 1/INV_DIV * D
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
