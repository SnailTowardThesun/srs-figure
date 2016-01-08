PROJECT(SRS-FIGURE)
SET(CMAKE_BUILD_TYPE Debug)

if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wno-unused-variable -pthread")
else( CMAKE_BUILD_TYPE STREQUAL "Debug" )
        set(CMAKE_BUILD_TYPE "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -pthread -fopenmp")
endif( CMAKE_BUILD_TYPE STREQUAL "Debug" )

SET(PROTOCOL_RTMP_HANDSHAKE ./protocol/srs_figure_rtmp_handshake.cpp)
SET(APP_SOCKET ./app/srs_figure_app_socket.cpp)
SET(APP_LOG ./app/srs_figure_app_log.cpp)
SET(CORE_CORE ./core/srs_figure_core.cpp)
SET(SRC_LIST ${CORE_CORE} ${APP_LOG} ${APP_SOCKET} ${PROTOCOL_RTMP_HANDSHAKE} SRSClient.cpp srs-figure.cpp )

SET(SRS_BINARY_DIR "./objs/")

SET(EXECUTABLE_OUTPUT_PATH ${SRS_BINARY_DIR})
SET(LIBRARY_OUTPUT_PATH ${SRS_BINARY_DIR})

MESSAGE(STATUS "This is BINARY dir" ${SRS_BINARY_DIR})

ADD_EXECUTABLE(srs-figure ${SRC_LIST})
