cmake_minimum_required(VERSION 3.9) # Check the CMake version.

project (Teaching) # Project name

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})


# Add capabilities C++14
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)


# =============================================================================
# QT CONFIG
# =============================================================================
# Use specific Qt version
# set(QT_VERSION "5.12")

# Project options
if (WIN32)
	set(QT_DIR_DEFAULT_VAL "")
else()
	set(QT_DIR_DEFAULT_VAL "/opt/Qt/5.12.3/gcc_64")
endif()

set(QT_DIR ${QT_DIR_DEFAULT_VAL} CACHE PATH "Qt libs search path")

if(EXISTS ${QT_DIR})
   list(APPEND CMAKE_PREFIX_PATH ${QT_DIR})
endif()

find_package(Qt5 ${QT_VERSION} COMPONENTS Core Charts Qml Widgets
	Network Sql Xml Quick QuickWidgets Multimedia
	WebSockets SerialBus SerialPort Test REQUIRED)

# Automatic handling of moc preprocessor
set(CMAKE_AUTOMOC ON)
# Automatic handling of uic preprocessor
set(CMAKE_AUTOUIC ON)
# Automatic handling of rcc preprocessor
set(CMAKE_AUTORCC ON)

# =============================================================================

# Global include dir for all projects
include_directories("${PROJECT_SOURCE_DIR}/include")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(HDR_GROUP_PREFIX "root")
set(SRC_GROUP_PREFIX "root")
set(UI_GROUP_PREFIX "root")

add_subdirectory(src)

message("Create root project '" ${PROJECT_NAME} "' is done")