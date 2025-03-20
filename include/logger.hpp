#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <ctime>
#include <iostream>
#include <mutex>
#include <string>

class Logger {
public:
  enum class Level {
    DEBUG,
    INFO,
    WARN,
    ERROR,
  };

  static Logger &getLogger() {
    static Logger logger;
    return logger;
  }

  void setLogLevel(Level level) { _logLevel = level; }

  void debug(const std::string &message) {
    log(Level::DEBUG, "DEBUG", message);
  }
  void info(const std::string &message) { log(Level::INFO, "INFO", message); }
  void warn(const std::string &message) { log(Level::WARN, "WARN", message); }
  void error(const std::string &message) {
    log(Level::ERROR, "ERROR", message);
  }

private:
  Level _logLevel = Level::INFO;

  Logger() = default;
  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

  void log(Level level, const std::string &levelstr,
           const std::string &message) {
    if (level < _logLevel)
      return;

    std::time_t now = std::time(nullptr);
    char timestr[20];
    std::strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S",
                  std::localtime(&now));

    std::cout << "[" << timestr << "] [" << levelstr << "] " << message
              << std::endl;
  }
};

#endif /* __LOGGER_HPP__ */
