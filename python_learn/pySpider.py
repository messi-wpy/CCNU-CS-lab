import requests
from bs4 import BeautifulSoup


def get(url):
    try:
        response = requests.get(url)
        print(response.url)
        return response.text
    except requests.exceptions.ConnectionError as c:
        print("连接失败   ----\n" + str(c))
    except requests.exceptions.Timeout as e:
        print("连接超时   ----\n" + str(e))
    except requests.exceptions.HTTPError as e:
        print("httperroe   ----\n" + str(e))


def getFromFile(fileName):
    f = open(fileName, "r")
    return f.read()


def saveToFile(fileName, text):
    f = open(fileName, "w")
    f.write(text)
    f.close()


def wreadHtml(url):
    soup = BeautifulSoup(get(url), "html.parser")
    ul = soup.body.div.find_next_sibling("div", id="wrapper").find("div", id="comments").ul
    commits = ul.find_all("span", class_="short")
    fold_commits = ul.find_next_sibling("ul").find_all("span", class_="short")
    list = []
    for commit in commits:
        list.append(commit.string)
    content = ''
    for fold in fold_commits:
        list.append(fold.string)
    for s in list:
        print(s)
        content += s + '\n'

    saveToFile("result.txt", content)


wreadHtml("https://book.douban.com/subject/1336330/comments/hot?p=1")
