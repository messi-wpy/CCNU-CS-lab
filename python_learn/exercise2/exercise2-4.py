def move(n, a, b, c):
    if n == 1:
        print(a, '--->', c)
    else:
        move(n - 1, a, c, b)
        move(1, a, b, c)
        move(n - 1, b, a, c)


if __name__ == "__main__":
    num = input("请输入要移动的汉诺塔圆盘数:")
    move(int(num), "A", "B", "C")
