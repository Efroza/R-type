cmake_minimum_required(VERSION 3.17)

project(r-type)

set(CMAKE_CXX_STANDARD 17)

message("Checking if conan exist in ${CMAKE_BINARY_DIR}")
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message("Downloading conan.cmake from https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
                    "${CMAKE_BINARY_DIR}/conan.cmake"
                    TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_configure(REQUIRES sfml/2.5.1
  GENERATORS cmake)

conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE .
                        BUILD missing
                        REMOTE conancenter
                        SETTINGS ${settings})
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
message("before conanfile.txt")
# conan_cmake_run(CONANFILE conanfile.txt
#                 BASIC_SETUP)

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

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(${PROJECT_NAME}_server ${SRCS1} ${HEADERS1})
add_executable(${PROJECT_NAME}_client ${SRCS2} ${HEADERS2})
target_link_libraries(${PROJECT_NAME}_server ${CONAN_LIBS})
target_link_libraries(${PROJECT_NAME}_client ${CONAN_LIBS})