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
conan_cmake_configure(REQUIRES sfml/2.5.1 asio/1.24.0 jsoncpp/1.9.5 yaml-cpp/0.7.0
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
    ./server/src/Server.cpp
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

set(GRAPHC_FILES
    ./clientGraphic/main.cpp
    ./clientGraphic/Core.cpp
    ./clientGraphic/Core.hpp
    ./clientGraphic/Graphic/IGraphic.hpp
    ./clientGraphic/Drawable/Drawable.hpp
    ./clientGraphic/Drawable/Drawable.cpp
)

set(SRCS3
    ./Engine/Game/main.cpp
	  ./Engine/Game/load_component.cpp
	  ./Engine/Game/load_systems.cpp
	  ./Engine/BaseComponent/image.cpp
	  ./Engine/BaseComponent/interaction.cpp
	  ./Engine/BaseComponent/rect.cpp
	  ./Engine/BaseSystems/animation_system.cpp
	  ./Engine/BaseSystems/interaction_system.cpp
	  ./Engine/BaseSystems/network_sytem.cpp
	  ./Engine/BaseSystems/collusion_system.cpp
	  ./Engine/ParseComponent/AParseComponent.cpp
	  ./Engine/ParseComponent/AParseInteraction.cpp
	  ./Engine/ParseComponent/parse_position.cpp
	  ./Engine/ParseComponent/parse_image.cpp
	  ./Engine/ParseComponent/parse_rect.cpp
	  ./Engine/ParseComponent/parse_animation.cpp
	  ./Engine/ParseComponent/parse_interaction.cpp
	  ./Engine/ParseComponent/parse_network.cpp
	  ./Engine/Parsing/parsing.cpp
	  ./Engine/Parsing/handling_interaction.cpp
	  ./Engine/Parsing/Yaml.cpp
	  ./Engine/Parsing/handling_component_system.cpp
    )


message("${Green} Building ${PROJECT_NAME}${ColorReset}")
add_executable(${PROJECT_NAME}_graphic ${SRCS3})
target_compile_options(${PROJECT_NAME}_graphic PRIVATE 
    -std=c++20 
    -I./Engine/Include 
    -I./Engine/BaseComponent 
    -I./Engine/ParseComponent 
    -I./Engine/Parsing 
    -I./Engine/Interaction 
    -I./Engine/Interaction/Include 
    -I./Engine/Graphic 
    -I./Engine/ComponentSystem
)
target_link_libraries(${PROJECT_NAME}_graphic ${CONAN_LIBS} jsoncpp dl yaml-cpp)
include(clientGraphic/Graphic/SFML/SFML_lib.cmake)
add_executable(${PROJECT_NAME}_client_graphic ${GRAPHC_FILES})
target_include_directories(${PROJECT_NAME}_client_graphic PRIVATE clientGraphic/Graphic)
target_link_libraries(${PROJECT_NAME}_client_graphic ${CMAKE_DL_LIBS})
add_executable(${PROJECT_NAME}_server ${SRCS1} ${HEADERS1})
add_executable(${PROJECT_NAME}_client ${SRCS2} ${HEADERS2})
target_link_libraries(${PROJECT_NAME}_server ${CONAN_LIBS})
target_link_libraries(${PROJECT_NAME}_client ${CONAN_LIBS})
message("${Green} Done${ColorReset}")
include(InstallRequiredSystemLibraries)
install(TARGETS ${PROJECT_NAME}_server RUNTIME DESTINATION bin)
install(TARGETS ${PROJECT_NAME}_client RUNTIME DESTINATION bin)
include(CPack)