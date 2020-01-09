all: server client

server: echoServer.cpp
	g++ -std=c++11  -c ./echoServer.cpp ./gen-cpp/EchoService.cpp ./gen-cpp/echo_constants.cpp ./gen-cpp/echo_types.cpp
	g++ -std=c++11  Echo*.o echoServer.cpp echo_*.o -o server -lpthread -levent -lthrift -lthriftnb

client: echoClient.cpp
	g++ -std=c++11  -c ./echoClient.cpp ./gen-cpp/EchoService.cpp ./gen-cpp/echo_constants.cpp ./gen-cpp/echo_types.cpp
	g++ -std=c++11  Echo*.o echoClient.cpp echo_*.o -o client -lpthread -levent -lthrift -lthriftnb

clean:
	rm -f server client
	rm -f *.o
