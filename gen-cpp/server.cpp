#include "RaccooChat.h"
#include "RaccooChatServer.h"

#include <iostream>

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PosixThreadFactory.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::concurrency;

using boost::shared_ptr;

using namespace ::raccoochat;

//DEFINE_uint64(port, 9090, "port number");
//DEFINE_uint64(threads, 32, "number of threads");

int main(int argc, char **argv) {
  int32_t port = 9090;
  size_t threads = 32;
  //google::SetUsageMessage("server");
  //google::ParseCommandLineFlags(&argc, &argv, true);
  //google::InitGoogleLogging(argv[0]);

  shared_ptr<RaccooChatHandler> handler(new RaccooChatHandler());
  shared_ptr<TProcessor> processor(new RaccooChatProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(threads);
  shared_ptr<ThreadFactory> threadFactory(new PosixThreadFactory());
  threadManager->threadFactory(threadFactory);
  threadManager->start();

  //TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  //TNonblockingServer* server = new TNonblockingServer(processor, protocolFactory, port, threadManager);
  TThreadedServer server(processor, serverTransport, transportFactory, protocolFactory);

  //LOG(INFO) << "Server has started.";
  std::cout << "Server has started." << std::endl;
  server.serve();
  std::cout << "Done." << std::endl;

  return 0;
}

