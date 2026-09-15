MOD = 987654321

# Grundy numbers for 2..10
cnt = [0]*4
# G(2)=0, G(3)=0, G(4)=1, G(5)=0, G(6)=1, G(7)=0, G(8)=2, G(9)=1, G(10)=1
cnt = [4, 4, 1, 0]
print('cnt:', cnt)

# FWHT manually
def wh(a):
    n = len(a)
    a = a[:]
    length = 1
    while 2*length <= n:
        for i in range(0, n, 2*length):
            for j in range(length):
                u = a[i+j]
                v = a[i+length+j]
                a[i+j] = (u+v) % MOD
                a[i+length+j] = (u-v) % MOD
        length <<= 1
    return a

a = wh(cnt)
print('FWHT:', a)

# Raise to power 5
K = 5
a = [pow(x, K, MOD) for x in a]
print('^5:', a)

# Inverse FWHT
a = wh(a)
print('I-FWHT:', a)

inv_n = pow(4, MOD-2, MOD)
a = [x * inv_n % MOD for x in a]
print('Final:', a)

total = pow(9, 5, MOD)
ans = (total - a[0]) % MOD
print(f'f(10,5) = {ans}')
print(f'Expected: 40085')
