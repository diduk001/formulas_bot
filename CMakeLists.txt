cmake_minimum_required(VERSION 3.18)
project(formulas_tmp)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(Boost_USE_MULTITHREADED ON)


# -- TgBot requirements --
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)
find_package(SQLite3 REQUIRED)

include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR} ${SQLite3_INCLUDE_DIRS})
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()
# -- --

add_subdirectory(lib/tgbot-cpp)
add_executable(formulas_bot src/main.cpp include/constants.h include/db_utils.h include/Subject.h include/group.h include/state.h)
target_link_libraries(formulas_bot TgBot ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES} ${SQLite3_LIBRARIES})

# Enable Google Tests
enable_testing()
find_package(GTest REQUIRED)

add_executable(
        example_test
        tests/example_test.cpp
)
target_link_libraries(
        example_test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(example_test)