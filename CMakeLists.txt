cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(CMAKE_C_STANDARD 11)
set(PROG hashtab_test)

project(hashtab-test LANGUAGES C)

add_executable(${PROG} src/hashtab_test.c src/hashtab.c)

list(APPEND flags "-Wall")

if(NOT WIN32)
    list(APPEND flags "-Wextra" "-Wpedantic")
endif()

target_compile_options(${PROG}
        PRIVATE
            ${flags}
        )


find_package(PkgConfig REQUIRED)

pkg_check_modules(deps REQUIRED IMPORTED_TARGET glib-2.0)
target_link_libraries(${PROG} PkgConfig::deps)
