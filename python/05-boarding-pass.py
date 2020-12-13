import os

python_dir=os.path.dirname(os.path.abspath(__file__))
input = os.path.join(os.path.dirname(python_dir),  "input/05-boarding-pass.txt")

max_seat_id = 116 * 8 + 8
min_seat_id = 2 * 8
all_seat_ids = list(range(min_seat_id, max_seat_id, 1))


def get_seats():
    bp = []
    with open(input, 'r') as infile:
        line = ''
        seat_max = 0
        for line in infile:
            line = line.rstrip()
            row = determine_bp_row(line[:7])
            col = determine_col(line[7:])
            seat_id = row * 8 + col
            seat_max = max(seat_max, seat_id)
            all_seat_ids.remove(seat_id)
        print("seat id max: " + str(seat_max))
    return all_seat_ids


def determine_col(line):
    col_chs = list(line)
    col_min = 0
    col_max = 8 - 1
    n = 3
    m = 2
    for j in range(m):
        if col_chs[j] == 'L':
            col_max = col_min + pow(2, m - j) - 1
        if col_chs[j] == 'R':
            col_min += pow(2, m - j)
    if col_chs[m] == 'L':
        return col_min
    else:
        return col_max


def determine_bp_row(line):
    row_chs = list(line)
    row_min = 0
    row_max = 128 - 1
    n = 7
    m = n - 1
    for j in range(m):
        if row_chs[j] == 'F':
            row_max = row_min + pow(2, m - j) - 1
        if row_chs[j] == 'B':
            row_min += pow(2, m - j)
    if row_chs[m] == 'F':
        return row_min
    else:
        return row_max


print(get_seats())
