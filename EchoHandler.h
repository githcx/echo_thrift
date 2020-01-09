#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/transport/TTransportException.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/server/TSimpleServer.h>
#include "gen-cpp/EchoService.h"

#include <unistd.h>
#include <atomic>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::concurrency;

using namespace ::echo;

class EchoServiceHandler : virtual public EchoServiceIf {
  private:
    std::atomic<int> cnt;
  public:
    virtual void Echo(std::string& _return, const std::string& msg, const TestReq& test)
    {
      //if( ++cnt > 5 ){ _return = "qps limit reached"; return; }
      _return = msg;
      //sleep(10);
    }
};

