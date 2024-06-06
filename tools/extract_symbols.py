import sys
import json

def main():
    input = sys.argv[1]
    output = sys.argv[2]

    with open('./extracts.json') as extractfile:
        what_to_extract = json.load(extractfile)

    sections = {}
    with open(input, 'r') as mapfile:
        while True:
            if mapfile.readline().strip() == 'Linker script and memory map':
                break

        section = '*default*'
        origin = 0
        here = 0
        while True:
            line = mapfile.readline()
            if line != '\n' and line[0] != ' ':
                section, origin, *_ = line.split()
                origin = int(origin, 0)

            if section == '.rodata':
                break
            elif section[0] == '.':
                continue

            if section not in what_to_extract['sections']:
                continue
            if section not in sections:
                sections[section] = {}

            assignment = line[50:].strip()
            if not assignment:
                continue
            try:
                lhs, rhs = assignment.split(" = ")
            except ValueError:
                continue
            if lhs == '.':
                here = int(rhs, 0)
            elif rhs == '.':
                sections[section][lhs] = origin + here
            else:
                sections[section][lhs] = origin + int(rhs, 0)

        file = ''
        while True:
            section = 'rom'
            line = mapfile.readline()
            if line.startswith('OUTPUT'):
                break

            line = line.strip()

            if line.endswith('(.rodata)'):
                file = line[:-len('(.rodata)')]

            if file not in what_to_extract['rom']:
                continue

            try:
                address, symbol = line.split()
            except ValueError:
                continue
            sections[section][symbol] = int(address, 0)

    with open(output, 'w') as jsonfile:
        json.dump(sections, jsonfile)


if __name__ == '__main__':
    main()