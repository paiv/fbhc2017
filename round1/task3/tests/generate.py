#!/usr/bin/env python
from __future__ import print_function
from random import randint as rr


def generate(tests, ncities, mroads, korders):
    print(tests)
    for i in range(tests):
        print('%d %d %d' % (ncities, mroads, korders))
        for mi in range(mroads):
            print('%d %d %d' % (rr(1,ncities), rr(1,ncities), rr(1,1000)))
        for ki in range(korders):
            f = rr(1,ncities)
            while True:
                t = rr(1,ncities)
                if t != f:
                    break
            print('%d %d' % (f, t))


if __name__ == '__main__':
    import sys
    ntests = 1
    if len(sys.argv) > 1:
        ntests = int(sys.argv[1])

    generate(ntests, 100, 100, 100)
