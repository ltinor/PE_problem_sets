from fractions import Fraction

seq = [1, 1, 2, 4, 9, 20, 46, 105, 243, 561, 1301, 3014, 6995, 16227, 37668, 87426,
       202960, 471146, 1093803, 2539294, 5895236]

def berlekamp_massey(s):
    C = [Fraction(1)]
    B = [Fraction(1)]
    L = 0
    m = 1
    b = Fraction(1)
    for n in range(len(s)):
        d = Fraction(s[n])
        for i in range(1, L + 1):
            d += C[i] * s[n - i]
        if d == 0:
            m += 1
        elif 2 * L <= n:
            T = C[:]
            coef = d / b
            if len(C) < len(B) + m:
                C += [Fraction(0)] * (len(B) + m - len(C))
            for i in range(len(B)):
                C[i + m] -= coef * B[i]
            L = n + 1 - L
            B = T
            b = d
            m = 1
        else:
            coef = d / b
            if len(C) < len(B) + m:
                C += [Fraction(0)] * (len(B) + m - len(C))
            for i in range(len(B)):
                C[i + m] -= coef * B[i]
            m += 1
    return C, L

C, L = berlekamp_massey(seq)
print("order L =", L)
print("C =", C)
# s[n] = -sum_{i=1..L} C[i] s[n-i]
print("recurrence coefficients (for s[n]):")
for i in range(1, L+1):
    print("coef s[n-%d] =" % i, -C[i])
