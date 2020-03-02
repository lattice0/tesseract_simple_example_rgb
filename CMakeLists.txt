cmake_minimum_required(VERSION 3.5)

project(roseek LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(Qt5 COMPONENTS Core Quick REQUIRED)

add_executable(roseek
  main.cpp
  qml.qrc
  ImageStream.cpp
  YuvUtils.cpp
  #CameraView.cpp
)

add_library(ctmedia_codec MODULE IMPORTED)
add_library(ctstream MODULE IMPORTED)
add_library(maincore MODULE IMPORTED)

add_library(tesseract STATIC IMPORTED)
add_library(lept STATIC IMPORTED)
add_library(tiffio STATIC IMPORTED)
add_library(jpeg STATIC IMPORTED)
add_library(png STATIC IMPORTED)
add_library(z STATIC IMPORTED)
add_library(zstd STATIC IMPORTED)
add_library(lzma STATIC IMPORTED)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/mingw-w64-x86_64-static-tesseract/include/tesseract)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/mingw-w64-x86_64-static-tesseract/include/leptonica)

#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/win_bin/lib/x64)
set_target_properties(ctmedia_codec PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/win_bin/lib/x64/CTMedia.lib)
set_target_properties(ctstream PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/win_bin/lib/x64/CTStream.lib)
set_target_properties(maincore PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/win_bin/lib/x64/WPMainCore.lib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/mingw-w64-x86_64-static-tesseract/include/)

set_target_properties(tesseract PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/mingw-w64-x86_64-static-tesseract/lib/libtesseract.a)
set_target_properties(lept PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/mingw-w64-x86_64-static-tesseract/lib/liblept.a)
set_target_properties(tiffio PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/mingw-w64-x86_64-static-tesseract/lib/libtiff.a)
set_target_properties(jpeg PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/mingw-w64-x86_64-static-tesseract/lib/libjpeg.a)
set_target_properties(png PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/mingw-w64-x86_64-static-tesseract/lib/libpng.a)
set_target_properties(z PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/mingw-w64-x86_64-static-tesseract/lib/libz.a)
set_target_properties(zstd PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/mingw-w64-x86_64-static-tesseract/lib/libzstd.a)
set_target_properties(lzma PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/mingw-w64-x86_64-static-tesseract/lib/liblzma.a)


include_directories("include")
#target_compile_definitions(roosek2
#  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
#target_link_libraries(roosek2
#  PRIVATE Qt5::Core Qt5::Quick ctmedia_codec ctstream maincore ${Tesseract_LIBRARIES})
target_link_libraries(roseek ctmedia_codec ctstream maincore tesseract lept tiffio jpeg png z zstd lzma)
#target_link_libraries(roseek ${CMAKE_CURRENT_SOURCE_DIR}/win_bin/lib/x64/WPMainCore.lib ${CMAKE_CURRENT_SOURCE_DIR}/mingw-w64-x86_64-static-tesseract/lib/libtesseract.a)

