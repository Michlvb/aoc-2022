#Find top three

values = []
total = []

highest = 0
len = 3
current = 0

with open('elfcalories.txt', 'r') as input:
    for i, line in enumerate(input):
        if (line == '\n'):
            values.append(current)
            current = 0
        else:
            current += int(line)

for i in range(len):
    tmp = max(values)
    total.append(tmp)
    values.remove(tmp)

print(f"Total: {sum(total)}")