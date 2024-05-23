cmake_minimum_required(VERSION 3.11.0)
project(car_rental VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# find_package(Qt5 COMPONENTS Widgets REQUIRED) GUI

include(FetchContent)
FetchContent_Declare(
   googletest
   GIT_REPOSITORY      https://github.com/google/googletest.git
   GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

set(PROJECT_SOURCES
    src
    main.cpp
    gui.cpp
)

add_executable(MyProject ${PROJECT_SOURCES})

# target_link_libraries(MyProject Qt5::Widgets) GUI

# add_executable(testGoogle tests/test_flist.cpp tests/test_logger.cpp ${PROJECT_SOURCES})
# target_link_libraries(testGoogle PUBLIC gtest_main)
