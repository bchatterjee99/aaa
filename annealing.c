#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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
#define Start_Temp 100
int Temperature;

struct energy{
    double total;
    double b; // dist from boolean vector
    double c; // dist from failed constraints
};

// get next state
// jump dist. depend on temperature ?
void step(long curr_state[], long next_state[])
{
    for(int i=0; i<n; i++)
	next_state[i] = curr_state[i];

    for(int i=0; i<n; i++)
    {
        // prob decrease with temperature
	if((rand() % Max_Temp) <= Temperature/5)
	{
	    // +/- [0 .. 5]
	    /* next_state[i] = curr_state[i] + (5 - rand()%10); */
	    /* if(next_state[i] < b[i]) next_state[i] = b[i]; */
	    /* if(next_state[i] > c[i]) next_state[i] = c[i]; */

	    // swap state[i] and state[j]
	    int j = rand() % n;
	    long tmp = next_state[i];
	    next_state[i] = next_state[j];
	    next_state[j] = tmp;
	}
    }
}

double abs1(double x)
{
    if(x >= 0) return x;
    return -x;
}
double min1(double x, double y)
{
    if(x <= y) return x;
    return y;
}

// binarize vector
// return distance from boolean vector
double binarize(long state_inv[], long binary[])
{
    double e = 0;
    for(int i=0; i<n; i++)
    {
	double t = (double) state_inv[i] / (double)INV_DIV;
	if(abs1(t - 0.0) <= abs1(t - 1.0))
	{
	    binary[i] = 0;
	    e = e + abs1(t - 0.0);
	}
	else
	{
	    binary[i] = 1;
	    e = e + abs1(t - 1.0);
	}
    }
    return e;
    
}

// energy of state
void energy(long state[], struct energy* e)
{
    double energy = 0;

    long state_inv[200];
    long binary[200];

    // state_inv = D * state
    mult_vector(D, state, state_inv, n);

    // binarize state_inv
    // also get Energy(distance from boolean vector)
    e->b = binarize(state_inv, binary);

    // Energy(distance from failed constraints)
    int dist = check(binary, Constraint, b, c, C_n, C_m);
    if(dist == 0)
    {
	show_vector(binary, n, "---");
    }

    e->c = (double)dist;
    e->total = e->b + e->c;
}

// reduce temperature
void cool()
{
    if(Temperature == 10) return;
    if(rand() % 50 == 0) Temperature--;
}

// prob (0 - 100) to jump state
int prob(double E1, double E2)
{
    // if(E2 <= E1) return 100;
    double p = (E2 - E1)/(double)Temperature;
    double prob = 1.0 / exp(p);
    int ans = (int)(prob * 100.0);
    if(ans > 100) ans = 100;
    return ans;
}

void copy_state(long source[], long dest[])
{
    for(int i=0; i<n; i++)
	dest[i] = source[i];
}
void annealing()
{
    int itr = 0;
    struct energy min_energy; min_energy.total = 100000000;
    long f1[] = {0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0};
    long curr_state[200];
    long next_state[200];

    // curr_state = C * f1
    mult_vector(C, f1, curr_state, n);

    show_vector(curr_state, n, "curr-state");

    // starting temperature
    Temperature = Start_Temp;

    // take one step
    step(curr_state, curr_state);
    show_vector(curr_state, n, "step-1");
    // annealing
    while(1)
    {
	// get next-state
	step(curr_state, next_state);
	struct energy E1, E2;
	energy(curr_state, &E1);
	energy(next_state, &E2);

	// min_energy = min1(E1, min_energy);
	if(min_energy.total >= E1.total)
	{
	    min_energy.total = E1.total;
	    min_energy.b = E1.b;
	    min_energy.c = E1.c;
	}
	printf("curr-energy: %lf, min-energy-reached: %lf (%lf, %lf)\n", E1.total, min_energy.total, min_energy.b, min_energy.c);

	int p = prob(E1.total, E2.total); // jump prob
	if(rand() % 100 <= p) // jump
	{
	    copy_state(next_state, curr_state);
	}
	cool();

	itr++;
	// if(itr >= 10) break;
    }
    
}

void test()
{
    long f1[] = {0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0};

    // check1(f1, Constraint, b, c, C_n, C_m);
    Temperature = Start_Temp;
    long curr_state[200];
    long next_state[200];
    struct energy E1, E2, E3;

    mult_vector(C, f1, curr_state, n);
    energy(curr_state, &E1);
    show_vector(curr_state, n, "start-state");
    printf("start energy: %lf\n\n\n", E1);

    step(curr_state, curr_state);
    energy(curr_state, &E2);
    show_vector(curr_state, n, "curr-state");
    printf("curr-state energy: %lf\n\n\n", E2);

    step(curr_state, next_state);
    energy(next_state, &E3);
    show_vector(next_state, n, "next-state");
    printf("next-state energy: %lf\n\n\n", E3);

    double p1 = prob(E2.total, E3.total);
    printf("prob(E2, E3): %lf\n", p1);
    double p2 = prob(E3.total, E2.total);
    printf("prob(E3, E2): %lf\n", p2);

    printf("\n\n");
}

// C-inverse = 1/INV_DIV * D
int main()
{
    srand(time(0));
    input_matrix(C, "C.txt", &n);
    input_matrix(D, "D.txt", &n);
    input_constraint(Constraint, b, c, "constraint115.txt", &C_n, &C_m);

    /* mult_matrix(C, D, E, n); */
    /* show_matrix(E, n, "E"); */
    // test();
    annealing();

    printf("\n\n thikache\n\n");
    return 0;
}
