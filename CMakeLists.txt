# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.15)

set(CMAKE_CXX_STANDARD 23)

if (MSVC)
  add_compile_definitions(NOMINMAX _CRT_SECURE_NO_WARNINGS)
endif()

project ("AdventOfCode2024")

function(add_aoc_day day_name)
    add_executable(${day_name} "src/${day_name}/${day_name}.cpp" "src/${day_name}/${day_name}.h")
    
    target_include_directories(${day_name} PUBLIC "src/Utils")
    target_link_libraries(${day_name} PUBLIC Utils ctre::ctre)
    
    install(TARGETS ${day_name} DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )

    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/${day_name}/input.txt")
        message("Copying input file for ${day_name}")
        configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/${day_name}/input.txt" "${CMAKE_CURRENT_BINARY_DIR}/${day_name}_input.txt" COPYONLY)
    else()
        message(WARNING "Input file not found: ${CMAKE_CURRENT_SOURCE_DIR}/src/${day_name}/input.txt" )
    endif()
endfunction()

find_package(ctre)
find_package(nlohmann_json)
find_package(bshoshany-thread-pool)
find_package(Eigen3)

add_library(Utils STATIC "src/Utils/Utils.cpp" "src/Utils/Utils.h")
target_link_libraries(Utils PUBLIC ctre::ctre nlohmann_json::nlohmann_json bshoshany-thread-pool::bshoshany-thread-pool Eigen3::Eigen)

add_aoc_day("Day01")
add_aoc_day("Day02")
add_aoc_day("Day03")
add_aoc_day("Day04")
add_aoc_day("Day05")
add_aoc_day("Day06")
add_aoc_day("Day07")
add_aoc_day("Day08")
add_aoc_day("Day09")
add_aoc_day("Day10")
add_aoc_day("Day11")
add_aoc_day("Day12")
add_aoc_day("Day13")
add_aoc_day("Day14")
add_aoc_day("Day15")
add_aoc_day("Day16")
add_aoc_day("Day17")
add_aoc_day("Day18")
add_aoc_day("Day19")
add_aoc_day("Day20")
add_aoc_day("Day21")
add_aoc_day("Day22")
add_aoc_day("Day23")
add_aoc_day("Day24")
add_aoc_day("Day25")
