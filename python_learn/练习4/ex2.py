"""
请编程自动生成给定的中文文本“cnText.txt”的词云图。
please fill in the code.
"""
import jieba
from wordcloud import WordCloud, STOPWORDS, ImageColorGenerator
import pickle
import matplotlib.pyplot as plt

def main():
    f = open("cnText.txt", "r", encoding="utf-8")
    # +++your code here+++
    words=jieba.lcut(f.read())
    txt=" ".join(words)
    image=plt.imread("cat.jpg")
    wc=WordCloud(background_color="white",mask=image,font_path="./simsun.ttf",max_words=2000)
    wc.generate(txt)
    img_colors = ImageColorGenerator(image)
    wc.recolor(color_func=img_colors)
    plt.imshow(wc)
    plt.axis("off")
    plt.show()
    wc.to_file("word_cloud.png")




if __name__ == '__main__':
  main()
