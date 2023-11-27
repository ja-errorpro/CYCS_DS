import random

f = open('input399.txt', 'w')
f.write('OID\tArrival\tDuration\tTimeOut\n')

for oid in range(1, 100000):
    arrival = 100000 - oid
    duration = random.randint(1, 1000)
    timeout = random.randint(1, 1000)
    f.write(str(oid) + '\t' + str(arrival) + '\t' + str(duration) + '\t' + str(timeout) + '\n')

f.close()