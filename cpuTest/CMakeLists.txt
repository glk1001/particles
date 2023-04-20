set(PROJECT_NAME cpuTest)

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH PARENT_DIR)

# Source groups
set(no_group_source_files
        "cpuTest.cpp"
        )
source_group("" FILES ${no_group_source_files})

set(effects
        "${PARENT_DIR}/particlesCode/attractorEffect.cpp"
        "${PARENT_DIR}/particlesCode/fountainEffect.cpp"
        "${PARENT_DIR}/particlesCode/tunnelEffect.cpp"
        )
source_group("effects" FILES ${effects})

set(particles
        "${PARENT_DIR}/particlesCode/particleGenerators.cpp"
        "${PARENT_DIR}/particlesCode/particles.cpp"
        "${PARENT_DIR}/particlesCode/particleUpdaters.cpp"
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
        "${PARENT_DIR}"
        )

target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
        "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
        "NDEBUG"
        ">"
        )

set_project_warnings(cpuTest)
