#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PosixThreadFactory.h>

#include <iostream>

#include "RacconChat.h"
#include "CppRacconChat.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::concurrency;

using boost::shared_ptr;

using namespace ::tutorial;

int32_t main(int32_t argc, char **argv) {
  int32_t port = 9090;
  size_t numThreads = 32;

  shared_ptr<RacconChatHandler> handler(new RacconChatHandler());
  shared_ptr<TProcessor> processor(new RacconChatProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(numThreads);
  shared_ptr<ThreadFactory> threadFactory(new PosixThreadFactory());
  threadManager->threadFactory(threadFactory);
  threadManager->start();

  //TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  //TNonblockingServer* server = new TNonblockingServer(processor, protocolFactory, port, threadManager);
  TThreadedServer server(processor, serverTransport, transportFactory, protocolFactory);

  std::cout << "Server has started." << std::endl;
  server.serve();
  std::cout << "Done." << std::endl;

  return 0;
}

