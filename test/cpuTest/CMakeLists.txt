set(PROJECT_NAME cpuTest)

# Source groups
set(no_group_source_files
        "cpuTest.cpp"
        )
source_group("" FILES ${no_group_source_files})

set(effects
        "${SRC_DIR}/particles/effects/effect.h"
        "${SRC_DIR}/particles/effects/attractorEffect.cpp"
        "${SRC_DIR}/particles/effects/fountainEffect.cpp"
        "${SRC_DIR}/particles/effects/tunnelEffect.cpp"
        )
source_group("effects" FILES ${effects})

set(particles
        "${SRC_DIR}/particles/particleGenerators.cpp"
        "${SRC_DIR}/particles/particles.cpp"
        "${SRC_DIR}/particles/particleUpdaters.cpp"
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
        "${SRC_DIR}"
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
