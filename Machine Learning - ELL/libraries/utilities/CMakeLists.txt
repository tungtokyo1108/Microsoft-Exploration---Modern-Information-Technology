cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# set(library_name utilities)
set(library_name utilities)
find_package(Threads)

set(src
    src/Archiver.cpp
    src/ArchiveVersion.cpp
    src/Boolean.cpp
    src/CommandLineParser.cpp
    src/CompressedIntegerList.cpp
    src/CStringParser.cpp
    src/Files.cpp
    src/Format.cpp 
    src/Logger.cpp 
    src/OutputStreamImpostor.cpp
    src/StringUtil.cpp
    src/TypeName.cpp
)

set(include
    include/AbstractInvoker.h
    include/Archiver.h
    include/ArchiveVersion.h
    include/IArchivable.h
    include/Boolean.h
    include/CommandLineParser.h
    include/CompressedIntegerList.h
    include/CStringParser.h
    include/Debug.h
    include/Exception.h
    include/Files.h
    include/Format.h
    include/Logger.h
    include/OutputStreamImpostor.h
    include/ParallelTransformIterator.h
    include/StringUtil.h
    include/StlStridedIterator.h
    include/StlContainerIterator.h
    include/TransformIterator.h
    include/TypeFactory.h
    include/TypeName.h
    include/TypeTraits.h
    include/Unused.h
)

#source_group("src" FILES ${src})
#source_group("include" FILES ${include}) 
source_group("src" FILES ${src})
source_group("include" FILES ${include})


#add_library(${library_name} ${src} ${include})
#target_include_directories(${library_name} PRIVATE include ${ELL_LIBRARIES_DIR})

add_library(${library_name} ${src} ${include})
target_include_directories(${library_name} PRIVATE include ${ELL_LIBRARIES_DIR})
target_link_libraries(${library_name} Threads::Threads)

#set_property(TARGET ${library_name} PROPERTY FOLDER "libraries")
set_property(TARGET ${library_name} PROPERTY FOLDER "libraries")


############################## Test Section ##################################################

set(test_name ${library_name}_test)
set(test_src
    test/src/main.cpp 
    test/src/Files_test.cpp
    test/src/Iterator_test.cpp
)

set(test_include
    test/include/Files_test.h
    test/include/Iterator_test.h
)

source_group("src" FILES ${test_src})
source_group("include" FILES ${test_include})

add_executable(${test_name} ${test_src} ${test_include} ${include})
target_include_directories(${test_name} PRIVATE test/include ${ELL_LIBRARIES_DIR})

target_link_libraries(${test_name} utilities testing)
target_link_libraries(${test_name} Threads::Threads)

set_property(TARGET ${test_name} PROPERTY FOLDER "tests")
add_test(NAME ${test_name} COMMAND ${test_name})
