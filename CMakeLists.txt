cmake_minimum_required (VERSION 3.28.0)
project(async_shared_mutex_study VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.81.0 REQUIRED)

list(APPEND exec_PROGRAMS
    study.cpp
)

include(FetchContent)
FetchContent_Declare(
  sam
  GIT_REPOSITORY https://github.com/klemens-morgenstern/sam.git
  GIT_TAG d4e5b2970bb7462808235213d71f86bd5745ef59
)
FetchContent_MakeAvailable(sam)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/_deps/sam-src/include)

foreach(source_file ${exec_PROGRAMS})
    get_filename_component(source_file_we ${source_file} NAME_WE)
    add_executable(${source_file_we} ${source_file})
    target_link_libraries(${source_file_we} boost_sam)
endforeach()
