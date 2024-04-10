# 更改成自己项目的根目录
PROJECT_PATH=/workspaces/cpp/muduo/muduo
HEADER_PATH=-I ${PROJECT_PATH}/src/base \
			-I ${PROJECT_PATH}/src/net \
			-I ${PROJECT_PATH}/src/logger \
			-I ${PROJECT_PATH}/src/http \

LIB_PATH=-lmymuduo -lpthread

CFLAGS= -g -Wall ${LIB_PATH} ${HEADER_PATH}

all: EchoServer HttpServerTest

EchoServer: EchoServer.cpp
	g++ EchoServer.cpp ${CFLAGS} -L ${PROJECT_PATH}/lib -o EchoServer 

HttpServerTest:
	g++ HttpServerTest.cpp ${CFLAGS} -L ${PROJECT_PATH}/lib -o HttpServerTest

clean:
	rm -r EchoServer HttpServerTest