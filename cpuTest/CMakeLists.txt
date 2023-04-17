set(PROJECT_NAME cpuTest)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "cpuTest.cpp"
)
source_group("" FILES ${no_group_source_files})

set(effects
    "../particlesCode/attractorEffect.cpp"
    "../particlesCode/attractorEffect.h"
    "../particlesCode/effect.cpp"
    "../particlesCode/effect.h"
    "../particlesCode/fountainEffect.cpp"
    "../particlesCode/fountainEffect.h"
    "../particlesCode/tunnelEffect.cpp"
    "../particlesCode/tunnelEffect.h"
)
source_group("effects" FILES ${effects})

set(particles
    "../particlesCode/particleGenerators.cpp"
    "../particlesCode/particleGenerators.h"
    "../particlesCode/particleRenderer.cpp"
    "../particlesCode/particleRenderer.h"
    "../particlesCode/particles.cpp"
    "../particlesCode/particles.h"
    "../particlesCode/particleUpdaters.cpp"
    "../particlesCode/particleUpdaters.h"
    "fake_glParticleRenderer.cpp"
)
source_group("particles" FILES ${particles})

set(ALL_FILES
    ${no_group_source_files}
    ${effects}
    ${particles}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
)
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../particlesCode"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:"
        "_DEBUG"
    ">"
    "$<$<CONFIG:Release>:"
        "NDEBUG"
    ">"
)

# set_project_warnings(cpuTest)
