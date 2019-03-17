num_1 = int (input("请输入数字:"))
num_2 = int (input("请在输入一个数字"))
a=num_1*num_2
if num_1>=num_2:
    b=num_1
    c=num_2
else:
    b=num_2
    c=num_1

while b % c != 0:
    temp = c
    c = b % c
    b = temp

print("最大公约数:", c)
print("最小公倍数:", a/c)
