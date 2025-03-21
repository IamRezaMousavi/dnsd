#include "logger.hpp"

#include <ctime>
#include <iostream>

Logger &Logger::getLogger() {
  static Logger logger;
  return logger;
}

void Logger::setLogLevel(Level level) {
  _logLevel = level;
}

void Logger::debug(const std::string &message) {
  log(Level::DEBUG, "DEBUG", message);
}

void Logger::info(const std::string &message) {
  log(Level::INFO, "INFO", message);
}

void Logger::warn(const std::string &message) {
  log(Level::WARN, "WARN", message);
}

void Logger::error(const std::string &message) {
  log(Level::ERROR, "ERROR", message);
}

void Logger::log(Level level, const std::string &levelstr, const std::string &message) {
  if (level < _logLevel)
    return;

  std::time_t now = std::time(nullptr);
  char        timestr[20];
  std::strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

  std::cout << "[" << timestr << "] [" << levelstr << "] " << message << std::endl;
}
