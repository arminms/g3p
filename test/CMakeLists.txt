## defining target for unit tests
#
add_executable(unit_tests unit_tests.cpp)

## defining link libraries for unit tests
#
target_link_libraries(unit_tests PRIVATE
  ${PROJECT_NAME}::${PROJECT_NAME}
  Catch2::Catch2WithMain
)

## finally adding unit tests
#
catch_discover_tests(unit_tests)
