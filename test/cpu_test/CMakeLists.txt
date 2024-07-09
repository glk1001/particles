cmake_minimum_required(VERSION 3.28)

set(PROJECT_NAME cpuTest)

add_executable(${PROJECT_NAME}
               "cpu_test.cpp"
               attractor_effect.cpp
               fountain_effect.cpp
               tunnel_effect.cpp
)

target_sources(${PROJECT_NAME}
               PRIVATE
               FILE_SET private_modules TYPE CXX_MODULES FILES
               attractor_effect.cppm
               fountain_effect.cppm
               tunnel_effect.cppm
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
