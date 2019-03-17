n = int(input("输入数字n:"))


def _func(num):
    if num == 0 or num == 1:
        return num
    return num * _func(num - 1)


result = 0
for i in range(1, n + 1):
    result += _func(i)

print("1到n的阶乘为:", result)
