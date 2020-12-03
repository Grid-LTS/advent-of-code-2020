import os

input = os.path.join(os.path.dirname(os.path.abspath(__file__)), "input/03-tree-map.txt")


def count_trees(down,right):
    map = []
    with open(input, 'r') as infile:
        the_line = ''
        for line in infile:
            the_line = line.rstrip()
            map.append(the_line)

    width = len(the_line)
    rows = len(map)
    n = right * (rows -1) // down
    multiply = n // width + 1
    char_map = []
    for line in map:
        total = ''
        for i in range(multiply):
            total += line
        char_map.append(list(total))
    counter = 0
    for j in range((rows - 1)//down):
        index = j + 1
        if char_map[index*down][right * index] == '#':
            counter += 1
    return counter

a = count_trees(1,1)
b = count_trees(1,3)
c = count_trees(1,5)
d = count_trees(1,7)
e = count_trees(2,1)

print(a)
print(b)
print(c)
print(d)
print(e)

print(a*b*c*d*e)