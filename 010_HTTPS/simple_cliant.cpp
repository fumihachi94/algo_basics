/*--------------------------------------
TCP/IP クライアント側の基本プログラム
　(1)ソケットの生成
　(2)ソケットの接続
　(3)データの送信/受信
　(4)ソケットの切断
--------------------------------------*/

#include <iostream>
#include <sstream>
#include <memory.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF_LEN 128

int PORT     = 5000; 
int DOMAIN   = PF_INET;
int TYPE     = SOCK_STREAM; 
int PROTOCOL = 0;

int main(){
    // ソケットの生成
    auto sockfd = socket(DOMAIN, TYPE, PROTOCOL);
    if (sockfd < 0){
        std::perror("[Error] Failed to initialize a socket.");
        exit(EXIT_FAILURE);
    }

    // ソケットオプションの設定
    int optval = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
        std::perror("[Error] Failed to setsocket.");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // 通信ポート・アドレスの設定
    struct sockaddr_in client_addr;    
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    client_addr.sin_port = htons(PORT);

    // ソケットをサーバーに接続
    if(connect(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0){
        std::perror("[Error] Failed to connect.");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    auto body = std::string("Update HTTP Connect.");
    auto send_meg = std::string("");
    send_meg.append("GET localhost HTTP/1.1\r\n");
    send_meg.append("Host: 127.0.0.1:5000\r\n");
    send_meg.append("\r\n");
    write(sockfd, send_meg.c_str(), strlen(send_meg.c_str()));

    // 受信が終わるまでループ
    while(1) {
        char buf[BUF_LEN];
        int read_size;
        read_size = read(sockfd, buf, BUF_LEN);

        if (read_size > 0) {
            std::cout << read_size << std::endl;
            write(1, buf, read_size);
        }
        else {
            break;
        }
    }

    // ソケットをクローズ
    close(sockfd);
    exit(EXIT_SUCCESS);
}










