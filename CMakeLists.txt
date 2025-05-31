cmake_minimum_required(VERSION 3.25)
project(ZombieGame)
set(CMAKE_CXX_STANDARD 17)

# Set the binary exe file to a bin folder inside the build folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB SOURCE Main.cpp src/*.cpp src/*.h)
#Grab all cpp files from src
add_executable(ZombieGame ${SOURCE})

#Download SFML
Set(FETCHCONTENT_QUIET FALSE)

include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        2.6.2
        GIT_PROGRESS TRUE
)
set(SFML_STATIC_LIBRARIES TRUE CACHE BOOL "Use SFML as static" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libs" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_USE_SYSTEM_DEPS OFF CACHE BOOL "Use system dependencies" FORCE)

FetchContent_MakeAvailable(SFML)



#Static link gcc runtime and c++ standard library
if((CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")  AND CMAKE_SYSTEM_NAME STREQUAL "Windows")
    #GNU SPECIFIC WINDOWS SPECIFIC
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++")
endif()


#Set sfml as static UNLESS os is linux
if(NOT CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(SFML_STATIC_LIBRARIES TRUE)
endif()

#Keep public - SFML static must be  known to all files
target_compile_definitions(ZombieGame PUBLIC SFML_STATIC)

# Link SFML - must be public for game to use
target_link_libraries(ZombieGame PUBLIC sfml-graphics sfml-window sfml-system)

# Include the assets required to run the project - change if necessary
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/media ${CMAKE_BINARY_DIR}/bin/media
)