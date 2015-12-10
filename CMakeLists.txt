cmake_minimum_required(VERSION 2.8)
project(generic_ransac)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
file(GLOB_RECURSE source_files src/*.cpp)
list(REMOVE_ITEM source_files ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
file(GLOB_RECURSE header_files include/*.h)
add_executable(main src/main.cpp ${source_files} ${header_files})


# TESTING =====================

enable_testing()
find_package(GTest)

if (GTEST_FOUND)
    file(GLOB_RECURSE test_files test/*.cpp test/*.h)
    add_executable(testing ${source_files} ${header_files} ${test_files})
    include_directories(${GTEST_INCLUDE_DIRS})
    target_link_libraries(testing ${GTEST_LIBRARIES} pthread)
else ()
    message(WARNING "Could not find GTest")
endif ()


# EXTERNAL LIBRAIRIES =====================

# OpenCV
FIND_PACKAGE(OpenCV REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(main ${OpenCV_LIBS})
if (GTEST_FOUND)
    target_link_libraries(testing ${PROJECT_LIBS})
endif ()

