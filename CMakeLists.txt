set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE srcs CONFIGURE_DEPENDES src/*.cpp)
add_library(sallos OBJECT ${srcs})
target_include_directories(sallos PUBLIC include)
target_include_directories(sallos PRIVATE /usr/lib/llvm-17/lib/clang/17)

if (SALLOS_BUILD_EXAMPLE)
    add_subdirectory(example)
endif ()
