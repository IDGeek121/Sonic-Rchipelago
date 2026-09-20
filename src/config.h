#ifndef CONFIG_H
#define CONFIG_H

#include <IniFile.hpp>

namespace config {
  struct Config {
    std::string host;
    std::string slot;
    std::string password;
  };

  void read_config(struct config::Config* config);
}

#endif
