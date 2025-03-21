#include "argparser.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>

template<typename T>
Option<T>::Option(const std::string &shortname, const std::string &longname, const std::string &help, T defaultValue)
    : shortname(shortname), longname(longname), help(help), value(defaultValue) {}

template<typename T>
T Option<T>::getValue() const {
  return value;
}

template<typename T>
void Option<T>::setValueFromString(const std::string &valueStr) {
  std::istringstream iss(valueStr);
  iss >> value;
  if (iss.fail()) {
    throw std::runtime_error("Invalid value for option: " + longname);
  }
}

template<typename T>
bool Option<T>::requiresValue() const {
  return true;
}

template<typename T>
std::string Option<T>::getLongName() const {
  return longname;
}

template<typename T>
std::string Option<T>::getHelp() const {
  return help;
}

Option<bool>::Option(const std::string &shortname, const std::string &longname, const std::string &help, bool defaultValue)
    : shortname(shortname), longname(longname), help(help), value(defaultValue) {}

bool Option<bool>::getValue() const {
  return value;
}

void Option<bool>::setValueFromString(const std::string &valueStr) {
  (void)valueStr;
  value = true; // For boolean flags, just set to true when the option is present
}

bool Option<bool>::requiresValue() const {
  return false;
}

std::string Option<bool>::getLongName() const {
  return longname;
}

std::string Option<bool>::getHelp() const {
  return help;
}

ArgParser::ArgParser(const std::string &appname, const std::string &description): appname(appname), description(description) {}

ArgParser::~ArgParser() {
  for (auto &pair : options) {
    delete pair.second;
  }
}

template<typename T>
void ArgParser::add_option(const std::string &shortname, const std::string &longname, const std::string &help, T defaultValue) {
  Option<T> *option  = new Option<T>(shortname, longname, help, defaultValue);
  options[shortname] = option;
  options[longname]  = option;
}

void ArgParser::parse(int argc, char **argv) {
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg.substr(0, 2) == "--") {
      std::string longname = arg.substr(2);
      auto        it       = options.find(longname);
      if (it != options.end()) {
        OptionBase *option = it->second;
        if (option->requiresValue()) {
          if (i + 1 < argc) {
            option->setValueFromString(argv[++i]);
          } else {
            throw std::runtime_error("Option " + longname + " requires a value.");
          }
        } else {
          option->setValueFromString("true");
        }
      } else {
        throw std::runtime_error("Unknown option: " + longname);
      }
    } else if (arg[0] == '-') {
      std::string shortname = arg.substr(1);
      auto        it        = options.find(shortname);
      if (it != options.end()) {
        OptionBase *option = it->second;
        if (option->requiresValue()) {
          if (i + 1 < argc) {
            option->setValueFromString(argv[++i]);
          } else {
            throw std::runtime_error("Option " + shortname + " requires a value.");
          }
        } else {
          option->setValueFromString("true");
        }
      } else {
        throw std::runtime_error("Unknown option: " + shortname);
      }
    } else {
      throw std::runtime_error("Unexpected argument: " + arg);
    }
  }
}

template<typename T>
T ArgParser::get_value(const std::string &name) const {
  auto it = options.find(name);
  if (it != options.end()) {
    Option<T> *option = dynamic_cast<Option<T> *>(it->second);
    if (option) {
      return option->getValue();
    } else {
      throw std::runtime_error("Type mismatch for option: " + name);
    }
  } else {
    throw std::runtime_error("Option not found: " + name);
  }
}

void ArgParser::print_help() const {
  std::cout << appname << "\n\n";
  std::cout << description << "\n\n";
  std::cout << "Options:\n";
  for (const auto &pair : options) {
    if (pair.first.length() == 1) { // Short name
      OptionBase *option = pair.second;
      std::cout << "  -" << pair.first << ", --" << option->getLongName() << "\n";
      std::cout << "        " << option->getHelp() << "\n";
    }
  }
}

// Explicit template instantiation for common types
template class Option<int>;
template class Option<float>;
template class Option<std::string>;
template class Option<bool>;

template void ArgParser::add_option<int>(const std::string &, const std::string &, const std::string &, int);
template void ArgParser::add_option<float>(const std::string &, const std::string &, const std::string &, float);
template void ArgParser::add_option<std::string>(const std::string &, const std::string &, const std::string &, std::string);
template void ArgParser::add_option<bool>(const std::string &, const std::string &, const std::string &, bool);

template int         ArgParser::get_value<int>(const std::string &) const;
template float       ArgParser::get_value<float>(const std::string &) const;
template std::string ArgParser::get_value<std::string>(const std::string &) const;
template bool        ArgParser::get_value<bool>(const std::string &) const;
