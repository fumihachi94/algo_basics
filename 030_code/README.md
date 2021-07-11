# トレンド楽曲のコード解析

## 準備

参考：
[たった3行のpythonで始めるSelenium入門 - Qiita](https://qiita.com/mastar_3104/items/0a1ce2bfa1d29287bc35)

selemiumを利用してスクレイピング

まずはこちらからドライバをダウンロード
[Getting started - ChromeDriver - WebDriver for Chrome](https://sites.google.com/a/chromium.org/chromedriver/getting-started)

現在利用しているChromeのバージョンが`91.0.4472.114`なのでそれにあったドライバをインストールします。

以下に保存し、zip解凍
```bash
/home/fumihachi/ws/lib/chromedriver_linux64
```

pipからseleniumのインストール
```
pip install selenium
```

### 動作テスト

以下のコードでChromeでGoogle検索ページが開かれればOKです。

```py
from selenium import webdriver
driver = webdriver.Chrome("/home/fumihachi/ws/lib/chromedriver_linux64/chromedriver")
driver.get("https://google.co.jp")
```



## コードの取得

```py
from selenium import webdriver
from selenium.webdriver.chrome.options import Options # オプションを使うために必要

option = Options()                          # オプションを用意
option.add_argument('--headless')           # ヘッドレスモードの設定を付与
driver = webdriver.Chrome("/home/fumihachi/ws/lib/chromedriver_linux64/chromedriver", options=option)

# <https://www.ufret.jp/>から楽曲を選択したURLを指定
url = "https://www.ufret.jp/song.php?data=56999"

driver.get(url)

# 簡単弾き設定をOFFにする：「簡単弾き:ON→OFF」
buttons = driver.find_elements_by_tag_name('button')
for button in buttons:
    if button.get_attribute("onclick") == "kantanon();":
        print("「簡単弾き:OFF」を選択")
        button.click()
        break

# コード要素だけを抽出
code_elem = driver.find_elements_by_tag_name('ruby')
for c in code_elem:
    print(c.text, end=' ')

print("")
```