all: server client

server: echoServer.cpp
	g++ -std=c++11  -c ./echoServer.cpp ./gen-cpp/EchoService.cpp ./gen-cpp/echo_constants.cpp ./gen-cpp/echo_types.cpp
	g++ -std=c++11  Echo*.o echoServer.cpp -o server -lpthread -levent -L/usr/local/lib -lthrift -lthriftnb

client: echoClient.cpp
	g++ -std=c++11  -c ./echoClient.cpp ./gen-cpp/EchoService.cpp ./gen-cpp/echo_constants.cpp ./gen-cpp/echo_types.cpp
	g++ -std=c++11  Echo*.o echoClient.cpp -o client -lpthread -levent -L/usr/local/lib -lthrift -lthriftnb

clean:
	rm -f server client
	rm -f *.o
