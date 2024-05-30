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
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
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
    main.cpp
    gui.cpp
)

add_executable(MyProject ${PROJECT_SOURCES})

# target_link_libraries(MyProject Qt5::Widgets) GUI

# add_executable(testGoogle tests/ tests/ ${PROJECT_SOURCES})
# target_link_libraries(testGoogle PUBLIC gtest_main)
target_link_libraries(MyProject PRIVATE nlohmann_json::nlohmann_json)
