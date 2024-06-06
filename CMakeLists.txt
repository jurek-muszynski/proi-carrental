cmake_minimum_required(VERSION 3.11.0)
project(car_rental VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

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
    src/user/user.cpp
    src/customer/customer.cpp
    src/admin/admin.cpp
    src/customer/customer_management.cpp
    src/fleet/fleet_management.cpp
    src/rental/rental.cpp
    src/rental/rental_management.cpp
    src/location/location.cpp
    src/vehicle/vehicle.cpp
    src/simulation/simulation.cpp
    src/simulation/simulation_report.cpp
    src/simulation/simulation_report_entity.cpp
    src/userInterface/userInterface.cpp
)

add_executable(car_rental user_interface.cpp ${PROJECT_SOURCES})

target_link_libraries(car_rental PRIVATE nlohmann_json::nlohmann_json)

add_executable(car_rental_simulation simulation.cpp ${PROJECT_SOURCES})

target_link_libraries(car_rental_simulation PRIVATE nlohmann_json::nlohmann_json)

add_executable(car_rental_tests
    tests/test_customer_management.cpp
    tests/test_customer.cpp
    tests/test_fleet_management.cpp
    tests/test_rental_management.cpp
    tests/test_rental.cpp
    tests/test_vehicle.cpp
    tests/test_address.cpp
    tests/test_location.cpp

 ${PROJECT_SOURCES})

target_link_libraries(car_rental_tests PUBLIC gtest_main)
target_link_libraries(car_rental_tests PRIVATE nlohmann_json::nlohmann_json)