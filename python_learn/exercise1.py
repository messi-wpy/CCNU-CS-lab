

def add_num(fileName):
    f=open(fileName,"r+",encoding="utf-8")
    words=f.read()
    f.seek(0,0)
    f.write("1.")
    line=2
    for i in range(0,len(words)):
        f.write(words[i])
        if words[i]=='\n':
            f.write(str(line)+".")
            line+=1
    f.close()

add_num("text1.txt")
