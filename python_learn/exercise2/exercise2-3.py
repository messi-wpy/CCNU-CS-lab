if __name__=="__main__":
    print("输入一个五位数")
    num=input()
    i=0
    j=len(num)-1

    while i<j:
        if num[i] != num[j]:
            print("不是回文数")
            quit()
        else:
            i+=1
            j-=1
    print("是回文")




