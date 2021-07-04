
以下のサイトを参考にC++でHTTPサーバーを勉強する。

[【C++】C++でHTTPサーバを実装してみた - dasukoの技術ブログ](https://dasuko.hatenadiary.jp/entry/cpp_http-server)
[[C言語] HTTPクライアントを作ってみる - Qiita](https://qiita.com/edo_m18/items/cef278d0c14d1371db3b)

サーバープログラムの基礎的な部分を分かりやすく解説してくれているこちらのサイトが非常に参考になりました。
- [Socket()とかBind()とかを理解する - Qiita](https://qiita.com/Michinosuke/items/0778a5344bdf81488114)
- [TCPプログラミング](https://research.nii.ac.jp/~ichiro/syspro98/) (国立情報学研究所 佐藤一郎教授のHPです)

---
## 目次

<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [目次](#目次)
- [クライアント](#クライアント)
- [サーバー](#サーバー)
  - [sockaddr_in `struct`](#sockaddr_in-struct)
  - [socket() `int`](#socket-int)
  - [setsockopt() `int`](#setsockopt-int)
  - [close() `int`](#close-int)
  - [bind() `int`](#bind-int)
  - [Accept() `int`](#accept-int)
- [参考サイト一覧](#参考サイト一覧)
- [用語一覧](#用語一覧)

<!-- /code_chunk_output -->


---
## クライアント




## サーバー

### sockaddr_in `struct`

必要なインクードと構造体の中身

```cpp
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* 上記のスーパーセット */

struct sockaddr_in {
    sa_family_t    sin_family; /* address family: AF_INET */
    in_port_t      sin_port;   /* port in network byte order */
    struct in_addr sin_addr;   /* internet address */ 
};
```

[Man page of IP](https://linuxjm.osdn.jp/html/LDP_man-pages/man7/ip.7.html)

### socket() `int`

socketは通信のためのエンドポイントを作成するコマンド。
```cpp
int socket(int domain, int type, int protocol);
```

**返り値**

>成功した場合、新しいソケットのファイルディスクリプターを返す。 エラーが発生した場合は -1 を返し、 errno を適切に設定する。

- [ファイルディスクリプタについて理解する - Qiita](https://qiita.com/toshihirock/items/78286fccf07dbe6df38f)

**使用例**

```cpp
#include <sys/types.h> // *1
#include <sys/socket.h>

auto sock = socket(AF_INET, SOCK_STREAM, 0);
// AF_INET : IPv4 Internet Protocol
// SOCK_STRAM : 順序性と信頼性があり、双方向の、接続された バイトストリーム (byte stream) を提供する。 帯域外 (out-of-band) データ転送メカニズムもサポートされる。
// protocol = 0 : 第三パラメータにゼロを指定した場合はOSが自動的に適切なプロトコル（通常はストリームソケットの場合はIPPROTO_TCP、データグラムソケットの場合はIPPROTO_UDP）を設定してくれます。 
```

*1 : POSIX.1 では <sys/types.h> のインクルードは必須とされておらず、 Linux ではこのヘッダーファイルは必要ではない。 しかし、歴史的には、いくつかの実装 (BSD 系) でこのヘッダーファイルが 必要であり、移植性が必要なアプリケーションではこのファイルを インクルードするのが賢明であろう。


参考サイト：
- [Man page of SOCKET](https://linuxjm.osdn.jp/html/LDP_man-pages/man2/socket.2.html)


### setsockopt() `int`

ソケットのオプションの設定と取得を行なう。
必要なインクードと構造体の中身は以下。

```cpp
#include <sys/types.h> 
#include <sys/socket.h>

int setsockopt (
    int __fd, // socket()で生成したファイルディスクリプターを指定
    int __level, // SOL_SOCKETを指定
    int __optname, // socketオプションを指定(*1)
    const void *__optval,
    socklen_t __optlen
);
// return [0: Success, 1: Failure]
```

*1) socketオプションは[Man page of SOCKET](https://linuxjm.osdn.jp/html/LDP_man-pages/man7/socket.7.html)を参照。

**使用例**

```cpp
int optval = 1;
if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
    std::cout << "Failed to setsocket" << std::endl;
    close(sock);
    return 1;
}
```

- [Man page of GETSOCKOPT](https://linuxjm.osdn.jp/html/LDP_man-pages/man2/getsockopt.2.html)


### close() `int`

C言語でファイルをクローズするための低水準入出力関数。
必要なインクードと構造体の中身は以下。

```cpp
#include <unistd.h>

int close(int fd)
// return [0: Success, 1: Failure]
```

参考サイト：
- [close()](http://cgengo.sakura.ne.jp/close.html)


### bind() `int`

生成したソケットに通信ポートやアドレスを紐付ける (ソケットに名前をつけると言うらしい)。
必要なインクードと構造体の中身は以下。

```cpp
#include <sys/types.h> 
#include <sys/socket.h>

int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
// return : [0: Success, 1: Failure]
```
[Man page of BIND](https://linuxjm.osdn.jp/html/LDP_man-pages/man2/bind.2.html)


### Accept() `int`

接続待ちソケットのキューから先頭の接続要求を取り出して、接続済みソケットのファイルディスクリプターを返す。
必要なインクードと構造体の中身は以下。

```cpp
#include <sys/types.h>
#include <sys/socket.h>

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
// return [0~ : Success(file descriptor) -1: Failure]
```

[Man page of ACCEPT](https://linuxjm.osdn.jp/html/LDP_man-pages/man2/accept.2.html)




<!-- =============================- -->
---
<!-- =============================- -->

## 参考サイト一覧
- setsockopt()でソケットオプションSO_REUSEADDRを指定するわけ。
  - [TCPを使う(サーバ、SO_REUSEADDR):Geekなぺーじ](https://www.geekpage.jp/programming/linux-network/so_reuseaddr.php)
- std:ostringstreamについて
  - [文字列ストリーム | Programming Place Plus　C++編【標準ライブラリ】　第２９章](https://programming-place.net/ppp/contents/cpp/library/029.html)
- AF_INETとPF_INETの違いについて
  - [PF_INETとAF_INETの微妙な違い – 日々、コレ勉強](https://www.khstasaba.com/?p=401)

## 用語一覧

|Terms|English|Explanation|Link|
|---|---|---|---|
|ネットワークバイトオーダー|Network Byte Order|データの記録・転送の順序のこと。TCP/IPでは最上位バイトから下位バイトに向けて記述するビッグエンディアンが用いられる。 |[ネットワークバイトオーダー（network byte order）とは - IT用語辞典 e-Words](https://e-words.jp/w/%E3%83%8D%E3%83%83%E3%83%88%E3%83%AF%E3%83%BC%E3%82%AF%E3%83%90%E3%82%A4%E3%83%88%E3%82%AA%E3%83%BC%E3%83%80%E3%83%BC.html)|
|ビッグエンディアン |Big Endian | 最上位ビットの属するバイトを低位アドレスへ格納していく方式|[バイトオーダ - ビッグエンディアン/リトルエディアン](http://www.ertl.jp/~takayuki/readings/info/no05.html)
|リトルエンディアン |Little Endian |最下位ビットの属するバイトを低位アドレスへ格納していく方式|[バイトオーダ - ビッグエンディアン/リトルエディアン](http://www.ertl.jp/~takayuki/readings/info/no05.html)
| | |


