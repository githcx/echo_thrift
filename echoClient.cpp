#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include "gen-cpp/EchoService.h"

#include <string>
#include <iostream>

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::concurrency;

using namespace ::echo;

int main()
{
  boost::shared_ptr<TSocket> socket(new TSocket("localhost",9148));
  boost::shared_ptr<TTransport> transportClient(new TFramedTransport(socket));
  boost::shared_ptr<TProtocol> protocolClient(new TBinaryProtocol(transportClient));

  EchoServiceClient client(protocolClient);
  //socket->setConnTimeout(1);
  //socket->setSendTimeout(1);
  socket->setRecvTimeout(1000);

  for(int retry = 0; retry < 2; retry++)
  {
    try{
      transportClient->open();

      string str;
      client.Echo(str, "hello");
      cout << str << endl;

      client.Echo(str, "olleh");
      cout << str << endl;

      transportClient->close();
      return 0;
    }
    catch(apache::thrift::transport::TTransportException& tx){
      cout << "transport Exception" << "retry #" << retry << " failed" << endl;;
      transportClient->close();
    }
    catch(apache::thrift::TException& tx){
      cout << "other Exception" << "retry #" << retry << " failed" << endl;
      transportClient->close();
    }
  }
  return 0;
}
