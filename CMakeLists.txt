cmake_minimum_required(VERSION 3.5)

project(Time_Manager CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fpermissive")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
find_package(wxWidgets COMPONENTS aui base core gl adv REQUIRED)

file(GLOB_RECURSE api_srcs "${CMAKE_SOURCE_DIR}/TimeSheet-API/*.cpp")
file(GLOB_RECURSE api_hdrs "${CMAKE_SOURCE_DIR}/TimeSHeet-API/*.h")

include_directories("${CMAKE_SOURCE_DIR}/TimeSheet-API/")

add_library(
    "${PROJECT_NAME}-api"
    ${api_srcs}
    ${api_hdrs}
)

include("${wxWidgets_USE_FILE}")

target_link_libraries("${PROJECT_NAME}-api" ${wxWidgets_LIBRARIES})

file(GLOB_RECURSE gui_srcs "${CMAKE_SOURCE_DIR}/TimeSheet/*.cpp")
file(GLOB_RECURSE gui_hdrs "${CMAKE_SOURCE_DIR}/TimeSheet/*.h")

include_directories("${CMAKE_SOURCE_DIR}/TimeSheet/")
include_directories("${CMAKE_SOURCE_DIR}/TimeSheet-API/")

include("${wxWidgets_USE_FILE}")

add_executable(
    "${PROJECT_NAME}"
    ${gui_srcs}
    ${gui_hdrs}
)
target_link_libraries("${PROJECT_NAME}" "${PROJECT_NAME}-api")
target_link_libraries("${PROJECT_NAME}" ${wxWidgets_LIBRARIES})