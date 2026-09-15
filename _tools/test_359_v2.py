# Extended simulation for Hilbert's Hotel
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
    return occupancy

occ = simulate(10000)

# Check known values
print('P(10,20) =', occ.get((10,20), 0), '(expected 440)')
print('P(25,75) =', occ.get((25,75), 0), '(expected 4863)')
print('P(99,100) =', occ.get((99,100), 0), '(expected 19454)')

# Try to derive formula
# P(f,1) = floor(f^2/2) confirmed
print()
for f in range(1, 15):
    print(f'P({f},1) = {occ[(f,1)]}, floor(f^2/2) = {f*f//2}')

# P(f,r) formula attempt
# Test: P(f,r) = T_{r} + something based on f?
# T_r = r(r+1)/2
print()
print("Test: P(f,r) - T_r:")
for r in range(1, 6):
    Tr = r*(r+1)//2
    for f in range(1, 6):
        val = occ.get((f,r), 0)
        if val:
            print(f'  P({f},{r})-T_{r} = {val} - {Tr} = {val-Tr}')
