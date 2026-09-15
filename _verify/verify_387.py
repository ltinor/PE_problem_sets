#!/usr/bin/env python3
"""PE 387: Harshad Numbers
Sum of strong, right-truncatable Harshad primes < 10^14
"""
import sys
sys.setrecursionlimit(1000000)

def is_prime(n):
    if n < 2:
        return False
    if n < 4:
        return True
    if n % 2 == 0 or n % 3 == 0:
        return False
    i = 5
    while i * i <= n:
        if n % i == 0 or n % (i + 2) == 0:
            return False
        i += 6
    return True

def digit_sum(n):
    return sum(int(d) for d in str(n))

def solve(limit):
    """Find sum of strong right-truncatable Harshad primes < limit"""
    total = 0
    
    # Generate right-truncatable Harshad numbers via DFS
    # Start from single digits 1-9
    def dfs(num):
        nonlocal total
        s = digit_sum(num)
        
        # Check if num is a strong Harshad number (num / digit_sum is prime)
        if num % s == 0 and is_prime(num // s):
            # Strong Harshad number - try appending digits to make primes
            for d in range(1, 10, 2):  # odd digits only for primality
                candidate = num * 10 + d
                if candidate >= limit:
                    continue
                if is_prime(candidate):
                    total += candidate
        
        # Continue building right-truncatable Harshad numbers
        for d in range(10):
            nxt = num * 10 + d
            if nxt >= limit:
                continue
            if nxt % digit_sum(nxt) == 0:
                dfs(nxt)
    
    for d in range(1, 10):
        dfs(d)
    
    return total

if __name__ == '__main__':
    print("Testing PE 387...")
    
    # Small limit
    result_1e4 = solve(10000)
    print(f"Sum < 10000: {result_1e4} (expected: 90619)")
    assert result_1e4 == 90619, f"Failed: {result_1e4} != 90619"
    
    # PE limit
    result = solve(10**14)
    print(f"Sum < 10^14: {result} (expected: 696067597313468)")
    assert result == 696067597313468, f"Failed: {result} != 696067597313468"
    print("All tests passed!")
