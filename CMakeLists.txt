cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME test)
project(${PROJECT_NAME})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include/)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include/TestWindow)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/CustomSwitch)

set(HDRS
    ./include/TestWindow/TestWindow.h

)

set(SRCS
    ./src/main.cpp
    ./src/TestWindow/TestWindow.cpp

)

set(QRCS
    resources/Switch.qrc
)

set(CMAKE_AUTOUIC_SEARCH_PATHS 
    ./forms/TestWindow
)

find_package(Qt6 COMPONENTS Widgets Designer REQUIRED)
add_subdirectory(CustomSwitch)

add_executable(${PROJECT_NAME} ${SRCS} ${QRCS} ${HDRS})

target_link_libraries(${PROJECT_NAME} Qt6::Widgets Qt6::Designer ToggleSwitchPlugin )