cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME cpuTest)

add_executable(${PROJECT_NAME}
        "cpu_test.cpp"
        )

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
        ${TARGET_LIB}
        m
        stdc++
        )

particles_set_project_warnings(${particles_WARNINGS_AS_ERRORS} cpuTest)
