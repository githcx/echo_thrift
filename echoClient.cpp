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
  TestReq test;

  transportClient->open();

  string str;
  client.Echo(str, "hello", test);
  cout << str << endl;

  client.Echo(str, "olleh", test);
  cout << str << endl;

  transportClient->close();

  return 0;
}
