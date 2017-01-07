#!/usr/bin/env python
from __future__ import print_function
import random


def generate(fights, spells, rolls, dice):
    print(fights)
    for i in range(fights):
        print('%d %d' % (random.randint(dice//2,dice), spells))
        print(' '.join(['%dd%d' % (random.randint(max(1,rolls//2),rolls), dice) for x in range(spells)]))


if __name__ == '__main__':
    generate(1000, 10, 20, 20)
