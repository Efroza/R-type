cmake_minimum_required(VERSION 3.17)

project(r-type)

set(CMAKE_CXX_STANDARD 20)

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
	  ./Engine/BaseSystems/network_player_system.cpp
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
	  ./Engine/server/src/tcp.cpp
	  ./Engine/server/src/udp.cpp
	  ./Engine/server/src/Server.cpp
	  ./shared/src/ClientInfo.cpp
    )

set(HEADERS3
    ./Engine/BaseComponent/animation.hpp
    ./Engine/BaseComponent/collusion.hpp
    ./Engine/BaseComponent/image.hpp
    ./Engine/BaseComponent/interaction.hpp
    ./Engine/BaseComponent/position.hpp
    ./Engine/BaseComponent/rect.hpp
    ./Engine/BaseComponent/network.hpp
    ./Engine/BaseComponent/network_player.hpp
    ./Engine/ComponentSystem/draw.hpp
    ./Engine/ComponentSystem/IComponentSystem.hpp
    ./Engine/ComponentSystem/print.hpp
    ./Engine/Include/data.hpp
    ./Engine/Include/entity.hpp
    ./Engine/Include/interactive.hpp
    ./Engine/Include/registry.hpp
    ./Engine/Include/sparse_array.hpp
    ./Engine/Include/systems.hpp
    ./Engine/Interaction/ILoad_Interaction.hpp
    ./Engine/Interaction/Include/down_deplacement.hpp
    ./Engine/Interaction/Include/left_deplacement.hpp
    ./Engine/Interaction/Include/right_deplacement.hpp
    ./Engine/Interaction/Include/up_deplacement.hpp
    ./Engine/ParseComponent/AParseComponent.hpp
    ./Engine/ParseComponent/AParseInteraction.hpp
    ./Engine/ParseComponent/IParseComponent.hpp
    ./Engine/ParseComponent/parse_animation.hpp
    ./Engine/ParseComponent/parse_image.hpp
    ./Engine/ParseComponent/parse_interaction.hpp
    ./Engine/ParseComponent/parse_network.hpp
    ./Engine/ParseComponent/parse_position.hpp
    ./Engine/ParseComponent/parse_rect.hpp
    ./Engine/Parsing/handling_component_system.hpp
    ./Engine/Parsing/handling_interaction.hpp
    ./Engine/Parsing/parsing.hpp
    ./Engine/Parsing/Yaml.hpp
    ./Engine/Parsing/Parsor.hpp
)

message("${Green} Building ${PROJECT_NAME}${ColorReset}")
add_executable(${PROJECT_NAME}_graphic ${SRCS3} ${HEADERS3})
target_compile_options(${PROJECT_NAME}_graphic PRIVATE 
    -I./Engine/Include
    -I./Engine/BaseComponent
    -I./Engine/ParseComponent
    -I./Engine/Parsing
    -I./Engine/Interaction
    -I./Engine/Interaction/Include
    -I./Engine/Graphic
    -I./Engine/ComponentSystem
    -I./Engine/server/include
)
target_link_libraries(${PROJECT_NAME}_graphic ${CONAN_LIBS})
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
install(TARGETS ${PROJECT_NAME}_graphic RUNTIME DESTINATION bin)
install(TARGETS ${PROJECT_NAME}_client_graphic RUNTIME DESTINATION bin)
include(CPack)
