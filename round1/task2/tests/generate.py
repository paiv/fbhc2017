#!/usr/bin/env python
from __future__ import print_function
import random


def generate(tests, n, x, r):
    print(tests)
    for i in range(tests):
        print('%d %d' % (n, r))
        for ni in range(n):
            print('%d %d' % (random.randint(0,x), random.randint(0,x)))


if __name__ == '__main__':
    generate(50, 50, 10, 3)
