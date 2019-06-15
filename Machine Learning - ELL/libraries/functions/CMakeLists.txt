set (library_name functions)

set (src src/LogLoss.cpp)

set (include include/LogLoss.h)

source_group("src" FILES ${src})
source_group("include" FILES ${include})

add_library(${library_name} ${src} ${include})
target_include_directories(${library_name} PRIVATE include ${ELL_LIBRARIES_DIR})
target_link_libraries(${library_name} utilities math)

set_property(TARGET ${library_name} PROPERTY FOLDER "libraries")


set (test_name ${library_name}_test)

set (test_src test/src/main.cpp)
set (test_include)

source_group("src" FILES ${test_src})
source_group("include" FILES ${test_include})

add_executable(${test_name} ${test_src} ${test_include} ${include})
target_include_directories(${test_name} PRIVATE test/include ${ELL_LIBRARIES_DIR})
target_link_libraries(${test_name} functions testing utilities math)

set_property(TARGET ${test_name} PROPERTY FOLDER "test")
add_test(NAME ${test_name} COMMAND ${test_name})