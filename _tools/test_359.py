# Simulate Hilbert's Hotel for small values
def simulate(max_person):
    floor_latest = {}
    occupancy = {}
    for person in range(1, max_person + 1):
        best_floor = None
        fl = 1
        while True:
            if fl not in floor_latest:
                best_floor = fl
                break
            latest = floor_latest[fl]
            s = latest + person
            rt = int(s ** 0.5)
            if rt * rt == s:
                best_floor = fl
                break
            fl += 1
        floor_latest[best_floor] = person
        room = 1
        while (best_floor, room) in occupancy:
            room += 1
        occupancy[(best_floor, room)] = person
    return floor_latest, occupancy

floor_latest, occ = simulate(500)

# Print P(f,1) for f=1..20
for f in range(1, 21):
    print(f'P({f},1) = {occ.get((f,1), 0)}')

print()
for r in range(1, 11):
    print(f'P(1,{r}) = {occ.get((1,r), 0)}')

print()
print('P(10,20) =', occ.get((10,20), 0), '(expected 440)')
print('P(25,75) =', occ.get((25,75), 0), '(expected 4863)')
print('P(99,100) =', occ.get((99,100), 0), '(expected 19454)')
