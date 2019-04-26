import requests
from bs4 import BeautifulSoup
import threading


def get(url):
    try:
        response = requests.get(url)
        print(response.url)
        return response.text
    except requests.exceptions.ConnectionError as c:
        print("连接失败   ----\n" + url)
    except requests.exceptions.Timeout as e:
        print("连接超时   ----\n" + url)
    except requests.exceptions.HTTPError as e:
        print("httperroe   ----\n" + url)


def getFromFile(fileName):
    f = open(fileName, "r")
    return f.read()


def saveToFile(fileName, text):
    f = open(fileName, "a")
    f.write(text)
    f.close()


def wreadHtml(url, threadid="null"):
    soup = BeautifulSoup(get(url), "html.parser")
    ul = soup.body.div.find_next_sibling("div", id="wrapper").find("div", id="comments").ul
    commits = ul.find_all("span", class_="short")
    fold_commits = ul.find_next_sibling("ul")

    list = []
    for commit in commits:
        list.append(commit.string)
    content = ''
    if fold_commits is not None:
        fold_commits = fold_commits.find_all("span", class_="short")
        for fold in fold_commits:
            list.append(fold.string)
    threadLock.acquire()
    print(threadid + "------get lock-----")
    for s in list:
        if s is not None:
            print(s)
            content += s + '\n'
    saveToFile("result.txt", content)
    threadLock.release()
    print(threadid + "-----release lock----")


class mySprideThread(threading.Thread):
    url = ""

    threadId = ""

    def __init__(self, threadid, url):
        threading.Thread.__init__(self)
        self.url = url

        self.threadId = threadid

    def run(self):
        print("开启线程---" + self.threadId + "  "+self.url)
        wreadHtml(self.url, self.threadId)


threadLock = threading.Lock()
threads = []
url = "https://book.douban.com/subject/1336330/comments/hot?p="
for i in range(1, 4):
    id = str(i)
    thread = mySprideThread("thread " + id, url + id)
    thread.start()
    threads.append(thread)

for thread_ in threads:
    thread_.join()

print("------------完成爬取-----------")
