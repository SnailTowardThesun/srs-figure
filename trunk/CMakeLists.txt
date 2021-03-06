PROJECT(SRS-FIGURE)
SET(CMAKE_BUILD_TYPE Debug)

if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11  -g -Wall -Wno-unused-variable -pthread -fpermissive")
else( CMAKE_BUILD_TYPE STREQUAL "Debug" )
        set(CMAKE_BUILD_TYPE "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11  -O2 -pthread -fopenmp")
endif( CMAKE_BUILD_TYPE STREQUAL "Debug" )

include_directories("./3rdparty/st-1.9/obj/")
include_directories("./app/")
include_directories("./core/")
include_directories("./kernel/")
include_directories("./protocol/")

SET(PROTOCOL_RTMP_HANDSHAKE ./protocol/srs_figure_rtmp_handshake.cpp)
SET(PROTOCOL_RTMP_CHUNK ./protocol/srs_figure_rtmp_chunk.cpp)
SET(PROTOCOL_FUNCTION ${PROTOCOL_RTMP_HANDSHAKE} ${PROTOCOL_RTMP_CHUNK})


SET(APP_SOCKET ./app/srs_figure_app_socket.cpp)
SET(APP_ST_SOCKET ./app/srs_figure_app_st_socket.cpp)
SET(APP_ST_THREAD ./app/srs_figure_app_st_thread.cpp)
SET(APP_LOG ./app/srs_figure_app_log.cpp)
SET(APP_CONF ./app/srs_figure_app_conf.cpp)
SET(APP_FUNCTION ${APP_LOG} ${APP_CONF} ${APP_SOCKET} ${APP_ST_SOCKET} ${APP_ST_THREAD})

SET(CORE_CORE ./core/srs_figure_core.cpp)

SET(KERNEL_STREAM ./kernel/srs_figure_kernel_stream.cpp)
SET(SRC_LIST ${CORE_CORE} ${APP_FUNCTION} ${PROTOCOL_FUNCTION} ${KERNEL_STREAM} SRSClient.cpp srs-figure.cpp )

SET(SRS_BINARY_DIR "./objs/")

SET(EXECUTABLE_OUTPUT_PATH ${SRS_BINARY_DIR})
SET(LIBRARY_OUTPUT_PATH ${SRS_BINARY_DIR})

MESSAGE(STATUS "This is BINARY dir" ${SRS_BINARY_DIR})

ADD_EXECUTABLE(srs-figure ${SRC_LIST})
TARGET_LINK_LIBRARIES(srs-figure "${CMAKE_SOURCE_DIR}/3rdparty/st-1.9/obj/libst.a")
