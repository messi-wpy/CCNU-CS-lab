def add_Info(fileName):
    f=open(fileName,"r+")
    data=f.read()
    f.seek(0,0)
    f.write("千千阙歌\n陈慧娴\n")
    f.write(data)
    f.write("\n由环球唱片发行")
    f.close()

add_Info("歌词.txt")