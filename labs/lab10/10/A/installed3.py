#!/usr/bin/env python
import re


def main():
    line_number: int = 0
    with open('logs.txt') as file:
        for line in file:
            line_number += 1
            # searching for all the packages that were installed, but excluding those that were half-installed
            # moreover, the cpu architecture is excluded too
            m = re.search(r" installed ((.+):(.+)) .*", line.rstrip())
            if m:
                print("%d: %s" % (line_number, m.group(2)))


if __name__ == "__main__":
    main()
