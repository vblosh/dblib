include(GoogleTest)

set(DBLIB_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(dblib_tests main.cpp main.h dbaccesstestsuite.cpp)
target_include_directories(dblib_tests PRIVATE ${DBLIB_INCLUDE_DIR} ${ODBC-CPP-WRAPPER_INCLUDE_DIR})
target_link_directories(dblib_tests PRIVATE ${ODBC-CPP-WRAPPER_LIB_DIR})
target_link_libraries(dblib_tests odbccpp GTest::GTest)

add_test(NAME test COMMAND dblib_tests)
