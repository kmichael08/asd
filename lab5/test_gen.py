#!/usr/bin/env python3
# Test generator for the problem of motorway painting
import random


def intervals(n, m):
    ranges = []
    for i in range(m):
        a = random.randint(1, n)
        b = random.randint(1, n)
        c = random.randint(0, 1)
        if c == 0:
            d = 'B'
        else:
            d = 'C'

        ranges.append((min(a, b), max(a, b), d))
    return ranges


def make_test(target):
    n = random.randint(1, 1000)
    m = random.randint(1, 1000)

    target.writelines(str(n) + '\n')
    target.writelines(str(m) + '\n')

    for (a, b, c) in intervals(n, m):
        target.writelines(str(a) + ' ' + str(b) + ' ' + c + '\n')


for i in range(10):
    test = open('test' + str(i) + '.in', 'w')
    make_test(test)
