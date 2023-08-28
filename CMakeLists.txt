cmake_minimum_required(VERSION 3.22.1)
project(YoshimiWRT)

set(CMAKE_CXX_STANDARD 23)

add_executable(YoshimiWRT main.cpp
        include/Header.h
        include/Host_Monitor.h
        lib/Host.cpp
        include/Host.h
        lib/Host_Monitor.cpp
        include/Definitions.h
        include/Logger.h
        include/Network_Utils.h
        include/Shared_Host_Vector.h
        include/Network.h
        include/Test.h
        include/Exceptions.h
)