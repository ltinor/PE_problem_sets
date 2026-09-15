# recurrence: s[n] = 4 s[n-1] - 9 s[n-3] - s[n-4] - 5 s[n-5] + 12 s[n-6] + 12 s[n-7] - 4 s[n-8]
seq = [1, 1, 2, 4, 9, 20, 46, 105]
for n in range(8, 40):
    v = 4*seq[n-1] - 9*seq[n-3] - seq[n-4] - 5*seq[n-5] + 12*seq[n-6] + 12*seq[n-7] - 4*seq[n-8]
    seq.append(v)
for i, v in enumerate(seq):
    print(i, v)
