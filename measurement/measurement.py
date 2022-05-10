import sys

with open(sys.argv[2]) as f:
    std_log = f.read().split('\n')
with open(sys.argv[3]) as f:
    ft_log = f.read().split('\n')
with open(sys.argv[4]) as f:
    test_log = f.read().split('\n')

print(f'--------{sys.argv[1]}--------')

std_c = len(std_log)
ft_c = len(ft_log)
test_c = len(test_log)

if(std_c != ft_c and
   std_c != test_c and
   ft_c != test_c):
    print('Error')
    exit

green = '\033[32m'
red = '\033[31m'
reset = '\033[0m'

for i in range(len(std_log) - 1):
    std_res = int(std_log[i])
    ft_res = int(ft_log[i])
    res = red + 'NG!' + reset
    if ft_res <= (std_res * 20):
        res = green + 'OK!' + reset
    print(f'{res} : {test_log[i]}')

print()
