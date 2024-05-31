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
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(json)

set(PROJECT_SOURCES
    src/address/address.cpp
    src/customer/customer.cpp
    src/customer/customer_management.cpp
    src/fleet/fleet_management.cpp
    src/rental/rental.cpp
    src/rental/rental_management.cpp
    src/location/location.cpp
    src/vehicle/vehicle.cpp
    src/simulation/simulation.h
)

add_executable(car_rental main.cpp ${PROJECT_SOURCES})

target_link_libraries(car_rental PRIVATE nlohmann_json::nlohmann_json)

# target_link_libraries(MyProject Qt5::Widgets) GUI

add_executable(car_rental_tests
    tests/test_customer_management.cpp
    tests/test_customer.cpp
    tests/test_fleet_management.cpp
    tests/test_rental_management.cpp
    tests/test_rental.cpp
    tests/test_vehicle.cpp
    tests/test_address.cpp

 ${PROJECT_SOURCES})
target_link_libraries(car_rental_tests PUBLIC gtest_main)
target_link_libraries(car_rental_tests PRIVATE nlohmann_json::nlohmann_json)

