#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include <thrift/TOutput.h>
#include "../src/utils/logger.h"

using namespace ::apache::thrift;
using namespace ::elasticmem::utils;

int main(int argc, char *argv[]) {
  log_utils::configure_log_level(log_level::all);
  GlobalOutput.setOutputFunction(log_utils::log_thrift_msg);
  return Catch::Session().run(argc, argv);
}