cmake_minimum_required(VERSION 3.10)

project(SituacionProblema)

# Set the C++ standard to C++17 (for filesystem support)
set(CMAKE_CXX_STANDARD 17)

# Include the 'include' directory for headers
include_directories(include)

# Find all .cpp files in the 'src' directory
file(GLOB SOURCES "src/*.cpp")

# Specify the folder where the executable will be generated (root of the project)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})  # This sets the output directory to the root

# Create the executable from the sources
add_executable(SituacionProblema ${SOURCES})

# Custom rule to run the program automatically after building
add_custom_target(run
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SituacionProblema  # Execute from the root directory
    DEPENDS SituacionProblema
)

# Ensure that the 'run' target depends on 'SituacionProblema'
add_dependencies(run SituacionProblema)

# Ensure the program runs when make is called
add_custom_target(make_and_run ALL
    DEPENDS run
)
