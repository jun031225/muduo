# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /workspaces/cpp/mymuduo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspaces/cpp/mymuduo/build

# Include any dependencies generated for this target.
include CMakeFiles/mymuduo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mymuduo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mymuduo.dir/flags.make

CMakeFiles/mymuduo.dir/src/base/Buffer/Buffer.cpp.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/src/base/Buffer/Buffer.cpp.o: ../src/base/Buffer/Buffer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cpp/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mymuduo.dir/src/base/Buffer/Buffer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/src/base/Buffer/Buffer.cpp.o -c /workspaces/cpp/mymuduo/src/base/Buffer/Buffer.cpp

CMakeFiles/mymuduo.dir/src/base/Buffer/Buffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/src/base/Buffer/Buffer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cpp/mymuduo/src/base/Buffer/Buffer.cpp > CMakeFiles/mymuduo.dir/src/base/Buffer/Buffer.cpp.i

CMakeFiles/mymuduo.dir/src/base/Buffer/Buffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/src/base/Buffer/Buffer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cpp/mymuduo/src/base/Buffer/Buffer.cpp -o CMakeFiles/mymuduo.dir/src/base/Buffer/Buffer.cpp.s

CMakeFiles/mymuduo.dir/src/base/Thread/CurrentThread.cpp.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/src/base/Thread/CurrentThread.cpp.o: ../src/base/Thread/CurrentThread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cpp/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mymuduo.dir/src/base/Thread/CurrentThread.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/src/base/Thread/CurrentThread.cpp.o -c /workspaces/cpp/mymuduo/src/base/Thread/CurrentThread.cpp

CMakeFiles/mymuduo.dir/src/base/Thread/CurrentThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/src/base/Thread/CurrentThread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cpp/mymuduo/src/base/Thread/CurrentThread.cpp > CMakeFiles/mymuduo.dir/src/base/Thread/CurrentThread.cpp.i

CMakeFiles/mymuduo.dir/src/base/Thread/CurrentThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/src/base/Thread/CurrentThread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cpp/mymuduo/src/base/Thread/CurrentThread.cpp -o CMakeFiles/mymuduo.dir/src/base/Thread/CurrentThread.cpp.s

CMakeFiles/mymuduo.dir/src/base/Thread/Thread.cpp.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/src/base/Thread/Thread.cpp.o: ../src/base/Thread/Thread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cpp/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/mymuduo.dir/src/base/Thread/Thread.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/src/base/Thread/Thread.cpp.o -c /workspaces/cpp/mymuduo/src/base/Thread/Thread.cpp

CMakeFiles/mymuduo.dir/src/base/Thread/Thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/src/base/Thread/Thread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cpp/mymuduo/src/base/Thread/Thread.cpp > CMakeFiles/mymuduo.dir/src/base/Thread/Thread.cpp.i

CMakeFiles/mymuduo.dir/src/base/Thread/Thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/src/base/Thread/Thread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cpp/mymuduo/src/base/Thread/Thread.cpp -o CMakeFiles/mymuduo.dir/src/base/Thread/Thread.cpp.s

CMakeFiles/mymuduo.dir/src/base/TimeStamp/TimeStamp.cpp.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/src/base/TimeStamp/TimeStamp.cpp.o: ../src/base/TimeStamp/TimeStamp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cpp/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/mymuduo.dir/src/base/TimeStamp/TimeStamp.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/src/base/TimeStamp/TimeStamp.cpp.o -c /workspaces/cpp/mymuduo/src/base/TimeStamp/TimeStamp.cpp

CMakeFiles/mymuduo.dir/src/base/TimeStamp/TimeStamp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/src/base/TimeStamp/TimeStamp.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cpp/mymuduo/src/base/TimeStamp/TimeStamp.cpp > CMakeFiles/mymuduo.dir/src/base/TimeStamp/TimeStamp.cpp.i

CMakeFiles/mymuduo.dir/src/base/TimeStamp/TimeStamp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/src/base/TimeStamp/TimeStamp.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cpp/mymuduo/src/base/TimeStamp/TimeStamp.cpp -o CMakeFiles/mymuduo.dir/src/base/TimeStamp/TimeStamp.cpp.s

CMakeFiles/mymuduo.dir/src/logger/back/AsyncLogging.cpp.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/src/logger/back/AsyncLogging.cpp.o: ../src/logger/back/AsyncLogging.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cpp/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/mymuduo.dir/src/logger/back/AsyncLogging.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/src/logger/back/AsyncLogging.cpp.o -c /workspaces/cpp/mymuduo/src/logger/back/AsyncLogging.cpp

CMakeFiles/mymuduo.dir/src/logger/back/AsyncLogging.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/src/logger/back/AsyncLogging.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cpp/mymuduo/src/logger/back/AsyncLogging.cpp > CMakeFiles/mymuduo.dir/src/logger/back/AsyncLogging.cpp.i

CMakeFiles/mymuduo.dir/src/logger/back/AsyncLogging.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/src/logger/back/AsyncLogging.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cpp/mymuduo/src/logger/back/AsyncLogging.cpp -o CMakeFiles/mymuduo.dir/src/logger/back/AsyncLogging.cpp.s

CMakeFiles/mymuduo.dir/src/logger/back/FileUtil.cpp.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/src/logger/back/FileUtil.cpp.o: ../src/logger/back/FileUtil.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cpp/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/mymuduo.dir/src/logger/back/FileUtil.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/src/logger/back/FileUtil.cpp.o -c /workspaces/cpp/mymuduo/src/logger/back/FileUtil.cpp

CMakeFiles/mymuduo.dir/src/logger/back/FileUtil.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/src/logger/back/FileUtil.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cpp/mymuduo/src/logger/back/FileUtil.cpp > CMakeFiles/mymuduo.dir/src/logger/back/FileUtil.cpp.i

CMakeFiles/mymuduo.dir/src/logger/back/FileUtil.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/src/logger/back/FileUtil.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cpp/mymuduo/src/logger/back/FileUtil.cpp -o CMakeFiles/mymuduo.dir/src/logger/back/FileUtil.cpp.s

CMakeFiles/mymuduo.dir/src/logger/back/LogFile.cpp.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/src/logger/back/LogFile.cpp.o: ../src/logger/back/LogFile.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cpp/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/mymuduo.dir/src/logger/back/LogFile.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/src/logger/back/LogFile.cpp.o -c /workspaces/cpp/mymuduo/src/logger/back/LogFile.cpp

CMakeFiles/mymuduo.dir/src/logger/back/LogFile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/src/logger/back/LogFile.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cpp/mymuduo/src/logger/back/LogFile.cpp > CMakeFiles/mymuduo.dir/src/logger/back/LogFile.cpp.i

CMakeFiles/mymuduo.dir/src/logger/back/LogFile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/src/logger/back/LogFile.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cpp/mymuduo/src/logger/back/LogFile.cpp -o CMakeFiles/mymuduo.dir/src/logger/back/LogFile.cpp.s

CMakeFiles/mymuduo.dir/src/logger/front/LogStream.cpp.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/src/logger/front/LogStream.cpp.o: ../src/logger/front/LogStream.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cpp/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/mymuduo.dir/src/logger/front/LogStream.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/src/logger/front/LogStream.cpp.o -c /workspaces/cpp/mymuduo/src/logger/front/LogStream.cpp

CMakeFiles/mymuduo.dir/src/logger/front/LogStream.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/src/logger/front/LogStream.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cpp/mymuduo/src/logger/front/LogStream.cpp > CMakeFiles/mymuduo.dir/src/logger/front/LogStream.cpp.i

CMakeFiles/mymuduo.dir/src/logger/front/LogStream.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/src/logger/front/LogStream.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cpp/mymuduo/src/logger/front/LogStream.cpp -o CMakeFiles/mymuduo.dir/src/logger/front/LogStream.cpp.s

CMakeFiles/mymuduo.dir/src/logger/front/Logging.cpp.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/src/logger/front/Logging.cpp.o: ../src/logger/front/Logging.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cpp/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/mymuduo.dir/src/logger/front/Logging.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/src/logger/front/Logging.cpp.o -c /workspaces/cpp/mymuduo/src/logger/front/Logging.cpp

CMakeFiles/mymuduo.dir/src/logger/front/Logging.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/src/logger/front/Logging.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cpp/mymuduo/src/logger/front/Logging.cpp > CMakeFiles/mymuduo.dir/src/logger/front/Logging.cpp.i

CMakeFiles/mymuduo.dir/src/logger/front/Logging.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/src/logger/front/Logging.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cpp/mymuduo/src/logger/front/Logging.cpp -o CMakeFiles/mymuduo.dir/src/logger/front/Logging.cpp.s

CMakeFiles/mymuduo.dir/src/net/Channel.cpp.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/src/net/Channel.cpp.o: ../src/net/Channel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cpp/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/mymuduo.dir/src/net/Channel.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/src/net/Channel.cpp.o -c /workspaces/cpp/mymuduo/src/net/Channel.cpp

CMakeFiles/mymuduo.dir/src/net/Channel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/src/net/Channel.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cpp/mymuduo/src/net/Channel.cpp > CMakeFiles/mymuduo.dir/src/net/Channel.cpp.i

CMakeFiles/mymuduo.dir/src/net/Channel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/src/net/Channel.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cpp/mymuduo/src/net/Channel.cpp -o CMakeFiles/mymuduo.dir/src/net/Channel.cpp.s

CMakeFiles/mymuduo.dir/src/net/EPollPoller.cpp.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/src/net/EPollPoller.cpp.o: ../src/net/EPollPoller.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cpp/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/mymuduo.dir/src/net/EPollPoller.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/src/net/EPollPoller.cpp.o -c /workspaces/cpp/mymuduo/src/net/EPollPoller.cpp

CMakeFiles/mymuduo.dir/src/net/EPollPoller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/src/net/EPollPoller.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cpp/mymuduo/src/net/EPollPoller.cpp > CMakeFiles/mymuduo.dir/src/net/EPollPoller.cpp.i

CMakeFiles/mymuduo.dir/src/net/EPollPoller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/src/net/EPollPoller.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cpp/mymuduo/src/net/EPollPoller.cpp -o CMakeFiles/mymuduo.dir/src/net/EPollPoller.cpp.s

CMakeFiles/mymuduo.dir/src/net/EventLoop.cpp.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/src/net/EventLoop.cpp.o: ../src/net/EventLoop.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cpp/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/mymuduo.dir/src/net/EventLoop.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/src/net/EventLoop.cpp.o -c /workspaces/cpp/mymuduo/src/net/EventLoop.cpp

CMakeFiles/mymuduo.dir/src/net/EventLoop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/src/net/EventLoop.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cpp/mymuduo/src/net/EventLoop.cpp > CMakeFiles/mymuduo.dir/src/net/EventLoop.cpp.i

CMakeFiles/mymuduo.dir/src/net/EventLoop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/src/net/EventLoop.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cpp/mymuduo/src/net/EventLoop.cpp -o CMakeFiles/mymuduo.dir/src/net/EventLoop.cpp.s

CMakeFiles/mymuduo.dir/src/net/EventLoopThread.cpp.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/src/net/EventLoopThread.cpp.o: ../src/net/EventLoopThread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cpp/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/mymuduo.dir/src/net/EventLoopThread.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/src/net/EventLoopThread.cpp.o -c /workspaces/cpp/mymuduo/src/net/EventLoopThread.cpp

CMakeFiles/mymuduo.dir/src/net/EventLoopThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/src/net/EventLoopThread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cpp/mymuduo/src/net/EventLoopThread.cpp > CMakeFiles/mymuduo.dir/src/net/EventLoopThread.cpp.i

CMakeFiles/mymuduo.dir/src/net/EventLoopThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/src/net/EventLoopThread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cpp/mymuduo/src/net/EventLoopThread.cpp -o CMakeFiles/mymuduo.dir/src/net/EventLoopThread.cpp.s

CMakeFiles/mymuduo.dir/src/net/EventLoopThreadPool.cpp.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/src/net/EventLoopThreadPool.cpp.o: ../src/net/EventLoopThreadPool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cpp/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/mymuduo.dir/src/net/EventLoopThreadPool.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/src/net/EventLoopThreadPool.cpp.o -c /workspaces/cpp/mymuduo/src/net/EventLoopThreadPool.cpp

CMakeFiles/mymuduo.dir/src/net/EventLoopThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/src/net/EventLoopThreadPool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cpp/mymuduo/src/net/EventLoopThreadPool.cpp > CMakeFiles/mymuduo.dir/src/net/EventLoopThreadPool.cpp.i

CMakeFiles/mymuduo.dir/src/net/EventLoopThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/src/net/EventLoopThreadPool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cpp/mymuduo/src/net/EventLoopThreadPool.cpp -o CMakeFiles/mymuduo.dir/src/net/EventLoopThreadPool.cpp.s

CMakeFiles/mymuduo.dir/src/net/Http/HttpContext.cpp.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/src/net/Http/HttpContext.cpp.o: ../src/net/Http/HttpContext.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cpp/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/mymuduo.dir/src/net/Http/HttpContext.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/src/net/Http/HttpContext.cpp.o -c /workspaces/cpp/mymuduo/src/net/Http/HttpContext.cpp

CMakeFiles/mymuduo.dir/src/net/Http/HttpContext.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/src/net/Http/HttpContext.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cpp/mymuduo/src/net/Http/HttpContext.cpp > CMakeFiles/mymuduo.dir/src/net/Http/HttpContext.cpp.i

CMakeFiles/mymuduo.dir/src/net/Http/HttpContext.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/src/net/Http/HttpContext.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cpp/mymuduo/src/net/Http/HttpContext.cpp -o CMakeFiles/mymuduo.dir/src/net/Http/HttpContext.cpp.s

CMakeFiles/mymuduo.dir/src/net/Http/HttpResponse.cpp.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/src/net/Http/HttpResponse.cpp.o: ../src/net/Http/HttpResponse.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cpp/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/mymuduo.dir/src/net/Http/HttpResponse.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/src/net/Http/HttpResponse.cpp.o -c /workspaces/cpp/mymuduo/src/net/Http/HttpResponse.cpp

CMakeFiles/mymuduo.dir/src/net/Http/HttpResponse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/src/net/Http/HttpResponse.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cpp/mymuduo/src/net/Http/HttpResponse.cpp > CMakeFiles/mymuduo.dir/src/net/Http/HttpResponse.cpp.i

CMakeFiles/mymuduo.dir/src/net/Http/HttpResponse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/src/net/Http/HttpResponse.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cpp/mymuduo/src/net/Http/HttpResponse.cpp -o CMakeFiles/mymuduo.dir/src/net/Http/HttpResponse.cpp.s

CMakeFiles/mymuduo.dir/src/net/Http/HttpServer.cpp.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/src/net/Http/HttpServer.cpp.o: ../src/net/Http/HttpServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cpp/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/mymuduo.dir/src/net/Http/HttpServer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/src/net/Http/HttpServer.cpp.o -c /workspaces/cpp/mymuduo/src/net/Http/HttpServer.cpp

CMakeFiles/mymuduo.dir/src/net/Http/HttpServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/src/net/Http/HttpServer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cpp/mymuduo/src/net/Http/HttpServer.cpp > CMakeFiles/mymuduo.dir/src/net/Http/HttpServer.cpp.i

CMakeFiles/mymuduo.dir/src/net/Http/HttpServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/src/net/Http/HttpServer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cpp/mymuduo/src/net/Http/HttpServer.cpp -o CMakeFiles/mymuduo.dir/src/net/Http/HttpServer.cpp.s

CMakeFiles/mymuduo.dir/src/net/Tcp/Acceptor.cpp.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/src/net/Tcp/Acceptor.cpp.o: ../src/net/Tcp/Acceptor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cpp/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Building CXX object CMakeFiles/mymuduo.dir/src/net/Tcp/Acceptor.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/src/net/Tcp/Acceptor.cpp.o -c /workspaces/cpp/mymuduo/src/net/Tcp/Acceptor.cpp

CMakeFiles/mymuduo.dir/src/net/Tcp/Acceptor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/src/net/Tcp/Acceptor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cpp/mymuduo/src/net/Tcp/Acceptor.cpp > CMakeFiles/mymuduo.dir/src/net/Tcp/Acceptor.cpp.i

CMakeFiles/mymuduo.dir/src/net/Tcp/Acceptor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/src/net/Tcp/Acceptor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cpp/mymuduo/src/net/Tcp/Acceptor.cpp -o CMakeFiles/mymuduo.dir/src/net/Tcp/Acceptor.cpp.s

CMakeFiles/mymuduo.dir/src/net/Tcp/InetAddress.cpp.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/src/net/Tcp/InetAddress.cpp.o: ../src/net/Tcp/InetAddress.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cpp/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_19) "Building CXX object CMakeFiles/mymuduo.dir/src/net/Tcp/InetAddress.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/src/net/Tcp/InetAddress.cpp.o -c /workspaces/cpp/mymuduo/src/net/Tcp/InetAddress.cpp

CMakeFiles/mymuduo.dir/src/net/Tcp/InetAddress.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/src/net/Tcp/InetAddress.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cpp/mymuduo/src/net/Tcp/InetAddress.cpp > CMakeFiles/mymuduo.dir/src/net/Tcp/InetAddress.cpp.i

CMakeFiles/mymuduo.dir/src/net/Tcp/InetAddress.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/src/net/Tcp/InetAddress.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cpp/mymuduo/src/net/Tcp/InetAddress.cpp -o CMakeFiles/mymuduo.dir/src/net/Tcp/InetAddress.cpp.s

CMakeFiles/mymuduo.dir/src/net/Tcp/Socket.cpp.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/src/net/Tcp/Socket.cpp.o: ../src/net/Tcp/Socket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cpp/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_20) "Building CXX object CMakeFiles/mymuduo.dir/src/net/Tcp/Socket.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/src/net/Tcp/Socket.cpp.o -c /workspaces/cpp/mymuduo/src/net/Tcp/Socket.cpp

CMakeFiles/mymuduo.dir/src/net/Tcp/Socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/src/net/Tcp/Socket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cpp/mymuduo/src/net/Tcp/Socket.cpp > CMakeFiles/mymuduo.dir/src/net/Tcp/Socket.cpp.i

CMakeFiles/mymuduo.dir/src/net/Tcp/Socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/src/net/Tcp/Socket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cpp/mymuduo/src/net/Tcp/Socket.cpp -o CMakeFiles/mymuduo.dir/src/net/Tcp/Socket.cpp.s

CMakeFiles/mymuduo.dir/src/net/Tcp/TcpConnection.cpp.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/src/net/Tcp/TcpConnection.cpp.o: ../src/net/Tcp/TcpConnection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cpp/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_21) "Building CXX object CMakeFiles/mymuduo.dir/src/net/Tcp/TcpConnection.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/src/net/Tcp/TcpConnection.cpp.o -c /workspaces/cpp/mymuduo/src/net/Tcp/TcpConnection.cpp

CMakeFiles/mymuduo.dir/src/net/Tcp/TcpConnection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/src/net/Tcp/TcpConnection.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cpp/mymuduo/src/net/Tcp/TcpConnection.cpp > CMakeFiles/mymuduo.dir/src/net/Tcp/TcpConnection.cpp.i

CMakeFiles/mymuduo.dir/src/net/Tcp/TcpConnection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/src/net/Tcp/TcpConnection.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cpp/mymuduo/src/net/Tcp/TcpConnection.cpp -o CMakeFiles/mymuduo.dir/src/net/Tcp/TcpConnection.cpp.s

CMakeFiles/mymuduo.dir/src/net/Tcp/TcpServer.cpp.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/src/net/Tcp/TcpServer.cpp.o: ../src/net/Tcp/TcpServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cpp/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_22) "Building CXX object CMakeFiles/mymuduo.dir/src/net/Tcp/TcpServer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/src/net/Tcp/TcpServer.cpp.o -c /workspaces/cpp/mymuduo/src/net/Tcp/TcpServer.cpp

CMakeFiles/mymuduo.dir/src/net/Tcp/TcpServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/src/net/Tcp/TcpServer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cpp/mymuduo/src/net/Tcp/TcpServer.cpp > CMakeFiles/mymuduo.dir/src/net/Tcp/TcpServer.cpp.i

CMakeFiles/mymuduo.dir/src/net/Tcp/TcpServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/src/net/Tcp/TcpServer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cpp/mymuduo/src/net/Tcp/TcpServer.cpp -o CMakeFiles/mymuduo.dir/src/net/Tcp/TcpServer.cpp.s

CMakeFiles/mymuduo.dir/src/Timer/Timer.cpp.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/src/Timer/Timer.cpp.o: ../src/Timer/Timer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cpp/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_23) "Building CXX object CMakeFiles/mymuduo.dir/src/Timer/Timer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/src/Timer/Timer.cpp.o -c /workspaces/cpp/mymuduo/src/Timer/Timer.cpp

CMakeFiles/mymuduo.dir/src/Timer/Timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/src/Timer/Timer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cpp/mymuduo/src/Timer/Timer.cpp > CMakeFiles/mymuduo.dir/src/Timer/Timer.cpp.i

CMakeFiles/mymuduo.dir/src/Timer/Timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/src/Timer/Timer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cpp/mymuduo/src/Timer/Timer.cpp -o CMakeFiles/mymuduo.dir/src/Timer/Timer.cpp.s

CMakeFiles/mymuduo.dir/src/Timer/TimerQueue.cpp.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/src/Timer/TimerQueue.cpp.o: ../src/Timer/TimerQueue.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cpp/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_24) "Building CXX object CMakeFiles/mymuduo.dir/src/Timer/TimerQueue.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/src/Timer/TimerQueue.cpp.o -c /workspaces/cpp/mymuduo/src/Timer/TimerQueue.cpp

CMakeFiles/mymuduo.dir/src/Timer/TimerQueue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/src/Timer/TimerQueue.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cpp/mymuduo/src/Timer/TimerQueue.cpp > CMakeFiles/mymuduo.dir/src/Timer/TimerQueue.cpp.i

CMakeFiles/mymuduo.dir/src/Timer/TimerQueue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/src/Timer/TimerQueue.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cpp/mymuduo/src/Timer/TimerQueue.cpp -o CMakeFiles/mymuduo.dir/src/Timer/TimerQueue.cpp.s

# Object files for target mymuduo
mymuduo_OBJECTS = \
"CMakeFiles/mymuduo.dir/src/base/Buffer/Buffer.cpp.o" \
"CMakeFiles/mymuduo.dir/src/base/Thread/CurrentThread.cpp.o" \
"CMakeFiles/mymuduo.dir/src/base/Thread/Thread.cpp.o" \
"CMakeFiles/mymuduo.dir/src/base/TimeStamp/TimeStamp.cpp.o" \
"CMakeFiles/mymuduo.dir/src/logger/back/AsyncLogging.cpp.o" \
"CMakeFiles/mymuduo.dir/src/logger/back/FileUtil.cpp.o" \
"CMakeFiles/mymuduo.dir/src/logger/back/LogFile.cpp.o" \
"CMakeFiles/mymuduo.dir/src/logger/front/LogStream.cpp.o" \
"CMakeFiles/mymuduo.dir/src/logger/front/Logging.cpp.o" \
"CMakeFiles/mymuduo.dir/src/net/Channel.cpp.o" \
"CMakeFiles/mymuduo.dir/src/net/EPollPoller.cpp.o" \
"CMakeFiles/mymuduo.dir/src/net/EventLoop.cpp.o" \
"CMakeFiles/mymuduo.dir/src/net/EventLoopThread.cpp.o" \
"CMakeFiles/mymuduo.dir/src/net/EventLoopThreadPool.cpp.o" \
"CMakeFiles/mymuduo.dir/src/net/Http/HttpContext.cpp.o" \
"CMakeFiles/mymuduo.dir/src/net/Http/HttpResponse.cpp.o" \
"CMakeFiles/mymuduo.dir/src/net/Http/HttpServer.cpp.o" \
"CMakeFiles/mymuduo.dir/src/net/Tcp/Acceptor.cpp.o" \
"CMakeFiles/mymuduo.dir/src/net/Tcp/InetAddress.cpp.o" \
"CMakeFiles/mymuduo.dir/src/net/Tcp/Socket.cpp.o" \
"CMakeFiles/mymuduo.dir/src/net/Tcp/TcpConnection.cpp.o" \
"CMakeFiles/mymuduo.dir/src/net/Tcp/TcpServer.cpp.o" \
"CMakeFiles/mymuduo.dir/src/Timer/Timer.cpp.o" \
"CMakeFiles/mymuduo.dir/src/Timer/TimerQueue.cpp.o"

# External object files for target mymuduo
mymuduo_EXTERNAL_OBJECTS =

../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/src/base/Buffer/Buffer.cpp.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/src/base/Thread/CurrentThread.cpp.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/src/base/Thread/Thread.cpp.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/src/base/TimeStamp/TimeStamp.cpp.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/src/logger/back/AsyncLogging.cpp.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/src/logger/back/FileUtil.cpp.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/src/logger/back/LogFile.cpp.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/src/logger/front/LogStream.cpp.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/src/logger/front/Logging.cpp.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/src/net/Channel.cpp.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/src/net/EPollPoller.cpp.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/src/net/EventLoop.cpp.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/src/net/EventLoopThread.cpp.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/src/net/EventLoopThreadPool.cpp.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/src/net/Http/HttpContext.cpp.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/src/net/Http/HttpResponse.cpp.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/src/net/Http/HttpServer.cpp.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/src/net/Tcp/Acceptor.cpp.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/src/net/Tcp/InetAddress.cpp.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/src/net/Tcp/Socket.cpp.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/src/net/Tcp/TcpConnection.cpp.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/src/net/Tcp/TcpServer.cpp.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/src/Timer/Timer.cpp.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/src/Timer/TimerQueue.cpp.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/build.make
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/cpp/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_25) "Linking CXX shared library ../lib/libmymuduo.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mymuduo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mymuduo.dir/build: ../lib/libmymuduo.so

.PHONY : CMakeFiles/mymuduo.dir/build

CMakeFiles/mymuduo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mymuduo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mymuduo.dir/clean

CMakeFiles/mymuduo.dir/depend:
	cd /workspaces/cpp/mymuduo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/cpp/mymuduo /workspaces/cpp/mymuduo /workspaces/cpp/mymuduo/build /workspaces/cpp/mymuduo/build /workspaces/cpp/mymuduo/build/CMakeFiles/mymuduo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mymuduo.dir/depend

