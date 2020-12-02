import os
import re

input = os.path.join(os.path.dirname(os.path.abspath(__file__)), "input/02-password-policy.txt")

def first_interpretation():
    good_pw = []
    with open(input, 'r') as infile:
        for line in infile:
            result = re.match(r'(\d+)-(\d+) (\w): (\w+)', line)
            if result is None:
                continue
            min=int(result.group(1))
            max=int(result.group(2))
            chr=result.group(3)
            word=result.group(4)
            if min <= word.count(chr) <= max:
                good_pw.append(line)
                print(line)
            
    print("number " + str(len(good_pw)))

def new_interpretation():
    good_pw = []
    with open(input, 'r') as infile:
        for line in infile:
            result = re.match(r'(\d+)-(\d+) (\w): (\w+)', line)
            if result is None:
                continue
            first = int(result.group(1))
            second = int(result.group(2))
            chr = result.group(3)
            pw = result.group(4)
            pos1 = first-1
            pos2 = second-1
            if pos1 >= len(pw) or pos2 >= len(pw):
                continue
            if pw[pos1] == chr and pw[pos2] != chr:
                good_pw.append(line)
                print(line)
                continue
            if pw[pos1] != chr and pw[pos2] == chr:
                good_pw.append(line)
                print(line)

    print("second interpret " + str(len(good_pw)))
    
first_interpretation()
new_interpretation()