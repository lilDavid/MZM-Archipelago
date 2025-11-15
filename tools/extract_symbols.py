from collections import defaultdict
import sys
import json

def main():
    input = sys.argv[1]
    output = sys.argv[2]

    with open('./extracts.json') as extractfile:
        what_to_extract = defaultdict(list, json.load(extractfile))

    sections = defaultdict(dict)
    with open(input, 'r') as mapfile:
        while True:
            if mapfile.readline().strip() == 'Linker script and memory map':
                break

        section = None
        file = None
        while True:
            line = mapfile.readline()
            if line.strip() == '':
                continue

            if line[0] != ' ':
                try:
                    section, *_ = line.split()
                except ValueError:
                    section, *_ = (line + mapfile.readline()).split()
                if section == '.debug':
                    break
                continue

            line = line[1:].rstrip()
            if line.startswith('*fill*'):
                continue

            if line.endswith(')'):
                file = line[:line.find('(')].lstrip()
            if line[0] != ' ':
                continue
            if line.endswith('= .'):
                file = None

            if section not in what_to_extract['sections']:
                continue
            if file and file not in what_to_extract[section]:
                continue

            addr, symbol, *_ = line.split()

            if symbol == '.':
                continue

            sections[section][symbol] = int(addr, 0)

    with open(output, 'w') as jsonfile:
        json.dump(sections, jsonfile, indent=4)


if __name__ == '__main__':
    main()
