words = input("请输入")
a=b=c=0
for s in words:
    if s.isdigit():
        a += 1
    elif s.isalpha():
        b += 1
    else:
        c += 1
print("包含英文字符个数:", b)
print("包含数字字符个数:", a)
print("包含空格和其他字符个数:", c)

