set(CMAKE_CXX_STANDARD 20)

add_library(print SHARED
    Engine/ComponentSystem/print.cpp
    Engine/ComponentSystem/print.hpp
)
conan_target_link_libraries(print ${CONAN_LIBS})