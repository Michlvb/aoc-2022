# List of calories

highest = 0
current = 0

with open('elfcalories.txt', 'r') as input:
    for i, line in enumerate(input):
        if (line == '\n'):
            if (current > highest):
                highest = current
            current = 0
        else:
            current += int(line)

# With highest calories
print(highest)