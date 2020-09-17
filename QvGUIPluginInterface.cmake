cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

if(NOT QV_QT_LIBNAME)
    set(QV_QT_LIBNAME Qt5)
    set(QV_QT_MAJOR_VERSION 5)
    set(QV_QT_MINOR_VERSION 11)
endif()

find_package(${QV_QT_LIBNAME} ${QV_QT_MAJOR_VERSION}.${QV_QT_MINOR_VERSION} COMPONENTS Gui Widgets)

set(QVGUIPLUGIN_INTERFACE_HEADERS
    ${QVPLUGIN_INTERFACE_INCLUDE_DIR}/QvGUIPluginInterface.hpp)

list(APPEND QV2RAY_QT_LIBS ${QV_QT_LIBNAME}::Gui ${QV_QT_LIBNAME}::Widgets)
