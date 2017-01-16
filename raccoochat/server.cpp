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


using namespace ::raccoochat;

DEFINE_uint64(port, 9090, "port number");
DEFINE_uint64(threads, 32, "number of threads");

int main(int argc, char **argv) {
  google::SetUsageMessage("RaccooChat Server");
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);

  boost::shared_ptr<RaccooChatHandler> handler(new RaccooChatHandler());
  boost::shared_ptr<TProcessor> processor(new RaccooChatProcessor(handler));
  boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(FLAGS_port));
  boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  boost::shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(FLAGS_threads);
  boost::shared_ptr<ThreadFactory> threadFactory(new PosixThreadFactory());
  threadManager->threadFactory(threadFactory);
  threadManager->start();

  //TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  //TNonblockingServer* server = new TNonblockingServer(processor, protocolFactory, port, threadManager);
  TThreadedServer server(processor, serverTransport, transportFactory, protocolFactory);

  LOG(INFO) << "Server has started";
  server.serve();
  LOG(INFO) << "Server has stopped";

  return 0;
}
