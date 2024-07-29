add_library(DOWN SHARED
    Engine/Interaction/Include/down_deplacement.hpp
    Engine/Interaction/src/down_deplacement.cpp
)

add_library(UP SHARED

    Engine/Interaction/Include/up_deplacement.hpp
    Engine/Interaction/src/up_deplacement.cpp
)

add_library(RIGHT SHARED

    Engine/Interaction/Include/right_deplacement.hpp
    Engine/Interaction/src/right_deplacement.cpp
)
add_library(LEFT SHARED

    Engine/Interaction/Include/left_deplacement.hpp
    Engine/Interaction/src/left_deplacement.cpp
)
add_library(SHOOT SHARED

    Engine/Interaction/Include/shoot_rocket.hpp
    Engine/Interaction/src/shoot_rocket.cpp
)

# conan_target_link_libraries(INTERACTION ${CONAN_LIBS})