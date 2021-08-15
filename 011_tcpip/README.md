# TCP/IP 入門

「LINUXで動かしながら学ぶTCP/IPネットワーク入門」の内容になります。

この本ではLinuxの**Network Namespace**という機能を使って実際に手を動かしながら解説してくれています。

> - コマンド中の`<>`はユーザー任意の定数または変数であることを示しています。


# Index

<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [TCP/IP 入門](#tcpip-入門)
- [Index](#index)
  - [Network Namespace (netns)](#network-namespace-netns)
      - [Network Namespaceを作る](#network-namespaceを作る)
      - [Network Namespaceの一覧表示](#network-namespaceの一覧表示)
      - [Network Namespace内でコマンド実行](#network-namespace内でコマンド実行)
      - [Network Namespace内に入る/出る](#network-namespace内に入る出る)
    - [Network Namespaceを繋げる](#network-namespaceを繋げる)
      - [仮想ネットワークIF (veth-IF) を作成](#仮想ネットワークif-veth-if-を作成)
      - [veth IF をNetwork Namespaceに紐付ける](#veth-if-をnetwork-namespaceに紐付ける)
      - [IPアドレスの付与](#ipアドレスの付与)
      - [ネットワークIFのUP/DOWN](#ネットワークifのupdown)
  - [Linux command for Network](#linux-command-for-network)
      - [IPアドレスの確認](#ipアドレスの確認)
      - [ルーティングテーブルの確認](#ルーティングテーブルの確認)
      - [ネットワークインターフェースの確認](#ネットワークインターフェースの確認)
      - [ping送信](#ping送信)

<!-- /code_chunk_output -->

## Network Namespace (netns)

```sh
$ ip netns help
Usage: ip netns list
       ip netns add NAME
       ip netns set NAME NETNSID
       ip [-all] netns delete [NAME]
       ip netns identify [PID]
       ip netns pids NAME
       ip [-all] netns exec [NAME] cmd ...
       ip netns monitor
       ip netns list-id
```

#### Network Namespaceを作る

```sh
$ sudo ip netns add <$NS_NAME>
```

#### Network Namespaceの一覧表示

```sh
$ ip netns list
```

#### Network Namespace内でコマンド実行

e.g.) IPアドレスを確認する場合

```sh
$ sudo ip netns exec <ns-name> ip address show
```

#### Network Namespace内に入る/出る

```sh
# 入る時
$ sudo ip netns exec <ns-name> bash
# 出る時
> exit // Ctrl+Dでも抜けられる
```

### Network Namespaceを繋げる

#### 仮想ネットワークIF (veth-IF) を作成

veth (Virtual Ethernet Device)という仮想ネットワークIFを利用します。

```sh
$ sudo ip link add <net-if1> type veth peer name <net-if2>
```

#### veth IF をNetwork Namespaceに紐付ける

```sh
$ sudo ip link set <net-if> netns <ns-name>
```

#### IPアドレスの付与

veth IF をNetwork Namespaceに紐付けただけではLANケーブルで接続しただけの状態です。
IPを使って通信させるためにIP付与が必要になります。

```sh
$ sudo ip netsn exec <ns-name> ip address add <192.0.2.1/24> dev <net-if>
```

#### ネットワークIFのUP/DOWN

IPアドレスを付与してもまだ通信はできません。ネットワークIFには、UP/DOWNの状態がありUPでないと使えません。

```sh
# UPに設定
$ sudo ip netns exec <ns-name> ip link set <net-if> up
# DOWNに設定
$ sudo ip netns exec <ns-name> ip link set <net-if> down
```




---

## Linux command for Network

#### IPアドレスの確認

```sh
$ ip address show
```

#### ルーティングテーブルの確認

```sh
$ ip route show
```

#### ネットワークインターフェースの確認

```sh
$ ip link show
```

#### ping送信

e.g.) IPアドレス`8.8.8.8`に向けてPingを3回送信する場合

```sh
$ ping -c 3 8.8.8.8
PING 8.8.8.8 (8.8.8.8) 56(84) bytes of data.
64 bytes from 8.8.8.8: icmp_seq=1 ttl=116 time=7.89 ms
64 bytes from 8.8.8.8: icmp_seq=2 ttl=116 time=7.33 ms
64 bytes from 8.8.8.8: icmp_seq=3 ttl=116 time=7.59 ms

--- 8.8.8.8 ping statistics ---
3 packets transmitted, 3 received, 0% packet loss, time 2002ms
rtt min/avg/max/mdev = 7.339/7.610/7.894/0.248 ms
```

送信元のIPアドレスを明示的に指定したい場合
（基本的に送信元IPアドレスはOSがSource Address Selectionという仕組みで自動判別してくれるため不要です）

```sh
$ ping -c 3 8.8.8.8 -I <192.0.2.1>
```


