#include <gtest/gtest.h>
#include <reproc++/run.hpp>
#include <system_error>
#include "version.h"

#define BITCASK_BINARY ("../bin/bitcask")

namespace {
std::pair<int, std::error_code> run_cli(const std::vector<std::string>& argv,
                                        std::string& output,
                                        std::string& error);
}

TEST(BasicCliTests, CliNoArgs) {
  int status = -1;
  std::error_code ec;
  std::string output;
  std::string error;

  std::tie(status, ec) = run_cli({BITCASK_BINARY}, output, error);
  ASSERT_TRUE(!ec) << ec.message();
  ASSERT_TRUE(status == 0);
}

TEST(BasicCliTests, CliVersion) {
  std::vector<std::string> argv{BITCASK_BINARY, "-V"};
  int status = -1;
  std::error_code ec;
  std::string output;
  std::string error;

  std::tie(status, ec) = run_cli(argv, output, error);

  ASSERT_TRUE(!ec) << ec.message();
  ASSERT_TRUE(status == 0);
  ASSERT_TRUE(output.find(PROJECT_VERSION) != output.npos);
}

TEST(BasicCliTests, CliGet) {
  // TEST to test how to capture stderr
  std::vector<std::string> argv{
      BITCASK_BINARY,
      "get",
      "key1",
  };
  int status = -1;
  std::error_code ec;
  std::string output;
  std::string error;

  std::tie(status, ec) = run_cli(argv, output, error);

  ASSERT_TRUE(status != 0);
  ASSERT_TRUE(error.find("unimplemented") != error.npos);
}

TEST(BasicCliTests, CliSet) {
  std::vector<std::string> argv{BITCASK_BINARY, "set", "key1", "value1"};
  int status = -1;
  std::error_code ec;
  std::string output;
  std::string error;

  std::tie(status, ec) = run_cli(argv, output, error);

  ASSERT_TRUE(status != 0);
  ASSERT_TRUE(error.find("unimplemented") != error.npos);
}

TEST(BasicCliTests, CliRm) {
  std::vector<std::string> argv{
      BITCASK_BINARY,
      "rm",
      "key1",
  };
  int status = -1;
  std::error_code ec;
  std::string output;
  std::string error;

  std::tie(status, ec) = run_cli(argv, output, error);

  ASSERT_TRUE(status != 0);
  ASSERT_TRUE(error.find("unimplemented") != error.npos);
}

TEST(BasicCliTests, CliInvalidGet) {
  std::vector<std::vector<std::string>> argvs{{
                                                  BITCASK_BINARY,
                                                  "get",
                                              },
                                              {
                                                  BITCASK_BINARY,
                                                  "get",
                                                  "extra",
                                                  "field",
                                              }

  };
  int status = -1;
  std::error_code ec;
  std::string output;
  std::string error;

  for (auto& argv : argvs) {
    std::tie(status, ec) = run_cli(argv, output, error);
    ASSERT_TRUE(status != 0);
  }
}

TEST(BasicCliTests, CliInvalidSet) {
  std::vector<std::vector<std::string>> argvs{{
                                                  BITCASK_BINARY,
                                                  "set",
                                              },
                                              {
                                                  BITCASK_BINARY,
                                                  "set",
                                                  "missing_field",
                                              },
                                              {
                                                  BITCASK_BINARY,
                                                  "set",
                                                  "extra",
                                                  "extra",
                                                  "field",
                                              }

  };
  int status = -1;
  std::error_code ec;
  std::string output;
  std::string error;

  for (auto& argv : argvs) {
    std::tie(status, ec) = run_cli(argv, output, error);
    ASSERT_TRUE(status != 0);
  }
}

TEST(BasicCliTests, CliInvalidRm) {
  std::vector<std::vector<std::string>> argvs{{
                                                  BITCASK_BINARY,
                                                  "rm",
                                              },
                                              {
                                                  BITCASK_BINARY,
                                                  "rm",
                                                  "extra",
                                                  "field",
                                              }

  };
  int status = -1;
  std::error_code ec;
  std::string output;
  std::string error;

  for (auto& argv : argvs) {
    std::tie(status, ec) = run_cli(argv, output, error);
    ASSERT_TRUE(status != 0);
  }
}

TEST(BasicCliTests, CliInvalidSubcommand) {
  int status = -1;
  std::error_code ec;
  std::string output;
  std::string error;

  std::tie(status, ec) = run_cli({"unknown", "subcommand"}, output, error);
  ASSERT_TRUE(ec) << ec.message();
  ASSERT_TRUE(status != 0);
}

namespace {
std::pair<int, std::error_code> run_cli(const std::vector<std::string>& argv,
                                        std::string& output,
                                        std::string& error) {
  reproc::process process;
  int status = -1;
  reproc::sink::string out_sink(output);
  reproc::sink::string err_sink(error);

  reproc::options options;
  options.deadline = reproc::milliseconds(5000);
  options.redirect.err.type = reproc::redirect::pipe;

  return reproc::run(argv, options, out_sink, err_sink);
}
}  // namespace
