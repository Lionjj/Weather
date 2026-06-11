cmake_minimum_required(VERSION 3.15)

project(Meteo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Meteo src/main.cpp)

execute_process(
    COMMAND xcrun --show-sdk-path
    OUTPUT_VARIABLE MAC_SDK_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

target_include_directories(Meteo PRIVATE "${MAC_SDK_PATH}/usr/include")

target_link_options(Meteo PRIVATE "-isysroot" "${MAC_SDK_PATH}")
target_link_libraries(Meteo PRIVATE "curl")