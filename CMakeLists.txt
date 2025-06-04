cmake_minimum_required(VERSION 3.5)

project(Live_Signal_Generator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(${CMAKE_SOURCE_DIR})  # <--- Make sure qcustomplot.h is here

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    qcustomplot.cpp
    qcustomplot.h
)

add_executable(Live_Signal_Generator
    ${PROJECT_SOURCES}
)

target_link_libraries(Live_Signal_Generator
    Qt6::Widgets
)
