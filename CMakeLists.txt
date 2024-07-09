cmake_minimum_required(VERSION 3.28)

project(particles CXX)

set(CMAKE_SCRIPTS_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(${CMAKE_SCRIPTS_PATH}/StandardProjectSettings.cmake)
include(${CMAKE_SCRIPTS_PATH}/PreventInSourceBuilds.cmake)
include(${CMAKE_SCRIPTS_PATH}/Cache.cmake)
include(${CMAKE_SCRIPTS_PATH}/CompilerWarnings.cmake)
include(${CMAKE_SCRIPTS_PATH}/Linker.cmake)
include(${CMAKE_SCRIPTS_PATH}/CheckMinimumToolRequirements.cmake)

include_directories(BEFORE
                    SYSTEM
                    src/glm
)

set(TARGET_LIB "particles")

include(${CMAKE_SCRIPTS_PATH}/GetParticlesSources.cmake)
set(Particles_SOURCE_DIR "")
Particles_get_modules("${Particles_SOURCE_DIR}" Particles_modules)
Particles_get_source_files("${Particles_SOURCE_DIR}" Particles_source_files)

add_library(${TARGET_LIB}
            STATIC
            ${Particles_source_files}
)

target_sources(${TARGET_LIB}
               PUBLIC
               FILE_SET CXX_MODULES FILES
               ${Particles_modules}
)

add_library(particles::lib ALIAS ${TARGET_LIB})

set(POS_INDEP_CODE "ON")
set_target_properties(${TARGET_LIB}
                      PROPERTIES
                      POSITION_INDEPENDENT_CODE ${POS_INDEP_CODE}
)

include(ProjectOptions.cmake)
particles_set_project_warnings(${particles_WARNINGS_AS_ERRORS} ${TARGET_LIB})

add_subdirectory(test/cpu_test)


message(STATUS "Particles: CMAKE_CXX_COMPILER_ID          = \"${CMAKE_CXX_COMPILER_ID}\".")
message(STATUS "Particles: CMAKE_CXX_COMPILER_VERSION     = \"${CMAKE_CXX_COMPILER_VERSION}\".")
message(STATUS "Particles: CMAKE_BUILD_TYPE               = \"${CMAKE_BUILD_TYPE}\".")
message(STATUS "Particles: WARNINGS_AS_ERRORS             = \"${WARNINGS_AS_ERRORS}\".")
message(STATUS "Particles: SOME_WARNINGS_OFF              = \"${SOME_WARNINGS_OFF}\".")
message(STATUS "Particles: CMAKE_MODULE_PATH              = \"${CMAKE_MODULE_PATH}\".")
message(STATUS "Particles: CMAKE_SCRIPTS_PATH             = \"${CMAKE_SCRIPTS_PATH}\".")
message(STATUS "Particles: CMAKE_GENERATOR                = \"${CMAKE_GENERATOR}\".")
message(STATUS "Particles: GENERATOR_IS_MULTI_CONFIG      = \"${GENERATOR_IS_MULTI_CONFIG}\".")
message(STATUS "Particles: CMAKE_RUNTIME_OUTPUT_DIRECTORY = \"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}\".")
message(STATUS "Particles: C++ standard                   = \"${CMAKE_CXX_STANDARD}\".")
message(STATUS "Particles: C++ standard required          = \"${CMAKE_CXX_STANDARD_REQUIRED}\".")
message(STATUS "Particles: C++ extensions                 = \"${CMAKE_CXX_EXTENSIONS}\".")
