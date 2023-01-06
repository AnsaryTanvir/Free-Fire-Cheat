# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -Wl,--exclude-libs,ALL")

#------------------- BEGIN Injector ------------------------#
project("injector")
add_executable( injector.so injector/inject.cpp)
#------------------- END Injector ------------------------#


# Declares and names of the project(s).
#------------------- BEGIN Payload ------------------------#
project("Server")
add_library(
        # Sets the name of the library---> libServer.so
        Server

        # Set the type of the libray
        SHARED

        # Source file(s).
        Server/Server.cpp

        # Substrate Source(s)
        Server/Substrate/Buffer.hpp
        Server/Substrate/CydiaSubstrate.h
        Server/Substrate/hde64.c
        Server/Substrate/hde64.h
        Server/Substrate/SubstrateARM.hpp
        Server/Substrate/SubstrateDebug.cpp
        Server/Substrate/SubstrateDebug.hpp
        Server/Substrate/SubstrateHook.cpp
        Server/Substrate/SubstrateHook.h
        Server/Substrate/SubstrateLog.hpp
        Server/Substrate/SubstratePosixMemory.cpp
        Server/Substrate/SubstrateX86.hpp
        Server/Substrate/SymbolFinder.h
        Server/Substrate/SymbolFinder.cpp
        Server/Substrate/table64.h

        # KittyMemory
        Server/KittyMemory/KittyMemory.cpp
        Server/KittyMemory/MemoryPatch.cpp
        Server/KittyMemory/MemoryBackup.cpp
        Server/KittyMemory/KittyUtils.cpp
        Server/KittyMemory/KittyScanner.cpp
        Server/KittyMemory/KittyArm64.cpp

        # Socket Source(s)
        Socket/SocketServer.cpp

        #Unity
        Unity/Unity.h
        Unity/Vector3.hpp
)
find_library(
        # Sets the name of the path variable.
        log-lib
        # Specifies the name of the NDK library that you want CMake to locate.
        log
)

target_link_libraries(
        # Specifies the target library.
        Server
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
)
#------------------- END Payload ------------------------#


#------------------- BEGIN client ------------------------#
project("Client")
add_library(
        Client
        SHARED
        Client/client.cpp
        Socket/SocketClient.cpp
)
find_library(
        log-lib
        log
)
target_link_libraries(
        Client
        ${log-lib}
)
#------------------- END client ------------------------#

