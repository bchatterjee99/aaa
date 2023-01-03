
int max1(int a, int b) { if(a >= b) return a; return b; }


int num_digits(int a)
{
    if(a == 0) return 1;
    int ans = 0;
    while(a > 0)
    {
	ans++;
	a = a / 10;
    }
    return ans;
}

void print1(int a, int pad)
{
    int x = pad - num_digits(a);
    while(x > 0) { printf(" "); x--; }
    printf("%d", a);
}
