#!/usr/bin/env python3
import os

def test():
    for i in range(10):
        os.system('./mal < test' + str(i) + '.in > test' + str(i) + '.out')
        os.system('./mal_brut < test' + str(i) + '.in > test' + str(i) + '_brut.out')
        os.system('diff -s test' + str(i) + '.out' + ' test' + str(i) + '_brut.out >> raport.out')

os.system('rm -f raport.out')
test()