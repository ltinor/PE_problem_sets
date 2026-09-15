import sys

def step(states):
    nxt = set()
    for st in states:
        bits = st
        while bits:
            low = bits & -bits
            idx = low.bit_length() - 1
            x = idx // 4
            y = idx % 4
            b1 = ((x + 1) * 4 + y)
            b2 = ((x + 1) * 4 + (y + 1) % 4)
            if (st >> b1) & 1 or (st >> b2) & 1:
                bits &= bits - 1
                continue
            new = (st ^ low) | (1 << b1) | (1 << b2)
            nxt.add(new)
            bits &= bits - 1
    return nxt

states = {1}
print(0, len(states))
for N in range(1, 22):
    states = step(states)
    print(N, len(states))
    sys.stdout.flush()
