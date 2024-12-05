cmake_minimum_required(VERSION 3.5)

set(PLUGIN ToggleSwitchPlugin)
project(${PLUGIN})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(HDRS
    ToggleSwitch.h
    ToggleSwitchPlugin.h
)

set(SRCS
    ToggleSwitch.cpp
    ToggleSwitchPlugin.cpp
)
set(QRCS
    res.qrc
)

# set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${QT6_INSTALL_PREFIX})
# set(INSTALL_EXAMPLEDIR "${QT6_INSTALL_PREFIX}/${QT6_INSTALL_PLUGINS}/designer")

message(STATUS "QT6_INSTALL_PREFIX: ${QT6_INSTALL_PREFIX}/${QT6_INSTALL_PLUGINS}")

find_package(Qt6 COMPONENTS Widgets Core Gui Designer REQUIRED)



add_library(${PLUGIN} SHARED ${HDRS} ${SRCS} ${QRCS})

target_link_libraries(${PLUGIN} Qt6::Widgets Qt6::Designer Qt6::Core Qt6::Gui)

# #Установка свойств для библиотеки
# set_target_properties(${PLUGIN} PROPERTIES
#     VERSION 1.0.0
#     SOVERSION 1
#     PUBLIC_HEADER "${HDRS}"
# )
install(TARGETS ${PLUGIN}
    DESTINATION ${QT6_INSTALL_PREFIX}/${QT6_INSTALL_PLUGINS}/designer
)
