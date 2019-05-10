import requests
import re

"""
请利用requests库及python正则表达式模块爬取以下网址前10页的电影信息，并将其写到movies.txt文件中。
网址：https://movie.douban.com/top250
“movies.txt”文件的内容示例如下：
肖申克的救赎
导演: 弗兰克·德拉邦特 Frank Darabont
主演: 蒂姆·罗宾斯 Tim Robbins /...
1994
美国
犯罪 剧情
评分：9.6
--*---*---*---
霸王别姬
导演: 陈凯歌 Kaige Chen&nbsp
主演: 张国荣 Leslie Cheung / 张丰毅 Fengyi Zha...
1993
中国大陆 香港
剧情 爱情 同性
评分：9.6
--*---*---*---
这个杀手不太冷
导演: 吕克·贝松 Luc Besson&nbsp
主演: 让·雷诺 Jean Reno / 娜塔莉·波特曼 ...
1994
法国
剧情 动作 犯罪
评分：9.4
……
"""


# +++add your code here+++
def getHtml_fromUrl(url):
    try:
        response = requests.get(url)
        f = open("urlResult.txt", "w")
        f.write(response.text)
        f.close()
        return response.text
    except requests.exceptions.ConnectionError as c:
        print("连接失败   ----\n" + url)
    except requests.exceptions.Timeout as e:
        print("连接超时   ----\n" + url)
    except requests.exceptions.HTTPError as e:
        print("httperroe   ----\n" + url)


# regex +上? 表示非贪婪模式
# 匹配一个中文---> \u4e00-\u9fa5
def getContent(content, from_url):
    div_pattern = re.compile(
        r'<div class="info">.+?<span class="title">([\u4e00-\u9fa5]+)</span>.+?(<p class="">.+?</p>).+?(\d+\.+\d+).+?</li>',
        re.DOTALL)
    res = div_pattern.findall(content)
    f = open("movies.txt", "a+")
    for match in res:
        s = match[0] + "\n"
        temp1 = re.search(r"导演[\u4e00-\u9fa5|:|\s|\w|·|/]+", match[1])
        if temp1:
            s += temp1.group(0) + "\n"
        temp1 = re.search(r"主演.+?<br>", match[1])
        if temp1:
            s += temp1.group()[:-4] + "\n"

        m = re.search(r"(\d+).+?([\u4e00-\u9fa5]+).+?([\u4e00-\u9fa5|\s]+?)\n", match[1])
        if m:
            s += m.group(1) + "\n" + m.group(2) + "\n" + m.group(3) + "\n"
        s += "评分: " + match[2] + "\n"
        s += "--*---*---*---" + "\n"
        f.write(s)
    f.close()
    print(f"{from_url}  has done!")


if __name__ == '__main__':
    for i in range(0, 10):
        start_num = str(25 * i)
        url = f"https://movie.douban.com/top250?start={start_num}&filter="
        html = getHtml_fromUrl(url)
        getContent(html, url)
    print("all finish!")
