cmake_minimum_required(VERSION 3.21)

# Set the target architecture.
# All modern x86/x64 processors support AVX2.
# Older x86/x64 processors may support SSE2 but not AVX2.
# Very old x86/x64 processors, or non x86/x64
# processors, do not support any of the two.
set(ENABLE_SSE2 True)
set(ENABLE_AVX2 True)


# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name
project(mesh_booleans)

set(TBB_TEST OFF CACHE BOOL " " FORCE)
set(TBB_EXAMPLES OFF CACHE BOOL " " FORCE)
add_subdirectory(arrangements/external/oneTBB)


# add the executable
add_executable(${PROJECT_NAME} main.cpp
        rationals_code/intersect_custom.h rationals_code/intersect_custom.cpp
        rationals_code/intersect_point_rationals.h rationals_code/intersect_point_rationals.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ./
    code/
    arrangements/code/
    arrangements/external/Indirect_Predicates/include/
        rationals_code/
)


add_executable(${PROJECT_NAME}_bug main_bug.cpp
        rationals_code/intersect_custom.h rationals_code/intersect_custom.cpp
        rationals_code/intersect_point_rationals.h rationals_code/intersect_point_rationals.cpp
)

target_include_directories(${PROJECT_NAME}_bug PUBLIC
        ./
        code/
        arrangements/code/
        arrangements/external/Indirect_Predicates/include/
        rationals_code/
)

set(cinolib_DIR ${PROJECT_SOURCE_DIR}/arrangements/external/Cinolib)
set(CINOLIB_USES_OPENGL_GLFW_IMGUI   ON)
set(CINOLIB_USES_SHEWCHUK_PREDICATES ON)
set(CINOLIB_USES_CGAL_GMP_MPFR       ON)

find_package(CGAL REQUIRED COMPONENTS Core)
target_link_libraries(mesh_booleans CGAL::CGAL)
find_package(cinolib REQUIRED)



target_link_libraries(${PROJECT_NAME} cinolib)
target_link_libraries(${PROJECT_NAME} tbb)
target_compile_definitions(${PROJECT_NAME} PUBLIC TBB_PARALLEL=1)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/arrangements/external/abseil-cpp/)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/arrangements/external/oneTBB/)



target_link_libraries(${PROJECT_NAME}_bug cinolib)
target_link_libraries(${PROJECT_NAME}_bug tbb)
target_link_libraries(${PROJECT_NAME}_bug CGAL::CGAL)

find_package(CGAL REQUIRED COMPONENTS Core)

# Check if CGAL::Core exists before linking
if(TARGET CGAL::Core)
        target_link_libraries(${PROJECT_NAME} CGAL::Core)
        target_link_libraries(${PROJECT_NAME}_bug CGAL::Core)
else()
        target_link_libraries(${PROJECT_NAME} CGAL::CGAL)
        target_link_libraries(${PROJECT_NAME}_bug CGAL::CGAL)
endif()


target_compile_definitions(${PROJECT_NAME}_bug PUBLIC TBB_PARALLEL=1)
target_include_directories(${PROJECT_NAME}_bug PUBLIC ${PROJECT_SOURCE_DIR}/arrangements/external/abseil-cpp/)
target_include_directories(${PROJECT_NAME}_bug PUBLIC ${PROJECT_SOURCE_DIR}/arrangements/external/oneTBB/)






add_executable(${PROJECT_NAME}_rotation main-rotation.cpp)

target_include_directories(${PROJECT_NAME}_rotation PUBLIC
    ./
    code/
    arrangements/code/
    arrangements/external/Indirect_Predicates/include/
)

target_link_libraries(${PROJECT_NAME}_rotation cinolib)
target_link_libraries(${PROJECT_NAME}_rotation tbb)
target_compile_definitions(${PROJECT_NAME}_rotation PUBLIC TBB_PARALLEL=1)
target_include_directories(${PROJECT_NAME}_rotation PUBLIC ${PROJECT_SOURCE_DIR}/arrangements/external/abseil-cpp/)
target_include_directories(${PROJECT_NAME}_rotation PUBLIC ${PROJECT_SOURCE_DIR}/arrangements/external/oneTBB/)

add_executable(${PROJECT_NAME}_arap main-arap.cpp)

target_include_directories(${PROJECT_NAME}_arap PUBLIC
    ./
    code/
    arrangements/code/
    arrangements/external/Indirect_Predicates/include/
)

target_link_libraries(${PROJECT_NAME}_arap cinolib)
target_link_libraries(${PROJECT_NAME}_arap tbb)
target_compile_definitions(${PROJECT_NAME}_arap PUBLIC TBB_PARALLEL=1)
target_include_directories(${PROJECT_NAME}_arap PUBLIC ${PROJECT_SOURCE_DIR}/arrangements/external/abseil-cpp/)
target_include_directories(${PROJECT_NAME}_arap PUBLIC ${PROJECT_SOURCE_DIR}/arrangements/external/oneTBB/)

add_executable(${PROJECT_NAME}_stencil main-stencil.cpp)

target_include_directories(${PROJECT_NAME}_stencil PUBLIC
    ./
    code/
    arrangements/code/
    arrangements/external/Indirect_Predicates/include/
        rationals_code/
)

target_link_libraries(${PROJECT_NAME}_stencil cinolib)
target_link_libraries(${PROJECT_NAME}_stencil tbb)
target_compile_definitions(${PROJECT_NAME}_stencil PUBLIC TBB_PARALLEL=1)
target_include_directories(${PROJECT_NAME}_stencil PUBLIC ${PROJECT_SOURCE_DIR}/arrangements/external/abseil-cpp/)
target_include_directories(${PROJECT_NAME}_stencil PUBLIC ${PROJECT_SOURCE_DIR}/arrangements/external/oneTBB/)


add_executable(${PROJECT_NAME}_inputcheck main-inputcheck.cpp)

target_include_directories(${PROJECT_NAME}_inputcheck PUBLIC
        ./
        code/
        arrangements/code/
        arrangements/external/Indirect_Predicates/include/
)

target_link_libraries(${PROJECT_NAME}_inputcheck cinolib)
target_link_libraries(${PROJECT_NAME}_inputcheck tbb)
target_compile_definitions(${PROJECT_NAME}_inputcheck PUBLIC TBB_PARALLEL=1)
target_include_directories(${PROJECT_NAME}_inputcheck PUBLIC ${PROJECT_SOURCE_DIR}/arrangements/external/abseil-cpp/)
target_include_directories(${PROJECT_NAME}_inputcheck PUBLIC ${PROJECT_SOURCE_DIR}/arrangements/external/oneTBB/)

# Compiler-specific options
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        # grant IEEE 754 compliance
        target_compile_options(${PROJECT_NAME} PUBLIC "/fp:strict")
        # use intrinsic functions
        target_compile_options(${PROJECT_NAME} PUBLIC "/Oi")
        # set target architecture
        if(ENABLE_AVX2)
                target_compile_options(${PROJECT_NAME} PUBLIC "/arch:AVX2")
        elseif(ENABLE_SSE2)
                target_compile_options(${PROJECT_NAME} PUBLIC "/arch:SSE2")
        endif()
        # reserve enough stack size
        target_link_options(${PROJECT_NAME} PUBLIC "/STACK:8421376")
        # turn off annoying warnings
        target_compile_options(${PROJECT_NAME} PUBLIC "/D _CRT_SECURE_NO_WARNINGS")
else()
        # set standard optimization level
        target_compile_options(${PROJECT_NAME} PUBLIC -O2)
        # reserve enough stack size
        target_compile_options(${PROJECT_NAME} PUBLIC -Wl,-z,stacksize=8421376)
        # grant IEEE 754 compliance
        target_compile_options(${PROJECT_NAME} PUBLIC -frounding-math)
        # set target architecture
        if(ENABLE_AVX2)
                target_compile_options(${PROJECT_NAME} PUBLIC "-mavx2")
        elseif(ENABLE_SSE2)
                target_compile_options(${PROJECT_NAME} PUBLIC "-msse2")
        endif()
endif()
