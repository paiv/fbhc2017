#!/usr/bin/env python
from __future__ import print_function
import random


def generate(days, n):
    print(days)
    for i in range(days):
        print(n)
        for x in range(n):
            print(random.randint(1,100))


if __name__ == '__main__':
    generate(500, 100)
