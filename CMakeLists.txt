cmake_minimum_required(VERSION 3.11.0)
project(flist VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include(FetchContent)
FetchContent_Declare(
   googletest
   GIT_REPOSITORY      https://github.com/google/googletest.git
   GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

set(PROJECT_SOURCES 
    src/vehicle.cpp 
    src/rental.cpp 
    src/fleet_managment.cpp 
    src/rental_managment.cpp 
    src/customer.cpp 
    src/customer_managment.cpp 
    main.cpp
)

add_executable(MyProject ${PROJECT_SOURCES})

target_link_libraries(MyProject Qt5::Widgets)

# add_executable(testGoogle tests/test_flist.cpp tests/test_logger.cpp ${PROJECT_SOURCES})
# target_link_libraries(testGoogle PUBLIC gtest_main)
