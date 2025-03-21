#ifndef __UDPSERVER_HPP__
#define __UDPSERVER_HPP__

#include <atomic>
#include <thread>

class UDPServer {
public:
  UDPServer(int port);
  ~UDPServer();

  void start();
  void stop();

  void setPort(int port);

private:
  int               port;
  std::atomic<bool> running;
  std::thread       serverThread;

  void run();
};

#endif /* __UDPSERVER_HPP__ */
