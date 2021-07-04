#include <iostream>
#include <sstream>
#include <memory.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <unistd.h>

#define LISTEN_BACKLOG 50

int PORT     = 5000; 
int DOMAIN   = PF_INET;
int TYPE     = SOCK_STREAM; 
int PROTOCOL = 0;
/* 
 - SOCK_STREAM->TCP socket
 - SOCK_DGRAM ->UDP socket
 - SOCK_RAW   ->RAW socket
*/


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
    struct sockaddr_in serv_addr;    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);

    // ソケットにアドレスを結びつける
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::perror("[Error] Failed to bind.");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // コネクト要求をいくつまで待つか (LISTEN_BACKLOG) を設定
    if (listen(sockfd, LISTEN_BACKLOG) == -1){
        std::perror("[Error] Failed to listen.");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    auto body = std::string("Hello HTTP Connect.");
    auto response = std::string("");
    std::ostringstream oss;
    
    oss << "Content-Length: " << 20 << "\r\n";

    response.append("HTTP/1.1 200 OK\r\n");
    response.append("Content-Type: text/html; charset=UTF-8\r\n");
    response.append(oss.str());
    response.append("Connection: Keep-Alive\r\n");
    response.append("\r\n");
    response.append(body);

    std::cout << "response:" << response << std::endl;

    char inbuf[2048];

    while (true) {
        // コネクト要求を待つ
        auto connfd = accept(sockfd, nullptr, nullptr);
        if (connfd < 0) {
            std::perror("[Error] Failed to accept.");
            break;
        }else{
            std::cout << "Acccess!\n"; 
        }

        memset(inbuf, 0, sizeof(inbuf));
        recv(connfd, inbuf, sizeof(inbuf), 0);

        if (send(connfd, response.c_str(), response.length(), 0) < 0) {
            std::perror("[Error] Failed to send.");
        }
    }

    // ソケットをクローズ
    close(sockfd);
    exit(EXIT_SUCCESS);
}