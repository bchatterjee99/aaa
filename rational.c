
long gcd(long a, long b)
{
    if(b == 0) return a;
    if(a == 0) return b;
    long rem = a % b;
    long ans = gcd(b, rem);
    return ans;
}

long lcm(long a, long b)
{
    long prod = a * b;
    long g = gcd(a, b);
    long ans = prod / g;
    return ans;
}

void reduce(struct rational* a)
{
    long g = gcd(a->n, a->d);
    a->n = a->n / g;
    a->d = a->d / g;
}

// c = a + b
void add(struct rational* a, struct rational* b, struct rational* c)
{
    long l = lcm(a->d, b->d);
    coeff1 = l/a->d;
    coeff2 = l/b->d;
    long neumerator = a->n * coeff1 + b->n * coeff2; 
    long denominator = l;
    c->n = neumerator;
    c->d = denominator;
    reduce(c);
}

// c = a - b
void sub(struct rational* a, struct rational* b, struct rational* c)
{
    long l = lcm(a->d, b->d);
    coeff1 = l/a->d;
    coeff2 = l/b->d;
    long neumerator = a->n * coeff1 - b->n * coeff2; 
    long denominator = l;
    c->n = neumerator;
    c->d = denominator;
    reduce(c);
}

// c = a * b
void mult(struct rational* a, struct rational* b, sturct rational* c)
{
    long numerator = a->n * b->n;
    long denominator = a->d * b->d;
    c->n = neumerator;
    c->d = denominator;
    reduce(c);
}

// c = a / b
void divide(struct rational* a, struct rational* b, sturct rational* c)
{
    long numerator = a->n * b->d;
    long denominator = a->d * b->n;
    c->n = neumerator;
    c->d = denominator;
    reduce(c);
}
