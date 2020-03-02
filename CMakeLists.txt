cmake_minimum_required(VERSION 3.5)

project(roseek LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(Qt5 COMPONENTS Core Quick REQUIRED)
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()
link_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/mingw-w64-x86_64-static-tesseract/lib/
)
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




include_directories(${CMAKE_CURRENT_SOURCE_DIR}/mingw-w64-x86_64-static-tesseract/include/tesseract)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/mingw-w64-x86_64-static-tesseract/include/leptonica)

#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/win_bin/lib/x64)
set_target_properties(ctmedia_codec PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/win_bin/lib/x64/CTMedia.lib)
set_target_properties(ctstream PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/win_bin/lib/x64/CTStream.lib)
set_target_properties(maincore PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/win_bin/lib/x64/WPMainCore.lib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/mingw-w64-x86_64-static-tesseract/include/)

include_directories("include")
#target_compile_definitions(roosek2
#  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
#target_link_libraries(roosek2
#  PRIVATE Qt5::Core Qt5::Quick ctmedia_codec ctstream maincore ${Tesseract_LIBRARIES})
target_link_libraries(roseek ctmedia_codec ctstream maincore
    tesseract
    lept
    openjp3d
    openjpwl
    openmj2
    jpeg
    pango-1.0
    pangocairo-1.0
    pangoft2-1.0
    pangowin32-1.0
    harfbuzz-gobject
    harfbuzz-icu
    harfbuzz-subset
    harfbuzz
    cairo
    pixman-1
    graphite2
    glib-2.0
    gio-2.0
    gmodule-2.0
    gobject-2.0
    gthread-2.0
    tiff
    gif
    webp
    asprintf
    charset
    crypto
    datrie
    archive
    expat
    ffi
    fontconfig
    formw
    fribidi
    gettextlib
    gettextpo
    gmp
    gmpxx
    gnurx
    png
    freetype
    openjp2
    history
    iconv
    icudt
    icuin
    icuio
    icutest
    icutu
    icuuc
    z
    intl
    lcms2
    lzma
    panelw
    pcre
    pcre16
    pcre32
    pcrecpp
    pcreposix
    png16
    readline
    regex
    sqlite3
    ws2_32
    bz2
    ssl
    tasn1
    thai
    tre
    turbojpeg
    zstd
    lzo2
    menuw
    mpc
    mpdec
    mpfr
    ncurses
    ncurses++w
    ncurses++w_g
    tiffxx
    tkstub86
    webpdecoder
    webpdemux
    webpmux
    ncursesw
    ncursesw_g
    bcrypt
    systre
    ole32
    winmm
    shlwapi
    stdc++
    user32
    kernel32
    gdi32
    comdlg32
    psapi
    wsock32
    hogweed
    nettle
    lz4
    m
    rpcrt4)
#target_link_libraries(roseek ${CMAKE_CURRENT_SOURCE_DIR}/win_bin/lib/x64/WPMainCore.lib ${CMAKE_CURRENT_SOURCE_DIR}/mingw-w64-x86_64-static-tesseract/lib/libtesseract.a)

