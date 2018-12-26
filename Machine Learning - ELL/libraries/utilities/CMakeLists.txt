cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(library_name utilities)

set(src
    src/Files.cpp 
    src/Logger.cpp 
    src/OutputStreamImpostor.cpp
    src/StringUtil.cpp
)

set(include
    include/AbstractInvoker.h
    include/Exception.h
    include/Files.h
    include/Logger.h
    include/OutputStreamImpostor.h
    include/StringUtil.h
)

source_group("src" FILES ${src})
source_group("include" FILES ${include}) 

add_library(${library_name} ${src} ${include})
target_include_directories(${library_name} PRIVATE include ${ELL_LIBRARIES_DIR})

set_property(TARGET ${library_name} PROPERTY FOLDER "libraries")