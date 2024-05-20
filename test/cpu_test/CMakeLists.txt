cmake_minimum_required(VERSION 3.28)

set(PROJECT_NAME cpuTest)

add_executable(${PROJECT_NAME}
        "cpu_test.cpp"
        )

set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
        )

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        particles::lib
        m
        stdc++
        )

particles_set_project_warnings(${particles_WARNINGS_AS_ERRORS} cpuTest)
