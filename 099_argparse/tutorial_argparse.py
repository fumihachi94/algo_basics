import argparse
parser = argparse.ArgumentParser(
    prog='tutorial_argument.py',
    description='This module is a tutorial on the usage of `argparse`.',
    add_help=True
)

# 詳細表示させるかどうか
# action='store_ture'を指定することで値を指定できないようにしています
parser.add_argument('-v', '--verbose', action='store_true', help='show verbose message')
# 引数をコマンドラインに文字列として表示
parser.add_argument("name", help="input your name.")
# 引数を数値として扱う（下記例：入力値を2乗したものをコマンドラインに表示）
parser.add_argument("age", type=int, help="input your age.")

args = parser.parse_args()

if args.verbose:
    print("Your name :", args.name)
    print("Your age  : ", args.age)
else:
    print(args.name, args.age) 