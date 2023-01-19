n = 4;
K = GF(2 ^ n)
arr = [0] * (2 ^ n)

def f(x, n):
    sum = 0;
    tmp = x;
    for i in range(0, n):
        sum = sum + tmp;
        tmp = tmp * tmp;
        # print("sum = ", sum, "tmp = ", tmp);
    # print("sum = ", sum, "tmp = ", tmp);
    return sum;


i = 0;
for a in GF(2 ^ n, "x"):
    arr[i] = a;
    i = i + 1;

alpha = arr[15];
print("alpha = ", alpha)
for a in GF(2 ^ n, "x"):
    print("a =", a);
    print("alpha * a = ", alpha * a);
    ans = f(alpha * a, n);
    print(ans);
    print();


