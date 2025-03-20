#ifndef __UDPSERVER_HPP__
#define __UDPSERVER_HPP__

#include <atomic>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

#include <string>

#include "dns.hpp"
#include "logger.hpp"

#define BUFFER_SIZE 1024 // 1 kB

class UDPServer {
public:
  UDPServer(int port) : port(port), running(false) {}
  ~UDPServer() { stop(); }

  void start() {
    running = true;
    serverThread = std::thread(&UDPServer::run, this);
  }

  void stop() {
    if (running) {
      running = false;
      if (serverThread.joinable()) {
        serverThread.join();
      }
    }
  }

private:
  int port;
  std::atomic<bool> running;
  std::thread serverThread;

  void run() {
    Logger &logger = Logger::getLogger();

    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_len = sizeof(clientAddr);
    uint8_t buffer[BUFFER_SIZE];

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
      logger.error("Socket creation failed: " + std::string(strerror(errno)));
      return;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&serverAddr, addr_len) < 0) {
      logger.error("Bind failed: " + std::string(strerror(errno)));
      close(sockfd);
      return;
    }

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 100000; // 100 ms

    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) <
        0) {
      std::cerr << "Error setting socket timeout" << std::endl;
      close(sockfd);
      return;
    }

    logger.info("UDP server is running on port " + std::to_string(port) +
                "...");

    while (running) {
      ssize_t received = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,
                                  (struct sockaddr *)&clientAddr, &addr_len);
      if (!running)
        break;

      if (received < 0) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
          // timeout without received data
          continue;
        }
        logger.error("Receive failed: " + std::string(strerror(errno)));
        break;
      }

      DNS dnspacket = parseDNS(buffer);
      std::cout << dnspacket << std::endl;

      // std::string response = "Reza";
      // sendto(sockfd, response.c_str(), response.size(), 0,
      //        (struct sockaddr *)&clientAddr, addr_len);
    }
    close(sockfd);
    logger.info("UDP server is shutting down");
  }
};

#endif /* __UDPSERVER_HPP__ */
