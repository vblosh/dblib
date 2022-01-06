cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)

project(dblib)

find_path(ODBC-CPP-WRAPPER_INCLUDE_DIR ...)

if((NOT ODBC-CPP-WRAPPER_INCLUDE_DIR) OR (NOT EXISTS ${ODBC-CPP-WRAPPER_INCLUDE_DIR}))
    # we couldn't find the header files for ODBC-CPP-WRAPPER or they don't exist
    message("Unable to find odbc-cpp-wrapper")

    # we have a submodule setup for odbc-cpp-wrapper, assume it is under ext/odbc-cpp-wrapper
    # now we need to clone this submodule
    execute_process(COMMAND git submodule update --init -- ext/odbc-cpp-wrapper
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

    # set ODBC-CPP-WRAPPER_INCLUDE_DIR properly
    set(ODBC-CPP-WRAPPER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/odbc-cpp-wrapper/include/obdc
        CACHE PATH "odbc-cpp-wrapper include directory")

    # build it
    add_subdirectory(ext/odbc-cpp-wrapper)
else()
    # see above, setup target as well
endif()

find_package(GTest)

#add_subdirectory(include)
if (GTEST_FOUND)
	enable_testing()
    add_subdirectory(test)
endif()
