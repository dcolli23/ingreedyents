cmake_minimum_required(VERSION 3.8.2)

project(INGREEDYENTS VERSION 0.0.1 LANGUAGES CXX)

#---------------------------------------------------------------------------------------------------
# Googletest setup
#---------------------------------------------------------------------------------------------------
# Download and unpack Googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if (result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker settings on Windows
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

#---------------------------------------------------------------------------------------------------
# Find files for this repository - this needs to be updated for every new src file.
#---------------------------------------------------------------------------------------------------
set(SOURCES
    app/main.cpp
    src/example.cpp
)
set(TESTFILES
    tests/Example_Test.cpp
)
set(LIBRARY_NAME ingreedyents) # Default name for library built from src

#---------------------------------------------------------------------------------------------------
# Build stuff - also change when needed.
#---------------------------------------------------------------------------------------------------
# Compile to library.
add_library(${LIBRARY_NAME} OBJECT ${SOURCES})

# Include headers.
#target_include_directories(${LIBRARY_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
include_directories(include)
include_directories(external/include)

add_executable(${LIBRARY_NAME}_main ${SOURCES})

#target_include_directories(${LIBRARY_NAME}_main PRIVATE ${PROJECT_SOURCE_DIR}/include)


# Link the executable to the library.
# NOTE: we don't have to do this yet since we don't make any libraries at the moment.
#target_link_libraries(main PRIVATE ${LIBRARY_NAME}) # Link executable to the library.

# Link the googletest library with the executable
#target_link_libraries(${LIBRARY_NAME}_main gtest_main)
#add_test(NAME Example_Test COMMAND ${LIBRARY_NAME}_main)

add_executable(my_tests ${TESTFILES} src/example.cpp)
target_link_libraries(my_tests gtest_main)

set_target_properties(
  ${LIBRARY_NAME} ${LIBRARY_NAME}_main
    PROPERTIES
      CXX_STANDARD 17
      CXX_STANDARD_REQUIRED YES
      CXX_EXTENSIONS NO
)