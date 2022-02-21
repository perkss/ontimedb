cmake_minimum_required(VERSION 3.21)
project(OnTimeDb
        VERSION 0.1
        DESCRIPTION "A TimeSeries Distributed Database")
set(CMAKE_CXX_STANDARD 11)

# The compiled library code is here
add_subdirectory(collections)

# The executable code is here
add_subdirectory(db)

add_subdirectory(tests)

enable_testing()


add_library(commonLibrary LibraryCode.c)

add_executable(mainApp main.cpp)
target_link_libraries(mainApp commonLibrary)