cmake_minimum_required(VERSION 3.22.1)
project(YoshimiWRT)

set(CMAKE_CXX_STANDARD 23)

add_executable(YoshimiWRT main.cpp
        include/Header.h
        include/Host_Monitor.h
        src/Host.cpp
        include/Host.h
        src/Host_Monitor.cpp
        include/Definitions.h
        include/Logger.h
        include/Network_Utils.h
        include/Shared_Host_Vector.h
        include/Network.h
        include/Test.h
        include/Exceptions.h
        include/network_interface.h include/HWAddress.h include/IPv4Address.h)