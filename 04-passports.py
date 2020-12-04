import os

input = os.path.join(os.path.dirname(os.path.abspath(__file__)), "input/04-passports.txt")


def passports():
    passports = []
    valid_keys = ['byr', 'iyr', 'eyr', 'hgt', 'hcl', 'ecl', 'pid']
    counter = 0
    with open(input, 'r') as infile:
        line = infile.readline()
        while line != '':
            passport = dict()
            while line != '\n' and line != '':
                components = line.split(' ')
                for component in components:
                    kv = component.split(':')
                    passport[kv[0].strip()] = kv[1].strip()
                line = infile.readline()
            fields = [x for x in passport.keys() if x in valid_keys]
            if len(fields) == len(valid_keys):
                # comment the if out for part I
                if validator(passport):
                    counter += 1
            line = infile.readline()
        print(counter)


def validator(passport):
    try:
        valid = True
        byr = int(passport['byr'])
        valid = valid and byr >= 1920 and byr <= 2002
        iyr = int(passport['iyr'])
        valid = valid and iyr >= 2010 and iyr <= 2020
        eyr = int(passport['eyr'])
        valid = valid and eyr >= 2020 and eyr <= 2030

        height = passport['hgt']
        unit = height[-2:]
        val = int(height[:-2])
        if unit == 'in':
            valid = valid and val >= 59 and val <= 76
        elif unit == 'cm':
            valid = valid and val >= 150 and val <= 193
        else:
            valid = False

        hc = passport['hcl']
        valid = valid and hc[0] == '#' and len(hc[1:]) == 6
        value = int(hc[1:], 16)
        valid = valid and passport['ecl'] in ['amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth']
        pid = passport['pid']
        valid = valid and len(pid) == 9 and int(pid)
    except ValueError as e:
        valid = False
    return valid


passports()
