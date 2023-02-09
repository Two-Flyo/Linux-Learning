.PHONY:all
all:CalcServer CalcClient

CalcServer:CalcServer.cpp
	g++ -o $@ $^ -std=c++11 -lpthread -ljsoncpp
CalcClient:CalcClient.cpp
	g++ -o $@ $^ -std=c++11 -ljsoncpp


.PHONY:clean
clean:
	rm -f CalcClient CalcServer


