import os
python_dir=os.path.dirname(os.path.abspath(__file__))
input = os.path.join(os.path.dirname(python_dir), "input/01-expense_report.txt")
numbers = []
with open(input, 'r') as infile:
    for line in infile:
        numbers.append(int(line))


def find(numbers_arr):
    for i in range(len(numbers_arr)):
        first = numbers_arr[i]
        for j in range(len(numbers_arr) - i - 1):
            second = numbers_arr[i + j + 1]
            if first + second == 2020:
                print("first:" + str(first))
                print("second:" + str(second))
                return first * second
    print("Pair not found")


def find_three(numbers_arr):
    for i in range(len(numbers_arr)):
        first = numbers_arr[i]
        for j in range(len(numbers_arr) - i - 1):
            second = numbers_arr[i + j + 1]
            for k in range(len(numbers_arr) - i - j - 2):
                third = numbers[i + j + k + 2]
                if first + second + third == 2020:
                    print("first:" + str(first))
                    print("second:" + str(second))
                    print("third:" + str(third))
                    return first * second * third
    print("Triple not found")


print("Pair " + str(find(numbers)))
print("Triple " + str(find_three(numbers)))
