cmake_minimum_required(VERSION 3.17)

project(r-type)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(SRCS1
    ./server/src/main.cpp
    )

set(HEADERS1
    )

set(SRCS2
    ./client/src/main.cpp
    )
    
set(HEADERS2
    )    

add_executable(r-type_server ${SRCS1} ${HEADERS1})
add_executable(r-type_client ${SRCS2} ${HEADERS2})
target_link_libraries(r-type_server ${CONAN_LIBS})
target_link_libraries(r-type_client ${CONAN_LIBS})