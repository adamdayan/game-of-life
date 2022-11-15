cmake_minimum_required(VERSION 3.10)
project(game-of-life LANGUAGES CXX CUDA)
if(NOT DEFINED CMAKE_CUDA_ARCHITECTURES)
  set(CMAKE_CUDA_ARCHITECTURES 75)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package(CUDAToolkit)
find_package(SFML COMPONENTS system window graphics REQUIRED)

# create game_backend library
add_library(game_backend src/cpu_board.cpp src/game_manager.cpp src/renderer.cpp src/gpu_board.cu)
target_include_directories(game_backend PUBLIC include/)
target_link_libraries(game_backend PUBLIC CUDA::cudart)
target_link_libraries(game_backend PUBLIC sfml-graphics sfml-window sfml-system)
set_target_properties(game_backend PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

# create run_game executable
add_executable(run_game src/main.cpp)
target_link_libraries(run_game PUBLIC game_backend)

# create speed_test executable
add_executable(speed_test src/speed_test.cpp)
target_link_libraries(speed_test PUBLIC game_backend)