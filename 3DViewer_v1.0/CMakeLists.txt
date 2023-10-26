cmake_minimum_required(VERSION 3.2)

project(viewer VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/modules)

if(${CMAKE_C_COMPILER_ID} STREQUAL "GNU")
    add_compile_options("-Wall" "-Wextra" "-Werror" "-g")
endif()

if((UNIX AND APPLE) AND (${CMAKE_C_COMPILER_ID} STREQUAL "GNU"))
    message("WE NEED CLANG FOR OPENGL ON APPLE -> FOR GUI")
elseif (UNIX AND APPLE)
    message("WE NEED GCC FOR CODE COVERAGE AND COMPILE OPTIONS")
endif()

# Formatting
set(CLANG_FORMAT_EXCLUDE_PATTERNS "build/" "dependencies/" ${CMAKE_BINARY_DIR})
find_package(ClangFormat)

# Tests
set(SOURCES_FOR_BACKEND s21_viewer.c s21_matrix_utils.c s21_affine.c)
add_library(lib_viewer ${SOURCES_FOR_BACKEND})
set(TEST_FILES s21_tests.c)
find_package(Check REQUIRED)
add_executable(test ${SOURCES_FOR_BACKEND} ${TEST_FILES})
target_link_libraries(test PUBLIC lib_viewer ${CHECK_LIBRARIES})
target_include_directories(test PUBLIC ${CHECK_INCLUDE_DIR})
if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" AND CMAKE_BUILD_TYPE STREQUAL "Debug")
include(CodeCoverage)
append_coverage_compiler_flags_to_target(test)
setup_target_for_coverage_lcov(
           NAME test_coverage
           EXECUTABLE test
           DEPENDENCIES test
   )
endif()

# QT
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(SOURCES_FOR_FRONTEND
        qt/main.cpp
        qt/styles.h
        qt/mainwindow.cpp
        qt/mainwindow.h
        qt/mainwindow.ui
        qt/myopenglwidget.cpp
        qt/myopenglwidget.h
        s21_affine.c
        s21_matrix_utils.c
        s21_viewer.c
        s21_viewer.h
)

find_package(QT NAMES Qt6 Qt5 REQUIRED)

file(GLOB giflib_sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/qt/*/*.c ${CMAKE_CURRENT_LIST_DIR}/qt/*/*.cpp ${CMAKE_CURRENT_LIST_DIR}/qt/*/*.h)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGLWidgets OpenGL)
    add_library(giflib ${giflib_sources})
    target_link_libraries(giflib PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::OpenGLWidgets Qt${QT_VERSION_MAJOR}::OpenGL)
else()
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Gui)
    add_library(giflib ${giflib_sources})
    target_link_libraries(giflib PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui)
endif()
target_include_directories(giflib PUBLIC {CMAKE_CURRENT_LIST_DIR}/giflib {CMAKE_CURRENT_LIST_DIR}/gifimage)
target_compile_options(giflib PRIVATE "-w")


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGLWidgets OpenGL)
    qt_add_executable(s21_viewer MANUAL_FINALIZATION ${SOURCES_FOR_FRONTEND})
    target_link_libraries(s21_viewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::OpenGLWidgets Qt${QT_VERSION_MAJOR}::OpenGL giflib)
else()
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Gui)
    add_executable(s21_viewer ${SOURCES_FOR_FRONTEND})
    target_link_libraries(s21_viewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui giflib)
endif()

target_include_directories(s21_viewer PUBLIC ${PROJECT_SOURCE_DIR}/qt/giflib ${PROJECT_SOURCE_DIR}/qt/gifimage)
target_include_directories(s21_viewer PUBLIC ${CMAKE_CURRENT_LIST_DIR}/qt)

set_target_properties(s21_viewer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(s21_viewer)
endif()

# CPACK FOR DIST STANDARD GNU TARGET
SET(CPACK_SOURCE_GENERATOR "TGZ")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME
    "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}")
SET(CPACK_SOURCE_IGNORE_FILES
    "/build/;/buildDebug/;/buildRelease/;${CPACK_SOURCE_IGNORE_FILES}")
include(CPack)
