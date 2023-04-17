project(particles C CXX)
cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_SCRIPTS_PATH "cmake")

include(${CMAKE_SCRIPTS_PATH}/StandardProjectSettings.cmake)
include(${CMAKE_SCRIPTS_PATH}/PreventInSourceBuilds.cmake)
include(${CMAKE_SCRIPTS_PATH}/Cache.cmake)
include(${CMAKE_SCRIPTS_PATH}/Linker.cmake)
include(${CMAKE_SCRIPTS_PATH}/CompilerWarnings.cmake)
include(${CMAKE_SCRIPTS_PATH}/Sanitizers.cmake)
include(${CMAKE_SCRIPTS_PATH}/StaticAnalyzers.cmake)
include(${CMAKE_SCRIPTS_PATH}/CheckMinimumToolRequirements.cmake)

include_directories(BEFORE
                    SYSTEM
                    glm
                    )

add_subdirectory(cpuTest)

message(STATUS "LSys: CMAKE_CXX_COMPILER_ID = \"${CMAKE_CXX_COMPILER_ID}\".")
message(STATUS "LSys: CMAKE_CXX_COMPILER_VERSION = \"${CMAKE_CXX_COMPILER_VERSION}\".")
message(STATUS "LSys: CMAKE_BUILD_TYPE = \"${CMAKE_BUILD_TYPE}\".")
message(STATUS "LSys: WARNINGS_AS_ERRORS = \"${WARNINGS_AS_ERRORS}\".")
message(STATUS "LSys: SOME_WARNINGS_OFF = \"${SOME_WARNINGS_OFF}\".")
message(STATUS "LSys: CMAKE_MODULE_PATH = \"${CMAKE_MODULE_PATH}\".")
message(STATUS "LSys: CMAKE_SCRIPTS_PATH = \"${CMAKE_SCRIPTS_PATH}\".")
message(STATUS "LSys: CMAKE_GENERATOR = \"${CMAKE_GENERATOR}\".")
message(STATUS "LSys: GENERATOR_IS_MULTI_CONFIG = \"${GENERATOR_IS_MULTI_CONFIG}\".")
message(STATUS "LSys: CMAKE_RUNTIME_OUTPUT_DIRECTORY = \"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}\".")
message(STATUS "LSys: C++ standard = \"${CMAKE_CXX_STANDARD}\".")
message(STATUS "LSys: C++ standard required = \"${CMAKE_CXX_STANDARD_REQUIRED}\".")
message(STATUS "LSys: C++ extensions = \"${CMAKE_CXX_EXTENSIONS}\".")
