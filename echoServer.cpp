#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/transport/TTransportException.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/server/TSimpleServer.h>
#include <boost/shared_ptr.hpp>
#include <boost/functional/hash.hpp>

#include "EchoHandler.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::concurrency;
using namespace ::echo;

using boost::shared_ptr;

int main()
{
  int thread_num = 5;
  int port       = 9148;

  boost::shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(thread_num);
  boost::shared_ptr<PosixThreadFactory> threadFactory = boost::shared_ptr<PosixThreadFactory>(
      new PosixThreadFactory(apache::thrift::concurrency::PosixThreadFactory::ROUND_ROBIN,
        apache::thrift::concurrency::PosixThreadFactory::NORMAL, 64));
  threadManager->threadFactory(threadFactory);
  threadManager->start();

  boost::shared_ptr<EchoServiceHandler> handler(new EchoServiceHandler());
  boost::shared_ptr<TProcessor> processor(new EchoServiceProcessor(handler));
  boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
  TNonblockingServer server(processor, protocolFactory, port, threadManager);
  try {
    server.serve();
  }
  catch(TException& tx) {
    threadManager->stop();
    return 1;
  }
}

