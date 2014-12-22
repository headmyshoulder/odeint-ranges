
add_executable ( const_step_range const_step_range.cpp )
target_link_libraries ( const_step_range ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
add_test ( NAME const_step_range COMMAND const_step_range )