cmake_minimum_required(VERSION 3.17)

project(r-type)

set(CMAKE_CXX_STANDARD 17)

string(ASCII 27 Esc)
set(ColorReset "${Esc}[m")
set(Red         "${Esc}[31m")
set(Green       "${Esc}[32m")

message("${Green}Checking if conan exist in ${CMAKE_BINARY_DIR}${ColorReset}")
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message("${Red}Downloading conan.cmake from https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake${ColorReset}")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
                    "${CMAKE_BINARY_DIR}/conan.cmake"
                    TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

message("${Green}Checking if doxygen exist in ${CMAKE_BINARY_DIR}${ColorReset}")
find_package(Doxygen)
if(DOXYGEN_FOUND)
  add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
  )
endif(DOXYGEN_FOUND)


message("${Green} Installing dependencies${ColorReset}")
conan_cmake_configure(REQUIRES sfml/2.5.1 asio/1.24.0
  GENERATORS cmake)

conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE .
                        BUILD missing
                        REMOTE conancenter
                        SETTINGS ${settings})

message("${Green} Loading dependencies${ColorReset}")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(SRCS1
    ./server/src/main.cpp
    ./server/src/tcp.cpp
    ./server/src/udp.cpp
    ./shared/src/ClientInfo.cpp
    )

set(HEADERS1
    ./server/include/server.hpp
    ./shared/include/headers.hpp
    ./shared/include/ClientInfo.hpp
    )

set(SRCS2
    ./client/src/main.cpp
    ./client/src/tcp.cpp
    ./client/src/udp.cpp
    ./shared/src/ClientInfo.cpp
    )
    
set(HEADERS2
    ./client/include/client.hpp
    ./shared/include/headers.hpp
    ./shared/include/ClientInfo.hpp
    )
# set(SRCS3
#     #Game
#     ./Engine/Game/main.cpp
#     ./Engine/Game/load_component.cpp
#     ./Engine/Game/load_systems.cpp
#     #BaseComponent
#     ./Engine/BaseComponent/image.cpp
#     #BaseSystems
#     ./Engine/BaseSystems/draw_system.cpp
#     ./Engine/BaseSystems/position_system.cpp
#     )
# set(HEADERS3
#     #Include
#     ./Engine/Include/entity.hpp
#     ./Engine/Include/registry.hpp
#     ./Engine/Include/sparse_array.hpp
#     ./Engine/Includ/systems.hpp
#     #BaseComponent
#     ./Engine/BaseComponent/draw.hpp
#     ./Engine/BaseComponent/image.hpp
#     ./Engine/BaseComponent/position.hpp
# )

# add_executable(r-type_server ${SRCS1} ${HEADERS1})
# add_executable(r-type_client ${SRCS2} ${HEADERS2})
# add_executable(r-type ${SRCS3} ${HEADERS3})
# target_link_libraries(r-type_client ${CONAN_LIBS})
# target_link_libraries(r-type_server ${CONAN_LIBS})
# target_link_libraries(r-type ${CONAN_LIBS})
#     ./client/include/client.hpp
#     )

message("${Green} Building ${PROJECT_NAME}${ColorReset}")
add_executable(${PROJECT_NAME}_server ${SRCS1} ${HEADERS1})
add_executable(${PROJECT_NAME}_client ${SRCS2} ${HEADERS2})
target_link_libraries(${PROJECT_NAME}_server ${CONAN_LIBS})
target_link_libraries(${PROJECT_NAME}_client ${CONAN_LIBS})
message("${Green} Done${ColorReset}")
include(InstallRequiredSystemLibraries)
install(TARGETS ${PROJECT_NAME}_server RUNTIME DESTINATION bin)
install(TARGETS ${PROJECT_NAME}_client RUNTIME DESTINATION bin)
include(CPack)