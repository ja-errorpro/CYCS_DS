import os

fin = open("response.txt", "r")
fout = open("response2.txt", "w")

al = fin.read().split()

c = 0
b = False
for i in al:
    if c == 16:
        c = 0
        fout.write("\n")
    fout.write(i)
    if b:
        fout.write(" ")
    c += 1
    b = not b
