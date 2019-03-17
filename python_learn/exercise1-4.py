money = input("输入货币金额:")
currency = money[0:3]
num = float(money[3:])
rate = 6.78
if currency == "RMB":
    print("USD%.2f" %(num / rate))
else:
    print("RMB%.2f"% (num * rate))
