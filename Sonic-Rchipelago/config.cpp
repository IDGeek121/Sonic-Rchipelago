#include "config.h"

namespace config {
  void read_config(struct config::Config* config) {
    const IniFile config_file = IniFile("mods/Sonic-Rrchipelago/config.ini");

    config->host = config_file.getString("general", "host", "");
    config->slot = config_file.getString("general", "slot", "");
    config->password = config_file.getString("general", "password", "");
  }
}
