cmake_minimum_required(VERSION 3.18)
# 设置项目名称
project(mymuduo C CPP)

# 添加搜索路径
include_directories(
    #${PROJECT_SOURCE_DIR}/src/base
    #${PROJECT_SOURCE_DIR}/src/net
    #${PROJECT_SOURCE_DIR}/src/logger
    #${PROJECT_SOURCE_DIR}/src/http

    ${PROJECT_SOURCE_DIR}/src/base/ 
    ${PROJECT_SOURCE_DIR}/src/base/Buffer 
    ${PROJECT_SOURCE_DIR}/src/base/Thread 
	${PROJECT_SOURCE_DIR}/src/base/TimeStamp 
	${PROJECT_SOURCE_DIR}/src/logger 
	${PROJECT_SOURCE_DIR}/src/logger/back 
	${PROJECT_SOURCE_DIR}/src/logger/front 
	${PROJECT_SOURCE_DIR}/src/net 
	${PROJECT_SOURCE_DIR}/src/net/Http 
    ${PROJECT_SOURCE_DIR}/src/net/Tcp 
	${PROJECT_SOURCE_DIR}/src/Timer 
    )

# 包含这些目录下的.cc文件
#aux_source_directory(${PROJECT_SOURCE_DIR}/src/base SRC_BASE)
#aux_source_directory(${PROJECT_SOURCE_DIR}/src/net SRC_NET)
#aux_source_directory(${PROJECT_SOURCE_DIR}/src/logger SRC_LOG)
#aux_source_directory(${PROJECT_SOURCE_DIR}/src/http SRC_HTTP)

aux_source_directory(${PROJECT_SOURCE_DIR}/src/base SRC_BASE)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/base/Buffer SRC_BUFFER) 
aux_source_directory(${PROJECT_SOURCE_DIR}/src/base/Thread SRC_THREAD) 
aux_source_directory(${PROJECT_SOURCE_DIR}/src/base/TimeStamp SRC_TIMESTAMP) 
aux_source_directory(${PROJECT_SOURCE_DIR}/src/logger SRC_LOGGER) 
aux_source_directory(${PROJECT_SOURCE_DIR}/src/logger/back SRC_LOGGER_BACK) 
aux_source_directory(${PROJECT_SOURCE_DIR}/src/logger/front SRC_LOGGER_FRONT) 
aux_source_directory(${PROJECT_SOURCE_DIR}/src/net SRC_NET) 
aux_source_directory(${PROJECT_SOURCE_DIR}/src/net/Http SRC_HTTP) 
aux_source_directory(${PROJECT_SOURCE_DIR}/src/net/Tcp SRC_TCP) 
aux_source_directory(${PROJECT_SOURCE_DIR}/src/Timer SRC_TIMER) 


# mymuduo最终编译成so动态库 设置动态库的路径 放置项目根目录的lib文件夹下面
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# 设置编译选项
set(CXX_FLAGS "-g -Wall -std=c++11")

# 生成动态库 mymuduo
#add_library(mymuduo SHARED  ${SRC_BASE} ${SRC_NET} ${SRC_LOG} ${SRC_HTTP})

add_library(mymuduo SHARED  ${SRC_BASE} ${SRC_BUFFER} ${SRC_THREAD} ${SRC_TIMESTAMP} ${SRC_LOGGER} ${SRC_LOGGER_BACK} ${SRC_LOGGER_FRONT} ${SRC_NET} ${SRC_HTTP} ${SRC_TCP} ${SRC_TIMER})

# 目标动态库所需连接的库（这里需要连接libpthread.so）
target_link_libraries(mymuduo pthread)

# 设置安装的默认路径
# set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
# install(TARGETS mymuduo LIBRARY DESTINATION lib)
# # 将目录安装到 include/tiny_network 下（只安装头文件）
# install(DIRECTORY ${PROJECT_SOURCE_DIR}/src/ DESTINATION include
#         FILES_MATCHING PATTERN "*.h")