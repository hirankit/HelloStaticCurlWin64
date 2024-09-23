cmake_minimum_required(VERSION 3.19)
project(HelloCurl C)

# Specify the C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Define runtime library flags
if(MSVC)
    set(MULTITHREADED_FLAG "$<$<CONFIG:Debug>:MultiThreadedDebug>$<$<NOT:$<CONFIG:Debug>>:MultiThreaded>")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "${MULTITHREADED_FLAG}")
endif()

# Find packages
find_package(CURL REQUIRED)
find_package(ZLIB REQUIRED)

# Add executable
add_executable(HelloCurl src/main.c)

# Include directories
target_include_directories(HelloCurl PRIVATE ${CURL_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIRS})

# Link against the static libraries
target_link_libraries(HelloCurl PRIVATE CURL::libcurl ZLIB::ZLIB)

# Ensure static linking
set_target_properties(HelloCurl PROPERTIES
    LINK_SEARCH_START_STATIC ON
    LINK_SEARCH_END_STATIC ON
)