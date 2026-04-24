include(FetchContent)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(test_src
    AllTests.cpp
    tests.cpp)

add_executable(${PROJECT_NAME}.test ${test_src})

target_include_directories(${PROJECT_NAME}.test PRIVATE
    ${${PROJECT_NAME}_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME}.test PRIVATE
    ${PROJECT_NAME}
    GTest::gtest)

add_test(NAME ${PROJECT_NAME}.test COMMAND ${PROJECT_NAME}.test)

install(TARGETS ${PROJECT_NAME}.test
        DESTINATION "${tool_dest}")
