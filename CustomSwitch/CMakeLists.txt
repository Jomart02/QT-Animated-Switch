cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME ToggleSwitch)
project(${PROJECT_NAME})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(HDRS
    ToggleSwitch.hpp
    ToggleSwitchPlugin.h
)

set(SRCS
    ToggleSwitchPlugin.cpp
)

set(INSTALL_EXAMPLEDIR "${QT6_INSTALL_PREFIX}/${QT6_INSTALL_PLUGINS}/designer")
# install(TARGETS ${PROJECT_NAME}
#     RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
#     BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
#     LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
# )

find_package(Qt6 COMPONENTS Widgets Designer REQUIRED)

add_library(${PROJECT_NAME} STATIC ${HDRS} ${SRCS})

qt6_add_plugin(ToggleSwitchPlugin)

target_link_libraries(${PROJECT_NAME} PUBLIC Qt6::Widgets Qt6::Designer)

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