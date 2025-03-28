#include <csignal>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include "argparser.hpp"
#include "db.hpp"
#include "logger.hpp"
#include "udpserver.hpp"

#define APPNAME "DNSD"
#define VERSION "v0.1.0"

#define PORT 5353
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
  ArgParser parser(APPNAME " " VERSION, "This is a simple dns server.");

  std::string dbFile = "db.conf";
  int         port   = PORT;

  parser.add_option<std::string>("f", "file", "Dns records file name", dbFile);
  parser.add_option<int>("p", "port", "Port to listening", port);
  parser.add_option<bool>("h", "help", "Show help message", false);

  try {
    parser.parse(argc, argv);

    if (parser.get_value<bool>("h")) {
      parser.print_help();
      exit(EXIT_SUCCESS);
    }

    dbFile = parser.get_value<std::string>("f");
    port   = parser.get_value<int>("p");

  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    exit(EXIT_FAILURE);
  }

  Logger &logger = Logger::getInstance();

  server.setPort(port);

  logger.info("Reading db file from " + dbFile);
  DB::getInstance(dbFile);

  std::signal(SIGINT, signalHandler);

  server.start();

  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    // logger.info("tick");
  }

  return EXIT_SUCCESS;
}
