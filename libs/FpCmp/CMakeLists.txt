
set(LIB_NAME FpCmp)

# Create a library target
add_library(${LIB_NAME} INTERFACE)
target_include_directories(${LIB_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Set C++ standard
target_compile_features(${LIB_NAME} INTERFACE cxx_std_17)

# Add the source/header files
target_sources(${LIB_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/FpCmp.hpp)

# Create an alias for convenient usage
add_library(FloatingPoint::Comparison ALIAS ${LIB_NAME} )

add_library(${LIB_NAME}_shared SHARED)
target_sources(${LIB_NAME}_shared PRIVATE ${CMAKE_CURRENT_LIST_DIR}/source/FpCmp.cpp)
target_include_directories(${LIB_NAME}_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${LIB_NAME}_shared PRIVATE FloatingPoint::Comparison)
set_target_properties(${LIB_NAME}_shared PROPERTIES OUTPUT_NAME FpCmp)
install(TARGETS ${LIB_NAME}_shared LIBRARY DESTINATION lib)

# Optionally, build as a static library
add_library(${LIB_NAME}_static STATIC)
target_sources(${LIB_NAME}_static PRIVATE ${CMAKE_CURRENT_LIST_DIR}/source/FpCmp.cpp)
target_include_directories(${LIB_NAME}_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${LIB_NAME}_static PRIVATE FloatingPoint::Comparison)
set_target_properties(${LIB_NAME}_static PROPERTIES OUTPUT_NAME FpCmp)
install(TARGETS ${LIB_NAME}_static ARCHIVE DESTINATION lib)

# Installation
install(FILES FpCmp.h DESTINATION include)


# Testing # if enable_testing() is called in the root CMakeLists.txt
add_subdirectory(test)
