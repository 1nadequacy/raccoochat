#include <iostream>
#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_uint64(a, 1, "first attr");
DEFINE_uint64(b, 2, "second attr");

int main(int argc, char **argv) {
  google::SetUsageMessage("test");
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);

  LOG(INFO) << "Test GLOG";

  std::cout << FLAGS_a << ' ' << FLAGS_b << std::endl;

  return 0;
}

