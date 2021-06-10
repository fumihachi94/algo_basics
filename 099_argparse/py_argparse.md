# Argparseの使い方
argparseはPythonの標準ライブラリの一つで、コマンドライン引数の解析モジュールです。
[Argparse チュートリアル — Python 3.9.1rc1 ドキュメント](https://docs.python.org/ja/3/howto/argparse.html#id1)

>**【!注意】**
コマンドラインで実行する場合とJupyter Notebookで実行する場合では、書き方が変わってきます！
以下を参考にしてJupyter Notebookで動作する書き方で以下記述していきます。<
[Jupyter lab / notebookで argparseそのままで実行する方法 - Qiita](https://qiita.com/uenonuenon/items/09fa620426b4c5d4acf9)

>**パーサ(parser)とは？**
パーサとは、構文解析を行うためのプログラムの総称である。
また、自然言語処理においては、自然言語における文法上の構造を解析するためにパーサが利用される。
[parserとは何？ Weblio辞書](https://www.weblio.jp/content/parser)

## 基礎編

```py
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("echo", help="echo the string you use here")
args = parser.parse_args()
print(args.echo)
```

コマンドライン引数で指定した文字列をそのまま表示するようになりました。
```bash
$ python3 tutorial_argparse.py hoge
hoge
```

add_argument()メソッド：プログラムが受け付けるコマンドラインオプションを指定する
上記例では`echo`としました。

コマンドラインオプションを指定せずに実行すると以下のようなエラーとなります。

```bash
$ python3 tutorial_argparse.py 
usage: tutorial_argparse.py [-h] echo
tutorial_argparse.py: error: the following arguments are required: echo
```

`-h [--help]`で参照すると、設定した`echo`オプションに対して説明を見ることができます。

```bash
$ python3 tutorial_argparse.py -h
usage: tutorial_argparse.py [-h] echo

positional arguments:
  echo        echo the string you use here

optional arguments:
  -h, --help  show this help message and exit
```



