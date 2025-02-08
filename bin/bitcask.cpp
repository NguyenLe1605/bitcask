#include <iostream>
#include "CLI/CLI.hpp"
#include "version.h"

int main(int argc, char** argv) {
  CLI::App app{"bitcask"};

  app.add_flag_function(
      "-V",
      [](int count) {
        std::cout << "bitcask " << PROJECT_VERSION << std::endl;
      },
      "Print the version");

  auto get =
      app.add_subcommand("get", "Get the string value of a given string key");

  std::string key;
  get->add_option("key", key, "string key")->required();
  get->callback([&]() {
    std::cerr << "unimplemented\n";
    exit(-1);
  });

  std::string value;
  auto set =
      app.add_subcommand("set", "Set the value of a string key to a string");
  set->add_option("key", key, "string key")->required();
  set->add_option("value", value, "string value")->required();
  set->callback([&]() {
    std::cerr << "unimplemented\n";
    exit(-1);
  });

  auto rm = app.add_subcommand("rm", "Remove a given key");
  rm->add_option("key", key, "string key")->required();
  rm->callback([&]() {
    std::cerr << "unimplemented\n";
    exit(-1);
  });

  CLI11_PARSE(app, argc, argv);

  return 0;
}
