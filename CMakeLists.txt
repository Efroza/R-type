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
set(SRCS3
    #Game
    ./Engine/Game/main.cpp
    ./Engine/Game/load_component.cpp
    ./Engine/Game/load_systems.cpp
    #BaseComponent
    ./Engine/BaseComponent/image.cpp
    #BaseSystems
    ./Engine/BaseSystems/draw_system.cpp
    ./Engine/BaseSystems/position_system.cpp
    )
set(HEADERS3
    #Include
    ./Engine/Include/entity.hpp
    ./Engine/Include/registry.hpp
    ./Engine/Include/sparse_array.hpp
    ./Engine/Includ/systems.hpp
    #BaseComponent
    ./Engine/BaseComponent/draw.hpp
    ./Engine/BaseComponent/image.hpp
    ./Engine/BaseComponent/position.hpp
)

add_executable(r-type_server ${SRCS1} ${HEADERS1})
add_executable(r-type_client ${SRCS2} ${HEADERS2})
add_executable(r-type ${SRCS3} ${HEADERS3})
target_link_libraries(r-type_client ${CONAN_LIBS})
target_link_libraries(r-type_server ${CONAN_LIBS})
target_link_libraries(r-type ${CONAN_LIBS})