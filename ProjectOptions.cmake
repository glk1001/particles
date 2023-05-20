macro(particles_supports_sanitizers)
  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)
    set(SUPPORTS_UBSAN ON)
  else()
    set(SUPPORTS_UBSAN OFF)
  endif()

  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
    set(SUPPORTS_ASAN OFF)
  else()
    set(SUPPORTS_ASAN ON)
  endif()
endmacro()

particles_supports_sanitizers()
option(particles_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${SUPPORTS_ASAN})
option(particles_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
option(particles_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${SUPPORTS_UBSAN})
option(particles_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
option(particles_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)

if (NOT SUPPORTS_UBSAN
    OR particles_ENABLE_SANITIZER_UNDEFINED
    OR particles_ENABLE_SANITIZER_ADDRESS
    OR particles_ENABLE_SANITIZER_THREAD
    OR particles_ENABLE_SANITIZER_LEAK)
    set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
else ()
    set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
endif ()

particles_assure_out_of_source_builds()
particles_enable_cache()

option(particles_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" ON)
