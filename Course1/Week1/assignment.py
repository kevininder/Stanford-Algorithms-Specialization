# Implementation of Karatsuba algorithm in a recursive manner.
# x = 3141592653589793238462643383279502884197169399375105820974944592
# y = 2718281828459045235360287471352662497757247093699959574966967627

import math


def karatsuba(x, y):
    if x < 10 or y < 10:
        return x * y
    else:
        b = max(len(str(x)), len(str(y))) // 2
        x1 = x // (10**b)
        x0 = x % (10**b)
        y1 = y // (10**b)
        y0 = y % (10**b)
        z0 = karatsuba(x0, y0)
        z2 = karatsuba(x1, y1)
        z1 = karatsuba(x1 + x0, y1 + y0) - z2 - z0
        return z2 * (10**(b*2)) + z1 * (10**b) + z0


x = int(input("Enter the first integer: "))
y = int(input("Enter the second integer: "))

print(int(karatsuba(x, y)))
