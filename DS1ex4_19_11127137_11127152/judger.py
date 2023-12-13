

schools = []
with open("schools.txt", "r") as f:
    lines = f.readlines()
    schools = [line for line in lines]
inputs = "1\n404\n"

with open("1.in", "w") as f:
    f.write(inputs)
    for i in range(1000):
        f.write("2\n")
        f.write(str(i) + "\n")

    f.write("0\n")

print("Done!")