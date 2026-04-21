cmake_minimum_required(VERSION 3.20)
project(king-arthur-model)
set(CMAKE_CXX_STANDARD 20)

# Erzwinge gleiche Runtime für alle Targets
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
# -----------------------------------------

# 1. Setze Build-Typ Standard auf Release
# -----------------------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# -----------------------------------------
# 2. EXE soll im Projektverzeichnis landen
# -----------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(SFML_STATIC_LIBRARIES ON)
set(SFML_DIR "C:/SFML/lib/cmake/SFML")


find_package(SFML COMPONENTS Graphics Window REQUIRED)
find_package(SFML 3 COMPONENTS Main Network System)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src/gameObjects)
add_subdirectory(src/data)

add_executable( king-arthur-model
        main.cpp
        utils.cpp
        utils.h
)


target_link_libraries(king-arthur-model
        LibGameObjects
        LibData
        SFML::Graphics
        SFML::Window
        SFML::Main
        SFML::Network
        SFML::System
)

# -----------------------------------------
# 6. Windows: MinGW Runtime hinzufügen,
#    aber NICHT ins Build-Verzeichnis mischen!
# -----------------------------------------
if (MINGW)
    target_link_libraries(padi25_08la stdc++fs)
endif()
