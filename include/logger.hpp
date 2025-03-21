#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <string>

class Logger {
public:
  enum class Level {
    DEBUG,
    INFO,
    WARN,
    ERROR,
  };

  static Logger &getLogger();

  void setLogLevel(Level level);

  void debug(const std::string &message);
  void info(const std::string &message);
  void warn(const std::string &message);
  void error(const std::string &message);

private:
  Level _logLevel = Level::INFO;

  Logger()                          = default;
  Logger(const Logger &)            = delete;
  Logger &operator=(const Logger &) = delete;

  void log(Level level, const std::string &levelstr, const std::string &message);
};

#endif /* __LOGGER_HPP__ */
