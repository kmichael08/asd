import random

def make_test(target):
    m = random.randint(3, 8)
    n = random.randint(2, 8)

    target.write(str(m) + ' ' + str(n) +'\n')

    for i in range(m):
        for i in range(n):
            a = random.randint(1, 8)
            target.write(str(a) + ' ')
        target.write('\n')


for i in range(10):
    target = open('test' + str(i) +'.in', 'w')
    make_test(target)