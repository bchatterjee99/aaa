import numpy as np


f = open("matrix.txt");

line = next(f).split();
n = int(line[0]);
print("n = ", n);

A = np.zeros((n, n));

for i in range(0, n):
    line = next(f).split();
    for j in range(0, n):
        A[i][j] = int(line[j]);

print("matrix:");
print(A);
    
det = np.linalg.det(A);

print("determinant = ", det);
