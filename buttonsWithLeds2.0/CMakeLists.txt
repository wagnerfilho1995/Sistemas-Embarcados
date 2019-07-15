cmake_minimum_required(VERSION 3.13.1)

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(buttonsWithLeds2)


list(APPEND HEADERS
    "${PROJECT_BINARY_DIR}/include/generated"
    "${PROJECT_BINARY_DIR}/zephyr/include/generated"
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/include/setup"
    "${PROJECT_SOURCE_DIR}/include/input"
    "${PROJECT_SOURCE_DIR}/include/output"
    )

list(APPEND SOURCES
    "${PROJECT_SOURCE_DIR}/src/main.c"
    "${PROJECT_SOURCE_DIR}/src/input.c"
    "${PROJECT_SOURCE_DIR}/src/output.c"
)

include_directories(${HEADERS})
target_sources(app PRIVATE ${SOURCES})
