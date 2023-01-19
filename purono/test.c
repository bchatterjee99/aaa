
#include <stdio.h>

struct aaa{
    int a;
    int b;
};


void fun(struct aaa * A[][10])
{
    
}

void test(int a[][10], int b[10])
{
    printf("test: a = %p\n", a);
    printf("test: &a[0][0] = %p\n\n", &a[0][0]);
    b[0] = 5;
}

int main()
{
    /* struct aaa a; */
    /* struct aaa* A[10][10]; */
    /* A[0][0] = &a; */

    int a[10][10];
    int b[10];
    for(int i=0; i<10; i++)
	for(int j=0; j<10; j++)
	    a[i][j] = 0;
    for(int i=0; i<10; i++) b[i] = 1;

    printf("a = %p\n", a);
    printf("&a[0][0] = %p\n\n", &a[0][0]);
    test(a, b);

    printf("a = \n");
    for(int i=0; i<10; i++)
    {
	for(int j=0; j<10; j++)
	    printf("%d ", a[i][j]);
	printf("\n");

    }
    printf("b = ");
    for(int i=0; i<10; i++) printf("%d ", b[i]);

    printf("\n\n  thikache\n\n");
    return 0;
}
