
import jieba


def main():
    txt = open("text.txt", "r", errors='ignore').read()
    count={}
    words=jieba.lcut(txt)
    for w in words:
        count[w]=count.get(w,0)+1

    items=list(count.items())
    items.sort(key=lambda x:x[1],reverse=True)
    for i in range(10):
        word, count = items[i]
        print("{0}:{1}".format(word, count))


if __name__ == '__main__':
    main()
