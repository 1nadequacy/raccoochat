all:
	llvm-g++ -std=c++11 -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -Wall -I/usr/local/include/thrift *.cpp -L/usr/local/lib -lthrift -o server
