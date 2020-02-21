cmake_minimum_required(VERSION 3.8.2)

project(INGREEDYENTS VERSION 0.0.1 LANGUAGES CXX)

#---------------------------------------------------------------------------------------------------
# Find files for this repository - this needs to be updated for every new src file.
#---------------------------------------------------------------------------------------------------
set(SOURCES
    app/main.cpp
    src/example.cpp
)
set(TESTFILES
#    tests/main.cpp
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

set_target_properties(
  ${LIBRARY_NAME} ${LIBRARY_NAME}_main
    PROPERTIES
      CXX_STANDARD 17
      CXX_STANDARD_REQUIRED YES
      CXX_EXTENSIONS NO
)