cmake_minimum_required(VERSION 3.5)

project(roosek2 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)
include_directories(yuv2rgb)

add_executable(roosek2
  main.cpp
  qml.qrc
  ImageStream.cpp
  yuv2rgb/yuv2rgb.cpp
  CameraView.cpp
)

add_library(ctmedia_codec MODULE IMPORTED)
add_library(ctstream MODULE IMPORTED)
add_library(maincore MODULE IMPORTED)

#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/win_bin/lib/x64)
set_target_properties(ctmedia_codec PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/win_bin/lib/win32/CTMedia.lib)
set_target_properties(ctstream PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/win_bin/lib/win32/CTStream.lib)
set_target_properties(maincore PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/win_bin/lib/win32/WPMainCore.lib)

include_directories("include")
target_compile_definitions(roosek2
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(roosek2
  PRIVATE Qt5::Core Qt5::Quick ctmedia_codec ctstream maincore)
