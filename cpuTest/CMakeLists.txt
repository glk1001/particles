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

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE cpuTest)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
)
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../ext;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../commonCode;"
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
    "WIN32;"
    "_CONSOLE;"
    "_LIB"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /Od
        >
        $<$<CONFIG:Release>:
            /Ox;
            /Oi;
            /arch:AVX;
            /Oy;
            /Ot;
            /fp:fast
        >
        /W3;
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
    )
    string(CONCAT FILE_CL_OPTIONS
        "$<$<CONFIG:Release>:"
            "/Qpar-report:2"
        ">"
    )
    source_file_compile_options(../particlesCode/particleUpdaters.cpp ${FILE_CL_OPTIONS})
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /INCREMENTAL
        >
        $<$<CONFIG:Release>:
            /OPT:REF;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        /DEBUG;
        /SUBSYSTEM:CONSOLE
    )
endif()

