set(PROJECT_NAME cpuTest)

# Source groups
set(no_group_source_files
        "cpu_test.cpp"
        )
source_group("" FILES ${no_group_source_files})

set(effects
        "${INC_DIR}/particles/effects/effect.h"
        "${SRC_DIR}/particles/effects/attractor_effect.cpp"
        "${SRC_DIR}/particles/effects/fountain_effect.cpp"
        "${SRC_DIR}/particles/effects/tunnel_effect.cpp"
        )
source_group("effects" FILES ${effects})

set(particles
        "${SRC_DIR}/particles/particle_generators.cpp"
        "${SRC_DIR}/particles/particle_updaters.cpp"
        "${SRC_DIR}/particles/particles.cpp"
        )
source_group("particles" FILES ${particles})

set(ALL_FILES
        ${no_group_source_files}
        ${effects}
        ${particles}
        )

# Target
add_executable(${PROJECT_NAME} ${ALL_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        "${INC_DIR}"
        )

target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
        "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
        "NDEBUG"
        ">"
        )

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        m
        stdc++
        )

set_project_warnings(cpuTest)

message(STATUS "CpuTest: INC_DIR = \"${INC_DIR}\".")
message(STATUS "CpuTest: SRC_DIR = \"${SRC_DIR}\".")
