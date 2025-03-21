#ifndef __ARGPARSER_HPP__
#define __ARGPARSER_HPP__

#include <map>
#include <string>

class OptionBase {
public:
  virtual ~OptionBase()                                            = default;
  virtual void        setValueFromString(const std::string &value) = 0;
  virtual bool        requiresValue() const                        = 0;
  virtual std::string getLongName() const                          = 0;
  virtual std::string getHelp() const                              = 0;
};

template<typename T>
class Option: public OptionBase {
public:
  Option(const std::string &shortname, const std::string &longname, const std::string &help, T defaultValue = T());

  T           getValue() const;
  void        setValueFromString(const std::string &valueStr) override;
  bool        requiresValue() const override;
  std::string getLongName() const override;
  std::string getHelp() const override;

private:
  std::string shortname;
  std::string longname;
  std::string help;
  T           value;
};

// Specialization for bool (flags)
template<>
class Option<bool>: public OptionBase {
public:
  Option(const std::string &shortname, const std::string &longname, const std::string &help, bool defaultValue = false);

  bool        getValue() const;
  void        setValueFromString(const std::string &valueStr) override;
  bool        requiresValue() const override;
  std::string getLongName() const override;
  std::string getHelp() const override;

private:
  std::string shortname;
  std::string longname;
  std::string help;
  bool        value;
};

class ArgParser {
public:
  ArgParser(const std::string &appname, const std::string &description);
  ~ArgParser();

  template<typename T>
  void add_option(const std::string &shortname, const std::string &longname, const std::string &help, T defaultValue = T());

  void parse(int argc, char **argv);

  template<typename T>
  T get_value(const std::string &name) const;

  void print_help() const;

private:
  std::string                         appname;
  std::string                         description;
  std::map<std::string, OptionBase *> options;
};

#endif /* __ARGPARSER_HPP__ */
