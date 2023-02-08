.PHONY:all
all:tcp_client tcp_server


tcp_client:tcp_client.cpp
	g++ -o $@ $^ -std=c++11 -lpthread

tcp_server:tcp_server.cpp
	g++ -o $@ $^ -std=c++11 -lpthread

.PHONY:clean
clean:
	rm -f tcp_client tcp_server
