cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(library_name math)

if (MSVC)
add_compile_options(-D_SCL_SECURE_NO_WARNINGS)
endif()

#include(OpenBLAS)
find_package(blas)

set(src src/BlasWrapper.cpp
)

set(include include/BlasWrapper.h
            include/Common.h
            include/Matrix.h
            include/Vector.h
)

source_group("src" FILES ${src})
source_group("include" FILES ${include})

add_library(${library_name} ${src} ${include})
target_include_directories(${library_name} PRIVATE include ${ELL_LIBRARIES_DIR})
target_include_directories(${library_name} SYSTEM PUBLIC ${BLAS_INCLUDE_DIRS})
target_link_libraries(${library_name} utilities ${BLAS_LIBS})

if(BLAS_FOUND)
target_compile_definitions(${library_name} PUBLIC USE_BLAS=1)
endif()

set_property(TARGET ${library_name} PROPERTY FOLDER "libraries")


############################## Test Section ##################################################

set(test_name ${library_name}_test)

set(test_src test/src/main.cpp)
set(test_include test/include/Vector_test.h)

source_group("src" FILES ${test_src})
source_group("include" FILES ${test_include})

add_executable(${test_name} ${test_src} ${test_include} ${include})
target_include_directories(${test_name} PRIVATE test/include ${ELL_LIBRARIES_DIR})
target_link_libraries(${test_name} math testing)
# copy_shared_libraries(${test_name})

set_property(TARGET ${test_name} PROPERTY FOLDER "tests")

add_test(NAME ${test_name} COMMAND ${test_name})
# set_test_library_path(${test_name})
