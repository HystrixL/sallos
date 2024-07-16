set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE srcs CONFIGURE_DEPENDES src/*.cpp)
add_library(sallos OBJECT ${srcs})
target_include_directories(sallos PUBLIC include)

if (SALLOS_BUILD_EXAMPLE)
    add_subdirectory(example)
endif ()
