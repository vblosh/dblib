include("${CMAKE_CURRENT_LIST_DIR}/UnitTest++Targets.cmake")
get_filename_component(UTPP_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../../../include/" ABSOLUTE)

set_target_properties(UnitTest++ PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ${UTPP_INCLUDE_DIRS}
)
