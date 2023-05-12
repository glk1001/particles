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
        src/glm
        )

set(TARGET_LIB "particles")

add_library(${TARGET_LIB}
        STATIC
        "include/particles/effects/effect.h"
        "src/particles/effects/attractor_effect.cpp"
        "src/particles/effects/fountain_effect.cpp"
        "src/particles/effects/tunnel_effect.cpp"
        "src/particles/particle_generators.cpp"
        "src/particles/particle_updaters.cpp"
        "src/particles/particles.cpp"
        )

add_library(particles::lib ALIAS ${TARGET_LIB})

target_include_directories(${TARGET_LIB}
        PUBLIC
        include
        )

set(POS_INDEP_CODE "ON")
set_target_properties(${TARGET_LIB}
        PROPERTIES
        POSITION_INDEPENDENT_CODE ${POS_INDEP_CODE}
        )

set_project_warnings(${TARGET_LIB} ${TARGET_APP})

add_subdirectory(test/cpu_test)

message(STATUS "Particles: CMAKE_CXX_COMPILER_ID = \"${CMAKE_CXX_COMPILER_ID}\".")
message(STATUS "Particles: CMAKE_CXX_COMPILER_VERSION = \"${CMAKE_CXX_COMPILER_VERSION}\".")
message(STATUS "Particles: CMAKE_BUILD_TYPE = \"${CMAKE_BUILD_TYPE}\".")
message(STATUS "Particles: WARNINGS_AS_ERRORS = \"${WARNINGS_AS_ERRORS}\".")
message(STATUS "Particles: SOME_WARNINGS_OFF = \"${SOME_WARNINGS_OFF}\".")
message(STATUS "Particles: CMAKE_MODULE_PATH = \"${CMAKE_MODULE_PATH}\".")
message(STATUS "Particles: CMAKE_SCRIPTS_PATH = \"${CMAKE_SCRIPTS_PATH}\".")
message(STATUS "Particles: CMAKE_GENERATOR = \"${CMAKE_GENERATOR}\".")
message(STATUS "Particles: GENERATOR_IS_MULTI_CONFIG = \"${GENERATOR_IS_MULTI_CONFIG}\".")
message(STATUS "Particles: CMAKE_RUNTIME_OUTPUT_DIRECTORY = \"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}\".")
message(STATUS "Particles: C++ standard = \"${CMAKE_CXX_STANDARD}\".")
message(STATUS "Particles: C++ standard required = \"${CMAKE_CXX_STANDARD_REQUIRED}\".")
message(STATUS "Particles: C++ extensions = \"${CMAKE_CXX_EXTENSIONS}\".")
