cmake_minimum_required(VERSION 3.5.1)
project(gomoku)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -o3 -fopenmp -pg")
include_directories(./includes ./)


set(SOURCE_FILES
    doc/doc.txt
    includes/ASFMLCanvas.hpp
    includes/Game.hpp
    includes/GomokuWindow.hpp
    includes/Player.hpp
    includes/SFMLCanvas.hh
        includes/MinMax.hh
    ressources/back.bmp
    ressources/back.jpg
    ressources/black.jpg
    ressources/black.png
    ressources/black_transp.png
    ressources/blackTurn.png
    ressources/blackWin.png
    ressources/gomoku.jpg
    ressources/invalid.png
    ressources/Open.ttf
    ressources/white.jpg
    ressources/white.png
    ressources/white_transp.png
    ressources/whiteTurn.png
    ressources/whiteWin.png
    src/ASFMLCanvas.cpp
    src/Game.cpp
    src/GomokuWindow.cpp
    src/main.cpp
    src/Player.cpp
    src/sfmlcanvas.cpp
        src/MinMax.cpp
        bug3.txt
    gomoku.pro
    gomoku.pro.user
        GomokuWindow.ui
        Makefile
    moc_GomokuWindow.cpp
        patterns_default
        test.txt
    ui_GomokuWindow.h src/Pattern.cpp includes/Pattern.hpp)

find_package(Qt5Widgets REQUIRED)

add_executable(gomoku ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(gomoku ${SFML_LIBRARIES})
endif()

target_link_libraries(gomoku Qt5::Widgets)