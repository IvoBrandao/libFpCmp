cmake_minimum_required(VERSION 3.25)

project(FPComparison VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(GNUInstallDirs)
include(FetchContent)
include(CTest)


FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG f8d7d77c06936315286eb55f8de22cd23c188571
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

# add folder for libraries
add_subdirectory(libs)

# add an executable as an example
add_executable(FPComparison ${CMAKE_CURRENT_LIST_DIR}/source/main.cpp)

# add the include directory to the executable
target_include_directories(FPComparison 
PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)

# link the library to the executable
target_link_libraries(FPComparison FpCmp)

# Testing
enable_testing()
