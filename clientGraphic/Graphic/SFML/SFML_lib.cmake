set(CMAKE_CXX_STANDARD 20)

add_library(SFML SHARED
        clientGraphic/Graphic/SFML/SFML.hpp
        clientGraphic/Graphic/SFML/SFML.cpp
        clientGraphic/Graphic/IGraphic.hpp
        clientGraphic/Graphic/AGraphic.hpp
        clientGraphic/Graphic/AGraphic.cpp

        clientGraphic/Drawable/Drawable.hpp
        clientGraphic/Drawable/Drawable.cpp
    )

    conan_target_link_libraries(SFML ${CONAN_LIBS})