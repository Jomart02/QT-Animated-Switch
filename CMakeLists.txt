cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME test)
project(${PROJECT_NAME})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include/)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include/CustomSwitch)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include/TestWindow)

set(HDRS
    ./include/TestWindow/TestWindow.h
    ./include/CustomSwitch/ToggleSwitch.hpp
)

set(SRCS
    ./src/main.cpp
    ./src/TestWindow/TestWindow.cpp

)

set(QRCS

)

set(CMAKE_AUTOUIC_SEARCH_PATHS 
    ./forms/TestWindow
)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(${PROJECT_NAME} ${SRCS} ${QRCS} ${HDRS})

target_link_libraries(${PROJECT_NAME} Qt6::Widgets )