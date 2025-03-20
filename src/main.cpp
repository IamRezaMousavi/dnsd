#include <csignal>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include "config.hpp"
#include "logger.hpp"
#include "udpserver.hpp"

#define PORT 8080
UDPServer server(PORT);

void signalHandler(int signum) {
  switch (signum) {
  case SIGINT:
    server.stop();
    exit(EXIT_SUCCESS);
    break;

  default:
    break;
  }
}

int main(int argc, char **argv) {
  Logger &logger = Logger::getLogger();

  logger.info("Reading config file");
  Config config("db.conf");

  std::signal(SIGINT, signalHandler);

  server.start();

  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    // logger.info("tick");
  }

  return EXIT_SUCCESS;
}
