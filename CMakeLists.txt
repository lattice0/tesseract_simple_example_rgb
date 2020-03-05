cmake_minimum_required(VERSION 3.5)

project(roseek LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(/usr/include/tesseract/)
include_directories(/usr/include/leptonica/)
find_package(Qt5 COMPONENTS Core Quick REQUIRED)

link_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/mingw-w64-x86_64-static-tesseract/lib/
)
include_directories(libbpm/)
SET(CMAKE_INSTALL_RPATH "${CMAKE_CURRENT_SOURCE_DIR}/libs/linux/")
add_executable(roseek
  libbmp/libbmp.c
  main.cpp
  qml.qrc
  ImageStream.cpp
  YuvUtils.cpp
  utils.cpp
  #jpeg2rgb/src/jpeg_file.cpp
  #jpeg2rgb/src/rgb_file.cpp
  CameraView.cpp
)
#find_package(TurboJPEG REQUIRED)

add_library(ctmedia_codec MODULE IMPORTED)
add_library(ctstream MODULE IMPORTED)
add_library(maincore MODULE IMPORTED)
add_library(jpegutil MODULE IMPORTED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/mingw-w64-x86_64-static-tesseract/include/tesseract)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/mingw-w64-x86_64-static-tesseract/include/leptonica)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/jpeg2rgb/include)

IF (WIN32)
  set_target_properties(ctmedia_codec PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/win/lib/x64/CTMedia.lib)
  set_target_properties(ctstream PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/win/lib/x64/CTStream.lib)
  set_target_properties(maincore PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/win/lib/x64/WPMainCore.lib)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/mingw-w64-x86_64-static-tesseract/include/)
  find_package(OpenMP)
  if (OPENMP_FOUND)
      set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
      set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
  endif()
ELSE()
  set_target_properties(ctmedia_codec PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/linux/libCTMedia_codec.so)
  set_target_properties(ctstream PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/linux/libCTStream.so)
  set_target_properties(maincore PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/linux/libWPMainCore.so)
  set_target_properties(jpegutil PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/linux/libRSJpegUtil.so)
ENDIF()

include_directories("include")
#target_compile_definitions(roosek2
#  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(roseek PRIVATE Qt5::Core Qt5::Quick ctmedia_codec ctstream maincore jpegutil tesseract lept)# turbojpeg)
#target_link_libraries(roseek ctmedia_codec ctstream maincore jpegutil tesseract lept)
#target_link_libraries(roseek ${CMAKE_CURRENT_SOURCE_DIR}/win_bin/lib/x64/WPMainCore.lib ${CMAKE_CURRENT_SOURCE_DIR}/mingw-w64-x86_64-static-tesseract/lib/libtesseract.a)