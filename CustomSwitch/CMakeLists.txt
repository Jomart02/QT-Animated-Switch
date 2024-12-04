cmake_minimum_required(VERSION 3.5)


project(ToggleSwitchPlugin LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

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

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${QT6_INSTALL_PREFIX})
set(INSTALL_EXAMPLEDIR "${QT6_INSTALL_PREFIX}/${QT6_INSTALL_PLUGINS}/designer")

message(STATUS "QT6_INSTALL_PREFIX: ${QT6_INSTALL_PREFIX}")

find_package(Qt6 COMPONENTS Widgets Designer REQUIRED)

qt6_add_plugin(ToggleSwitchPlugin)

target_sources(${PROJECT_NAME} PRIVATE ${HDRS} ${SRCS} )

target_link_libraries(${PROJECT_NAME} PUBLIC     
    Qt::Widgets
    Qt6::Designer
)

# Установка свойств для библиотеки
set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION 1.0.0
    SOVERSION 1
    PUBLIC_HEADER "${HDRS}"
)
install(TARGETS ToggleSwitchPlugin
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"

)
