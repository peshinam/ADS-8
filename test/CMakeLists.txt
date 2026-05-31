add_executable(ADS-8.test AllTests.cpp tests.cpp)
target_include_directories(ADS-8.test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(ADS-8.test gtest gtest_main)
add_test(NAME ADS-8.test COMMAND ADS-8.test)
