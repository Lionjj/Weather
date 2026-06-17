cmake_minimum_required(VERSION 3.15)

project(Meteo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE)
    list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew")
endif()

file(GLOB SOURCES "src/*.cpp")

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(Meteo ${SOURCES})

target_link_libraries(Meteo PRIVATE
    CURL::libcurl
    nlohmann_json::nlohmann_json
)