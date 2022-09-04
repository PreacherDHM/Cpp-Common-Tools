include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)


project(CommonTests LANGUAGES CXX)

add_executable(CommonTests ./DuggingTests.cpp)

target_link_libraries(CommonTests PRIVATE GTest::GTest Common)
include_directories(../includes)

add_test(Common CommonTests)
