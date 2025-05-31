cmake_minimum_required(VERSION 3.15)
project(MyGameProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Папка для бинарников (исполняемых файлов)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Папка для объектных файлов и библиотек
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/obj)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/obj)

# ---- Вынесем общие исходники игры в библиотеку ----

file(GLOB_RECURSE GAME_SOURCES src/*.cpp)

add_library(game_lib STATIC ${GAME_SOURCES})

target_include_directories(game_lib PUBLIC ${CMAKE_SOURCE_DIR}/src)

# ---- Исполняемый файл игры ----

add_executable(game src/main.cpp) # только main.cpp для запуска игры

target_link_libraries(game PRIVATE game_lib)

# ---- GTest ----
add_subdirectory(lib/googletest)

enable_testing()

file(GLOB TEST_SOURCES test/*.cpp)

add_executable(tests ${TEST_SOURCES})

target_link_libraries(tests PRIVATE game_lib gtest_main)

add_test(NAME RunUnitTests COMMAND tests)

# --- Кастомные цели для удобства ---

add_custom_target(run_game
  COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} ./game
  DEPENDS game
  WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

add_custom_target(run_tests
  COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
  DEPENDS tests
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
