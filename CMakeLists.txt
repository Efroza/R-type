cmake_minimum_required(VERSION 3.17)

project(r-type)

set(CMAKE_CXX_STANDARD 17)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message("Downloading conan.cmake from https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
                    "${CMAKE_BINARY_DIR}/conan.cmake"
                    TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_install(PATH_OR_REFERENCE .
                    BUILD missing
                    REMOTE conan-center
                    SETTINGS compiler.libcxx=libstdc++11)


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

add_executable(${PROJECT_NAME}_server ${SRCS1} ${HEADERS1})
add_executable(${PROJECT_NAME}_client ${SRCS2} ${HEADERS2})
target_link_libraries(${PROJECT_NAME}_server ${CONAN_LIBS})
target_link_libraries(${PROJECT_NAME}_client ${CONAN_LIBS})