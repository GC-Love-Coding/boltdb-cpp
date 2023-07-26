add_executable(alloc_test alloc_test.cc)
target_link_libraries(alloc_test PRIVATE Catch2::Catch2WithMain)